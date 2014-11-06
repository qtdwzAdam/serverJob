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

class ChatServer : public QDialog
{
    Q_OBJECT

public:
    ChatServer  ( QWidget *parent = NULL );
    ~ChatServer ();

    void    Run ( quint16 port );

protected:
    void    incomingConnection  ( int handle );

private slots:
    void    sessionOpened();
    void    sendFortune();

private:
    QLabel *statusLabel;
    QPushButton *quitButton;
    QTcpServer *tcpServer;
    QStringList fortunes;
    QNetworkSession *networkSession;

};

#endif // SOCKETSERVER_H
