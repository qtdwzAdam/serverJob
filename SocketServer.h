#ifndef SOCKETSERVER_H
#define SOCKETSERVER_H

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
<<<<<<< HEAD
#include<sys/types.h>
#include<windows.h>
#include<winsock.h>
#include<errno.h>

#pragma comment(lib, "wsock32.lib")
#pragma comment(lib, "ws2_32.lib")
=======
#include<winsock.h>
#include<sys/types.h>
//#include<unistd.h>
#include<windows.h>
#include<errno.h>

#pragma comment(lib, "wsock32.lib")
>>>>>>> 2834e1677e2fe6ce8fedef01e753b7f40e1c9892

#define SERVER_PORT 9877

#define MAX_SOCKETFD 20

class TcpSocketServer{
public:
    int init();
    int acceptClient(int listenfd);
    void sendToClient(int clientfd, char* sendBuf);
    int recvFromClient(int clientfd, char* recvBuf, int maxLength);
    void closeClient(int clientfd);
};


#endif // SOCKETSERVER_H
