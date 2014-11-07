#ifndef SOCKETSERVER_H
#define SOCKETSERVER_H

#include <QTcpServer>
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
    ~SocketServer ();

    void    Run ( quint16 port );
    void    sendString(QString str, QTcpSocket *clientConnection);

protected:
    void    incomingConnection(int socketDescriptor );

public slots:
    void    sendout();
private slots:
    void    confirmID();

private:

};

#endif // SOCKETSERVER_H
