#include "SocketServer.h"
#include <QHostAddress>
#include <QMessageBox>
#include <QtWidgets>
#include <QtNetwork>
#include "tcpthread.h"

#include <stdlib.h>
SocketServer::SocketServer(QObject *parent, int port)
    : QTcpServer(parent)
{
    // Auto to listen to a port.
    while(!isListening()&&!listen(QHostAddress::Any,port))
    {
        qDebug() << "Error in listen of SocketServer!";
        close();
        return;
    }

    qDebug()<<"start the init to SocketServer!!";
}

void SocketServer::incomingConnection  ( int socketDescriptor )
{
    qDebug()<<"A new connection is comming!!";
    TcpThread *thread = new TcpThread(socketDescriptor, this);
    //将线程结束信号与线程的deleteLater槽关联
    connect(this, SIGNAL(destroyed()), thread, SLOT(deleteLater()));
    connect(thread, SIGNAL(finished()),
            thread, SLOT(deleteLater()));
    //关联相应的UI更新槽
    connect(thread,SIGNAL(bytesArrived(qint64,qint32,QByteArray,int)),
            this,SIGNAL(bytesArrived(qint64,qint32,QByteArray,int)));
    //QT的线程都是从start开始，调用run()函数
    thread->start();
    qDebug() << "The thread to handle TCP is starting!!";

}
