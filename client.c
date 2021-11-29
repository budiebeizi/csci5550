#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<string.h>
#include<stdio.h>

int main(int argc,char *argv[]){
    char *path = "sunyz/2mfile"
    char *server_address = "10.0.41.2";
    int server_port = 3000;
    char *send_data = strchr(path, '/');
    send_data[0] = 'w';
    int buffer_size = 4096;

    
    int clientfd = socket(AF_INET, SOCK_STREAM, 0);
    if(clientfd == -1){
        printf("create socket error. \n");
        return -1;
    }

    struct sockaddr_in serveraddr;
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_addr.s_addr = inet_addr(server_address);
    serveraddr.sin_port = htons(server_port);
    if(connect(clientfd, (struct sockaddr *)&serveraddr, sizeof(serveraddr)) == -1){
        printf("connect error. \n");
        return -1;
    }

    int ret = send(clientfd, send_data, sizeof(send_data));

    char *recvBuf[4096] = {'\0'};
    ret = recv(clientfd, recvBuf, 4096, 0);
    if(ret > 0){
        printf(recvBuf);
        printf('\n');
    }else{
        printf("recv data error. \n");
    }
    close(clientfd);
    return 0;
}