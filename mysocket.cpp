
#include "mysocket.h"
#include "SocketServer.h"
#include <QTcpSocket>
MySocket::MySocket( QObject *parent /* = NULL */ )
    : QTcpSocket( parent )
{
    connect( this, SIGNAL(readyRead()), this, SLOT(onReadyRead()) );
}

MySocket::~MySocket()
{
    printf( "~MySocket\n" );
    close();
}

void MySocket::onReadyRead()
{
    char data[1024] = { 0 };
    int len = readData( data, 1024 );
    if( len <= 0 ) {
        printf( "MySocket::OnReadyRead() read data failed !\n" );
        return;
    }

    printf( "receive data: %s\n", data );

    if( 0 >= writeData(data, len) )
        printf( "MySocket::OnReadyRead() write data failed !\n" );
    else
        printf( "send    data: %s\n", data );
}
