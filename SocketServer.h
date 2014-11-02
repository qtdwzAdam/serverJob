#ifndef SOCKETSERVER_H
#define SOCKETSERVER_H

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
