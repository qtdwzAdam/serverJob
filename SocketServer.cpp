#include "SocketServer.h"
#include <QHostAddress>
#include <QtWidgets>
#include <QtNetwork>
#include "tcpthread.h"

#include <stdlib.h>
SocketServer::SocketServer(QObject *parent, int port)
    : QTcpServer(parent)
{
    if (!listen(QHostAddress::Any, port)) {
        qDebug() << "Error in listen of SocketServer!!";
        close();
        return;
    }
    //connect(tcpServer, SIGNAL(newConnection()), this, SLOT(justToCall()));
    qDebug()<<"End of the init to SocketServer!!";
}

SocketServer::~SocketServer()
{
    qDebug()<<"End of the ~SocketServer!!";

}



void SocketServer::incomingConnection  ( int socketDescriptor )
{
    qDebug()<<"A new connection is comming!!";
    TcpThread *thread = new TcpThread(socketDescriptor, this);
    //将线程结束信号与线程的deleteLater槽关联
    connect(thread, SIGNAL(finished()),
            thread, SLOT(deleteLater()));
    //关联相应的UI更新槽
    connect(thread,SIGNAL(bytesArrived(qint64,qint32,int)),
            this,SIGNAL(bytesArrived(qint64,qint32,int)));
    //QT的线程都是从start开始，调用run()函数
    thread->run();

}

void SocketServer::confirmID()
{

    QString infoToConfirm;
    infoToConfirm = tr("This is a test!\n");

    QTcpSocket *clientConnection = nextPendingConnection();

    sendString(infoToConfirm, clientConnection);

    //clientConnection->disconnectFromHost();

}

void SocketServer::sendout()
{
    QString infoToConfirm;
    infoToConfirm = tr("This is a test!\n");


}

void SocketServer::sendString(QString str, QTcpSocket *clientConnection)
{
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_3);

    out << (quint16)0;
    out << str;
    out.device()->seek(0);
    out << (quint16)(block.size() - sizeof(quint16));

    clientConnection->write(block);
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
