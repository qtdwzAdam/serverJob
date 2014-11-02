#include "SocketServer.h"

int TcpSocketServer::init()
{
    int listenfd;
    struct sockaddr_in serveraddr;

    listenfd = socket(AF_INET, SOCK_STREAM, 0);
    if(listenfd<0)
    {
        printf("Socket Error!\n");
        return -1;//exit(1);
    }

    bzero(&serveraddr, sizeof(serveraddr));
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(SERVER_PORT);
    serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);//(SERVER_IP);

    bind(listenfd, (struct sockaddr *)&serveraddr, sizeof(serveraddr));

    listen(listenfd, MAX_SOCKETFD);

    return listenfd;
}

int TcpSocketServer::acceptClient(int listenfd)
{
    socklen_t clientlen;
    int clientfd;
    struct sockaddr_in clientaddr;

    clientlen = sizeof(clientaddr);
    clientfd = accept(listenfd, (struct sockaddr *)&clientaddr, &clientlen);
    if(clientfd<0)
    {
        if(errno == EINTR)
            return -1;//continue;
        else
        {
            printf("Accept Error!\n");
            return -2;
        }
    }

    return clientfd;
}

void TcpSocketServer::sendToClient(int clientfd, char* sendBuf)
{
    send(clientfd, sendBuf, strlen(sendBuf)+1, 0);
}

int TcpSocketServer::recvFromClient(int clientfd, char* recvBuf, int maxLength)
{
    int recvState;
    recvState = recv(clientfd, recvBuf, maxLength, 0);
    return recvState;
}

void TcpSocketServer::closeClient(int clientfd)
{
    close(clientfd);
}
