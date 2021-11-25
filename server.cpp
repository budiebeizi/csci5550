#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<iostream>
#include<string.h>
#include<vector>

#define recvBuf_Size 32
#define SERVER_PORT 3000

int main(int argc,char *argv[])
{
        //创建一个监听socket
        int listenfd=socket(AF_INET,SOCK_STREAM,0);
        if(listenfd == -1)
        {

                std::cout<<"create client fd error. "<< std::endl;
                return -1;
        }

        //初始化服务器地址
        struct sockaddr_in bindaddr;
        bindaddr.sin_family = AF_INET;
        bindaddr.sin_addr.s_addr = htonl(INADDR_ANY);
        bindaddr.sin_port = htons(SERVER_PORT);
        if(bind(listenfd,(struct sockaddr *)&bindaddr,sizeof(bindaddr)) == -1)
        {


                std::cout << "bind listen  socket error" << std::endl;
                return -1;
        }

        //启动监听

        if(listen(listenfd,SOMAXCONN) == -1)//SOMAXCONN 表示监听队列数默认为128
        {

                std::cout << "listen error." << std::endl;
                return -1;
        }
        //记录所有客户端连接的容器
        std::vector<int> clientfds;

        while(true)
        {
                struct sockaddr_in clientaddr;
                socklen_t clientaddrlen = sizeof(clientaddr); //accept函数第三个参数需要的类型

                //接受客户端的连接
                int clientfd = accept(listenfd, (struct sockaddr *)&clientaddr, &clientaddrlen );
                if(clientfd != -1 )
                {
                        char recvBuf[recvBuf_Size] ={0};
                        //从客户端接受数据
                        int ret = recv(clientfd, recvBuf, recvBuf_Size, 0);
                        if(ret > 0)
                        {
                                std::cout <<"recv data from client, data:" <<recvBuf <<std::endl;
                                //将收到的数据处理后发送给客户端
                                ret = send(clientfd, recvBuf, strlen(recvBuf), 0);
                                if(ret != strlen(recvBuf))
                                        std::cout << "send data error."<< std::endl;

                                std::cout << "send data successfully,data:" << recvBuf << std::endl;

                        }
                        else

                        {
                                std::cout <<"recv data error." <<std::endl;
                        }
                        //关闭客户端fd
                        close(clientfd);

                }
        }


        //关闭监听fd
        close(listenfd);
        return 0;
}