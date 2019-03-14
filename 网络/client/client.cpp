#include <bits/stdc++.h>
#include <unistd.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <errno.h>

using namespace std;

#define IPADDR 127.0.0.1
#define PORT 8787

int main() {
    int sockfd;
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("socket");
        return -1;
    }
    sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(PORT);
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    int err = -1;
    if ((err = connect(sockfd, (sockaddr*)&addr, sizeof(addr))) < 0) {
        perror("connect");
        return -1;
    }
    char buf[1024];
    char recv[1024];
    read(sockfd, recv, 1024);
    cout << recv << endl;
    while(true){
        /* code */
        cin >> buf;
        char* p = buf;
        int len = strlen(buf) + 1;
        int n = write(sockfd, p, len);
        while(n < len){
            /* code */
            p += n;
            len -= n;
            n = write(sockfd, p, len);
        }
        close(sockfd);
    }
    return 0;
}