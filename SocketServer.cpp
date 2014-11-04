#include "SocketServer.h"
#include "mysocket.h"
#include <QHostAddress>
#include <stdio.h>
ChatServer::ChatServer( QObject *parent)
    : QTcpServer( parent )
{
    _mysockets.empty();
}

ChatServer::~ChatServer()
{
    qDeleteAll( _mysockets );
    _mysockets.clear();
}

void ChatServer::Run( quint16 port )
{
    printf("Run the Run function in ChatServer!\n");
    if( !this->listen(QHostAddress::Any, port) )
    {
        printf( "ChatServer listen failed !" );
        qDebug() << this->errorString();
        close();
    }
}

void ChatServer::incomingConnection( int handle )
{
    printf( "incomingConnection(): %d !\n", handle );
    MySocket *mysocket = new MySocket( this );
    mysocket->setSocketDescriptor( handle );
    connect( mysocket, SIGNAL(disconnected()), this, SLOT(clientDisconnected()) );
    _mysockets.append( mysocket );
}

void ChatServer::clientDisconnected()
{
    printf( "client disconnected !\n" );
    QList<MySocket*>::iterator iter;
    for( iter = _mysockets.begin(); iter != _mysockets.end(); iter++ ) {
        if( -1 == (*iter)->socketDescriptor() ) {
            _mysockets.erase( iter );
            return;
        }
    }
}
QString getIPAddress()
{
QString ipAddress;
    QList<QHostAddress> ipAddressesList = QNetworkInterface::allAddresses();
    for (int i = 0; i < ipAddressesList.size(); ++i) {
        if (ipAddressesList.at(i) != QHostAddress::LocalHost &&
            ipAddressesList.at(i).toIPv4Address()) {
            ipAddress = ipAddressesList.at(i).toString();
            break;
        }
    }
    if (ipAddress.isEmpty())
        ipAddress = QHostAddress(QHostAddress::LocalHost).toString();
    return ipAddress;
}
