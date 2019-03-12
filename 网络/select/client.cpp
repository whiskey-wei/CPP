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

#define MAXLINE 1024
#define IPADDRESS "127.0.0.1"
#define SERV_PORT 8787

int echo(int fd, char* buf) {
    write(fd, buf, 1024);
    read(fd, buf, 1024);
    printf("%s\n", buf);
    while(1){
        /* code */
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

    int conn = connect(sockfd, (struct sockaddr*)&addr, sizeof(addr));
    if (conn < 0) {
        perror("connect error");
        return -1;
    }
    char buf[] = "hellow server";
    echo(sockfd, buf);
    close(sockfd);
    return 0;
}