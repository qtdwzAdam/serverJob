#ifndef SOCKETSERVER_H
#define SOCKETSERVER_H

#include <QDialog>
#include <QTcpServer>
#include <QNetworkInterface>
QT_BEGIN_NAMESPACE
class QLabel;
class QPushButton;
class QTcpServer;
class QNetworkSession;
QT_END_NAMESPACE

QString getIPAddress() ;

class SocketServer : public QDialog
{
    Q_OBJECT

public:
    SocketServer  ( QWidget *parent = NULL );
    ~SocketServer ();

    void    Run ( quint16 port );
    void    sendString(QString str, QTcpSocket *clientConnection);

protected:
    void    incomingConnection  ( int handle );

private slots:
    void    sessionOpened();
    void    confirmID();

private:
    QLabel *statusLabel;
    QPushButton *quitButton;
    QTcpServer *tcpServer;
    QStringList fortunes;
    QNetworkSession *networkSession;

    QPushButton     *sendTest;

};

#endif // SOCKETSERVER_H
