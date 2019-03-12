#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include <netinet/in.h>
#include <sys/socket.h>
#include <poll.h>
#include <unistd.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <assert.h>

#define IPADDRESS   "127.0.0.1"
#define PORT        8787
#define MAXLINE     1024
#define LISTENQ     5
#define OPEN_MAX    1000
#define INFTIM      -1

//函数声明
//创建套接字绑定
static int socket_bind(const char* ip, int port);
//IO多路复用
static void do_poll(int listenfd);
//处理多个连接
static void handle_connection(struct pollfd *connfds, int num);

int main(int argc ,char* argv[]) {
    int listenfd, connfd, sockfd;
    struct sockaddr_in cliaddr;
    socklen_t cliaddrlen;
    listenfd = socket_bind(IPADDRESS, PORT);
    listen(listenfd, LISTENQ);
    do_poll(listenfd);
    return 0;
}

static int socket_bind(const char *ip, int port) {
    int listenfd;
    struct sockaddr_in servaddr;
    listenfd = socket(AF_INET, SOCK_STREAM, 0);
    if (listenfd == -1) {
        perror("socket error");
        exit(-1);
    }
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(port);
    inet_pton(AF_INET, ip, &servaddr.sin_addr);
    
    if (bind(listenfd, (struct sockaddr*)&servaddr, sizeof(servaddr)) == -1) {
        perror("bind");
        exit(-1);
    }

    return listenfd;
}

static void do_poll(int listenfd) {
    int connfd, sockfd;
    struct sockaddr_in cliaddr;
    socklen_t cliaddrlen;
    struct pollfd clienfds[OPEN_MAX];
    int maxi, i, nready;

    //添加监听描述符
    clienfds[0].fd = listenfd;
    clienfds[0].events = POLLIN;

    //初始化客户连接描述符
    for (i = 1; i < OPEN_MAX; ++i) {
        clienfds[i].fd = -1;
    }
    maxi = 0;

    //循环处理
    while(1){
        /* code */
        //获取可用描述符个数
        nready = poll(clienfds, maxi + 1, INFTIM);
        if (nready == -1) {
            perror("poll error");
            exit(-1);
        }
        //测试监听描述符是否准备好
        if (clienfds[0].revents & POLLIN) {
            cliaddrlen = sizeof(cliaddr);
            //接受新的连接
            if ((connfd = accept(listenfd, (struct sockaddr*)&cliaddr, &cliaddrlen)) == -1) {
                if (errno == EINTR) {
                    continue;
                }
                else
                {
                    /* code */        
                    perror("accept");
                    exit(-1);
                }
            }
            printf("accept a new client: %s:%d.\n", inet_ntoa(cliaddr.sin_addr), cliaddr.sin_port);
            //将新的描述符加入到数组中
            for (i = 1; i < OPEN_MAX; ++i) {
                if (clienfds[i].fd < 0) {
                    clienfds[i].fd = connfd;
                    break;
                }
            }
            if (i == OPEN_MAX) {
                printf("too many clients.\n");
                exit(-1);
            }
            //将新的描述符加入到读描述符集合中
            clienfds[i].events = POLLIN;
            //记录客户连接套接字的个数
            maxi = (i > maxi ? i : maxi);
            if (--nready <= 0) {
                continue;
            }
        }
        handle_connection(clienfds, maxi);
    }
}
static void handle_connection(struct pollfd *connfds, int num) {
    int i, n;
    char buf[MAXLINE];
    memset(buf, 0, MAXLINE);
    for (i = 1; i <= num; ++i) {
        if (connfds[i].fd < 0) {
            continue;
        }
        //客户端描述符是否表示好
        if (connfds[i].revents & POLLIN) {
            //接收客户端发送的信息
            n = read(connfds[i].fd, buf, MAXLINE);
            printf("recv msg is: %s \n\n",buf);
            if (n == 0) {
                close(connfds[i].fd);
                connfds[i].fd = -1;
                continue;
            }
            write(connfds[i].fd, buf, n);
        }
    }
}