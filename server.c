#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<string.h>
#include<stdio.h>

int main(int argc, char *argv[]){
    int recvBuf_size = 4096;
    int server_port = 3000;
    int listenfd = socket(AF_INET, SOCK_STREAM, 0);
    if(listenfd == -1){
        printf("create socket error. \n");
        return -1;
    }

    struct sockaddr_in bindaddr;
    bindaddr.sin_family = AF_INET;
    bindaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    bindaddr.sin_port = htons(server_port);
    if(bind(listenfd, (struct sockaddr *)&bindaddr, sizeof(bindaddr)) == -1){
        printf("bind listen socket error. \n");
        return -1;
    }
    if(listen(listenfd, SOMAXCONN) == -1){
        printf("listen error. \n");
        return -1;
    }

    while(true){
        struct sockaddr_in clientaddr;
        socklen_t clientaddrlen = sizeof(clientaddr);
        
        int clientfd = accept(listenfd, (struct sockaddr *)&clientaddr, &clientaddrlen);
        if(clientfd != -1){
            char *recvBuf[4096] = {'\0'};
            int ret = recv(clientfd, recvBuf, recvBuf_size, 0);
            if(ret > 0){
                if(recvBuf[0] == 'r'){
                    printf("read \n");
                    printf("%s \n", recvBuf+1);
                }
                if(recvBuf[0] == 'w'){
                    printf("write \n");
                    printf("%s \n", recvBuf+1);
                }
            }else{
                printf("recv data error. \n");
                return -1;
            }
        }
    }
    close(listenfd);
    return 0;
}
