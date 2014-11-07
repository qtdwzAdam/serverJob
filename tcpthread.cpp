#include "tcpthread.h"
#include <QtGui>
#include <QtNetwork>
#include <QApplication>

TcpThread::TcpThread(int handle, QObject *parent) :
    QThread(parent), handle(handle)
{
    bytesReceived = 0;
}

void TcpThread::run()
{
    tcpSocket = new QTcpSocket;
    if(!tcpSocket->setSocketDescriptor(handle))
    {
        emit error(tcpSocket->error());
        return;
    }
    qDebug() << handle;
    connect(tcpSocket, SIGNAL(readyRead()),
            this, SLOT(receiveFile()), Qt::BlockingQueuedConnection);
    exec();
}

void TcpThread::receiveFile()
{
    //将tcpsocket封装到QDataStream里，便于使用操作符>>
    QDataStream in(tcpSocket);
    if(bytesReceived < sizeof(qint32))
    {
        //先接收32bit的文件大小
        if(tcpSocket->bytesAvailable() >= sizeof(qint32))
        {
            in.setByteOrder(QDataStream::LittleEndian); //必须的,因为发送端为LINUX系统
            in>>TotalBytes;
            TotalBytes += 4;
            qDebug()<<TotalBytes;

            bytesReceived += sizeof(qint32);
            fileName = tcpSocket->peerAddress();
            quint16 port = tcpSocket->peerPort();
            localFile = new QFile(fileName.toString()+(tr(".%1").arg(port))); //用户端的IP地址作为保存文件名
            if (!localFile->open(QFile::WriteOnly ))

            {
            }
        }
    }
    //如果读取的文件小于文件大小就继续读
    if (bytesReceived < TotalBytes){
        byteToRead = tcpSocket->bytesAvailable();
        bytesReceived += byteToRead;
        inBlock = tcpSocket->readAll();
        qDebug()<<"bytesReceived is:"<<bytesReceived;
        localFile->write(inBlock);
        inBlock.resize(0);
    }
    emit bytesArrived(bytesReceived,TotalBytes,handle);
    if (bytesReceived == TotalBytes) {
        localFile->close();
        qDebug()<<bytesReceived;
        //emit finished();
        QApplication::restoreOverrideCursor();
    }
}
