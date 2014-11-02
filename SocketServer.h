#ifndef SOCKETSERVER_H
#define SOCKETSERVER_H

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<winsock.h>
#include<sys/types.h>
//#include<unistd.h>
#include<windows.h>
#include<errno.h>

#pragma comment(lib, "wsock32.lib")

#define SERVER_PORT 9877

#define MAX_SOCKET 20

class TcpSocketServer{
public:
    int init();
    int acceptClient(int listenfd);
    void sendToClient(int clientfd, char* sendBuf);
    int recvFromClient(int clientfd, char* recvBuf, int maxLength);
    void closeClient(int clientfd);
};


#endif // SOCKETSERVER_H
