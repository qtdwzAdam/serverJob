
#include "mysocket.h"
#include "SocketServer.h"
#include <QTcpSocket>
#include <QDataStream>
MySocket::MySocket( QObject *parent /* = NULL */ )
    : QTcpSocket( parent )
{
    connect( this, SIGNAL(readyRead()), this, SLOT(readClient()) );
    connect( this, SIGNAL(disconnected()), this, SLOT(deleteLater()) );
    nextBlockSize = 0;
}

void MySocket::readClient()
{
    QDataStream in(this);
    in.setVersion(QDataStream::Qt_5_3);
    if (nextBlockSize == 0){
        if( bytesAvailable() < sizeof(quint16))
            return;
        in >> nextBlockSize;
    }
    if (bytesAvailable() < nextBlockSize)
        return;
    QString requestType;
    in >> requestType;
    printf("%s\n", requestType);
}
