#include <unistd.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <cstring>
#include <bits/stdc++.h>
using namespace std;
#define IPADDRESS   "127.0.0.1"
#define PORT        8787
#define MAXLINE     1024
#define LISTENQ     5

int main() {
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("socket");
        exit(-1);
    }
    struct sockaddr_in addr;
    struct sockaddr_in cliaddr;
    memset(&addr, 0, sizeof(addr));
    memset(&cliaddr, 0, sizeof(cliaddr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(PORT);
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    if (bind(sockfd, (struct sockaddr*)&addr, sizeof(addr)) < 0) {
        perror("bind");
        exit(-1);
    }
    if (listen(sockfd, LISTENQ) < 0) {
        perror("listen");
        exit(-1);
    }
    int connfd = -1;
    socklen_t len = sizeof(cliaddr);
    while(1){
        if((connfd = accept(sockfd, (struct sockaddr*)&cliaddr, &len)) < 0){
            /* code */
            perror("conn");
            std::cout << errno << std::endl;
            printf("connect from: %s", inet_ntoa(cliaddr.sin_addr));
        }
        char buf[] = "i am server";
        write(connfd, buf, strlen(buf)+1);
        char recv[1024];
        read(connfd, recv, 1024);
        cout << recv << endl;
        close(connfd);
    }
    close(sockfd);
    return 0;
}