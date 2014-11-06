#ifndef SOCKETSERVER_H
#define SOCKETSERVER_H

#include <QTcpServer>
#include <QNetworkInterface>
QString getIPAddress() ;
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
