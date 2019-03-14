#include <bits/stdc++.h>
#include <unistd.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <errno.h>

using namespace std;

#define PORT 8787

int writen() {
    
}

int main() {
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("socket");
        return -1;
    }
    sockaddr_in seraddr, cliaddr;
    memset(&seraddr, 0, sizeof(seraddr));
    memset(&cliaddr, 0, sizeof(cliaddr));
    seraddr.sin_family = AF_INET;
    seraddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    seraddr.sin_port = htons(PORT);
    if (bind(sockfd, (sockaddr *)&seraddr, sizeof(seraddr)) < 0) {
        close(sockfd);
        perror("bind");
        return -1;
    }
    int connfd;
    if (listen(sockfd, 10) < 0) {
        close(sockfd);
        perror("listen");
        return -1;
    }
    while(1){
        /* code */
        socklen_t len = sizeof(cliaddr);
        if ((connfd = accept(sockfd, (sockaddr *) &cliaddr, &len)) < 0) {
            close(sockfd);
            close(connfd);
            perror("accept");
            return -1;
        }
        int pid = fork();
        if (pid < 0) {
            close(sockfd);
            close(connfd);
            perror("fork");
            return -1;
        }
        else if (pid > 0) {
            char buf[] = "i am server";
            char recv[1024];
            write(connfd, buf, strlen(buf) + 1);
            read(connfd, recv, 1024);
            printf("%s\n", recv);
            close(connfd);
        }
        else {
            close(connfd);
        }
    }
    close(sockfd);
    return 0;
}