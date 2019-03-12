#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <assert.h>

#define IPADDR "127.0.0.1"
#define PORT    8787
#define MAXLINE 1024
#define LISTENQ 5
#define SIZE    10

typedef struct server_context_st
{
    /* data */
    int cli_cnt;        //client数量
    int clifds[SIZE]; 
    fd_set allfds;      //句柄集合
    int maxfd;          //句柄最大值
}server_context_st;

static server_context_st *s_srv_ctx = NULL;

static int create_server_proc(const char* ip, int port) {
    int fd;
    struct sockaddr_in servaddr;
    fd = socket(AF_INET, SOCK_STREAM, 0);
    if (fd == -1) {
        perror("create socket");
        return -1;
    }
    int reuse;
    if (setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse)) == -1) {
        perror("set socket");
        return -1;
    }
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    inet_pton(AF_INET, ip, &servaddr.sin_addr);
    servaddr.sin_port = htons(port);

    if (bind(fd, (struct sockaddr*)&servaddr, sizeof(servaddr)) == -1) {
        perror("bind error:");
        return -1;
    }

    listen(fd, LISTENQ);

    return fd;
}

static int accept_client_proc(int srvfd) {
    struct sockaddr_in cliaddr;
    socklen_t cliaddrlen;
    cliaddrlen = sizeof(cliaddr);
    int clifd = -1;
    printf("Accept client proc is called. \n");

ACCEPT:
    clifd = accept(srvfd, (struct sockaddr*)&cliaddr, &cliaddrlen);
    if (clifd == -1) {
        if(errno == EINTR) {
            goto ACCEPT;
        } else {
             perror("accept error");
             return -1;
        }
    }
    printf("accept a new client: %s:%d\n",inet_ntoa(cliaddr.sin_addr), cliaddr.sin_port);

    //将新的链接描述符加入数组,小于0说明数组这个位置不是别的描述符
    int i = 0;
    for (int i = 0; i < SIZE; ++i) {
        if (s_srv_ctx->clifds[i] < 0) {
            s_srv_ctx->clifds[i] = clifd;
            s_srv_ctx->cli_cnt++;
            break;
        }
    }

    if (i == SIZE) {
        printf("too many clients \n");
        return -1;
    }
}

static int handle_client_msg(int fd, char* buf) {
    assert(buf);
    printf("recv buf is: %s\n", buf);
    write(fd, buf, strlen(buf)+1);
    return 0;
}

static void recv_client_msg(fd_set *readfds) {
    int i = 0, n = 0;
    int clifd;
    char buf[MAXLINE] = {0};
    for (i = 0; i <= s_srv_ctx->cli_cnt; ++i) {
        clifd = s_srv_ctx->clifds[i];
        if (clifd < 0) {
            continue;
        }

        //判断客户端套接字是否有数据
        if (FD_ISSET(clifd, readfds)) {
            //接受客户端发送的消息
            n = read(clifd, buf, MAXLINE);
            //n == 0表示读取完成，客户都关闭套接字
            if (n <= 0) {
                FD_CLR(clifd, &s_srv_ctx->allfds);
                close(clifd);
                s_srv_ctx->clifds[i] = -1;
                continue;
            }
            handle_client_msg(clifd, buf);
        }
    }
}

static void handle_client_proc(int srvfd) {
    int clifd = -1;
    int retval = 0;
    fd_set *readfds = &s_srv_ctx->allfds;
    struct timeval tv;
    int i = 0;

    while(1){
        /*每次调用select都要重新设置文件描述符和时间，
          因为事件发生后，文件描述符和时间都被内核修改了
        */
        FD_ZERO(readfds);
        //添加监听套接字
        FD_SET(srvfd, readfds);
        s_srv_ctx->maxfd = srvfd;

        tv.tv_sec = 30;
        tv.tv_usec = 0;

        //添加客户端套接字
        for (i = 0; i < s_srv_ctx->cli_cnt; ++i) {
            clifd = s_srv_ctx->clifds[i];
            //去掉无效套接字
            if (clifd != -1) {
                FD_SET(clifd, readfds);
            }
            s_srv_ctx->maxfd = (clifd > s_srv_ctx->maxfd ? clifd : s_srv_ctx->maxfd);
        }

        //轮询处理服务端和客户端套接字
        retval = select(s_srv_ctx->maxfd + 1, readfds, NULL, NULL, &tv);
        if (retval == -1) {
            perror("select error");
            return;
        }
        if (retval == 0) {
            printf("select timeout.\n");
            continue;
        }
        if (FD_ISSET(srvfd, readfds)) {
            //监听客户端请求
            accept_client_proc(srvfd);
        } else {
            //接受处理客户端消息
            recv_client_msg(readfds);
        }
    }
}

static void server_uninit() {
    if (s_srv_ctx) {
        free(s_srv_ctx);
        s_srv_ctx = NULL;
    }
}

static int server_init() {
    s_srv_ctx = (server_context_st *)malloc(sizeof(server_context_st));
    if (s_srv_ctx == NULL) {
        return -1;
    }
    memset(s_srv_ctx, 0, sizeof(s_srv_ctx));

    int i = 0;
    for(; i < SIZE; ++i) {
        s_srv_ctx->clifds[i] = -1;
    }

    return 0;
}

int main() {
    int srvfd;
    if (server_init() < 0) {
        printf("init error.\n");
        return -1;
    }

    srvfd = create_server_proc(IPADDR, PORT);
    if (srvfd < 0) {
        goto err;
    }

    //开始处理客户端请求
    handle_client_proc(srvfd);
    server_uninit();

err:
    server_uninit();
    return -1;
}