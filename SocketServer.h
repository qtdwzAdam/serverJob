#ifndef SOCKETSERVER_H
#define SOCKETSERVER_H

<<<<<<< HEAD
#include <QTcpServer>
#include <QNetworkInterface>

QString getIPAddress() ;
=======
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
>>>>>>> 2dee6aeb56ec084770fa910feca4730b263f3516

class MySocket;

class ChatServer : public QTcpServer
{
    Q_OBJECT

public:
    ChatServer  ( QObject *parent = NULL );
    ~ChatServer ();

    void    Run ( quint16 port );

protected:
    void    incomingConnection  ( int handle );

private slots:
    void    clientDisconnected  ();

private:
    quint16             _port;
    QList<MySocket*>  _mysockets;
};

#endif // SOCKETSERVER_H
