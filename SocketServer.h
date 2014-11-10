#ifndef SOCKETSERVER_H
#define SOCKETSERVER_H

#include <QTcpServer>
#include <QTcpSocket>
#include <QNetworkInterface>
QT_BEGIN_NAMESPACE
class QTcpServer;
QT_END_NAMESPACE

QString getIPAddress() ;

class SocketServer :public QTcpServer
{
    Q_OBJECT

public:
    SocketServer  (QObject *parent = 0 , int port=9877);

protected:
    void    incomingConnection(int socketDescriptor );

signals:
    void    bytesArrived(qint64,qint32,QByteArray,int);

};

#endif // SOCKETSERVER_H
