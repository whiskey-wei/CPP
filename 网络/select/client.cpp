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
#include <iostream>
using namespace std;
#define MAXLINE 1024
#define IPADDRESS "127.0.0.1"
#define SERV_PORT 8787

int echo(int fd) {
    char buf[1024];
    char rev[1024];
    while(scanf("%s", buf) != EOF){
        /* code */
        char *p = buf;
        int len = strlen(p);
        while(len > 0){
            int n = write(fd, p, len);
            if (n < 0 && errno == EINTR) {
                n = 0;
            }
            else if(n < 0)
            {
                perror("write");
                exit(-1);
            }
            len -= n;
            p += n;
        }
        int n = read(fd, rev, 100);
        while(n < 0 && errno == EINTR){
            /* code */
            n = read(fd, rev, 100);
        }
        if (n < 0) {
            perror("read");
            exit(-1);
        }
        printf("recv from server:%s\n", rev);
        memset(rev, 0, sizeof(rev));
    }
}

int main() {
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("socket error");
        return -1;
    }
    struct sockaddr_in addr;
    bzero(&addr, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(SERV_PORT);
    inet_pton(AF_INET, IPADDRESS, &addr.sin_addr);

    int err = connect(sockfd, (struct sockaddr*)&addr, sizeof(addr));
    if (err < 0) {
        perror("connect error");
        return -1;
    }
    char buf[] = "hellow server";
    echo(sockfd);
    close(sockfd);
    return 0;
}