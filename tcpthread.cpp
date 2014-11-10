#include "tcpthread.h"
#include <QtGui>
#include <QApplication>
#include <QtNetwork>

TcpThread::TcpThread(int socketDescriptor,QObject *parent):
    QThread(parent),socketDescriptor(socketDescriptor)
{
    //bytesReceived=0;

    //QObject::connect(this, SIGNAL(receiveSgl(QTcpSocket*)), &obj, SLOT(slot(QTcpSocket*)));
}

TcpThread::~TcpThread()
{

    quit();
    wait();
    deleteLater();

    qDebug() << "Delete the TcpThread";
}
void TcpThread::run()
{

    Object obj2(socketDescriptor);
    obj2.moveToThread(this);

    QObject::connect(&obj2,SIGNAL(bytesArrived(qint64,qint32,QByteArray,int)),
                     this,SIGNAL(bytesArrived(qint64,qint32,QByteArray,int)),

                     Qt::BlockingQueuedConnection);//接收数据

    //    qDebug()<<socketDescriptor;
    // //这是重中之重，必须加Qt::BlockingQueuedConnection！
    //这里困扰了我好几天，原因就在与开始没加，默认用的Qt::AutoConnection。
    //简单介绍一下QT信号与槽的连接方式：
    //Qt::AutoConnection表示系统自动选择相应的连接方式，如果信号与槽在同一线程，就采用Qt::DirectConnection，
    //如果信号与槽不在同一线程，将采用Qt::QueuedConnection的连接方式。
    //Qt::DirectConnection表示一旦信号产生，立即执行槽函数。
    //Qt::QueuedConnection表示信号产生后，将发送Event给你的receiver所在的线程，postEvent(QEvent::MetaCall,...)，
    //slot函数会在receiver所在的线程的event loop中进行处理。
    //Qt::BlockingQueuedConnection表示信号产生后调用sendEvent(QEvent::MetaCall,...),
    //在receiver所在的线程处理完成后才会返回;只能当sender,receiver不在同一线程时才可以。
    //Qt::UniqueConnection表示只有它不是一个重复连接，连接才会成功。如果之前已经有了一个链接（相同的信号连接到同一对象的同一个槽上），那么连接将会失败并将返回false。
    //Qt::AutoCompatConnection与QT3保持兼容性
    //说明一下，对于任何的QThread来说，其线程只存在于run()函数内，其它的函数都不在线程内，所以此处要采用Qt::BlockingQueuedConnection，
    //因为当SOCKET有数据到达时就会发出readyRead()信号，但是此时可能之前的receiveFile()还未执行完毕，之前使用的Qt::AutoConnection，
    //结果传输大文件的时候就会出错，原因就在于只要有数据到达的时候，就会连接信号，但是数据接收还没处理完毕，而Qt::BlockingQueuedConnection会阻塞
    //此连接，直到receiveFile()处理完毕并返回后才发送信号。
    //connect(tcpSocket,SIGNAL(readyRead()),this,SIGNAL(receiveSgl(tcpSocket)));
    //    connect(tcpSocket,SIGNAL(readyRead()),this,SLOT(receiveFile()),Qt::BlockingQueuedConnection);

    qDebug() << "run thread:" << QThread::currentThreadId();
    exec();
}
void Object::sendString(QString str)
{
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_3);

    out << (quint16)0;
    out << str;
    out.device()->seek(0);
    out << (quint16)(block.size() - sizeof(quint16));

    tcpSocket->write(block);
}

// Object class setting!
Object::Object(int socketDescriptor):socketDescriptor(socketDescriptor)
{
    tcpSocket=new QTcpSocket;
    bytesReceived=0;
    if(!tcpSocket->setSocketDescriptor(socketDescriptor)){
        emit error(tcpSocket->error());
        return;
    }

    qDebug()<<socketDescriptor;
    QObject::connect(tcpSocket,SIGNAL(readyRead()),
                     this,SLOT(receiveString()));
}
Object::~Object()
{
    tcpSocket->~QTcpSocket();
}

void Object::receiveString()
{
    byteToRead = tcpSocket->bytesAvailable();
    received = tcpSocket->readAll();
    qDebug() << "The received is: " << received;
    QString test = "For Fun!";
    sendString(test);
}

void Object::receiveFile()
{
    qDebug() << "obj thread:" << QThread::currentThreadId();
    QDataStream in(tcpSocket);
    if (bytesReceived < sizeof(qint32))
    {
        if (tcpSocket->bytesAvailable() >= sizeof(qint32))
        {
            in.setByteOrder(QDataStream::LittleEndian);//linux系统是大端
            in >> TotalBytes;
            TotalBytes += 4;
            qDebug() << TotalBytes;

            bytesReceived += sizeof(qint32);
            fileNameIp = tcpSocket->peerAddress();
            quint16 port = tcpSocket->peerPort();
            localFile = new QFile(fileNameIp.toString()+(tr(".%1").arg(port))) ;
            if (!localFile->open(QFile::WriteOnly))
            {
                qDebug() << "Error in localFile->open !";
            }
        }
    }
    if(bytesReceived < TotalBytes){
        byteToRead = tcpSocket->bytesAvailable();
        bytesReceived += byteToRead;
        inBlock = tcpSocket->readAll();
        qDebug() << "BytesReceived is :"<<bytesReceived;
        qDebug() << inBlock;    //  the received info
        localFile->write(inBlock);
        inBlock.resize(0);
    }
    emit bytesArrived(bytesReceived,TotalBytes,inBlock, socketDescriptor);
    if(bytesReceived == TotalBytes){
        localFile->close();
        qDebug() << bytesReceived;
        //emit TcpThread::finished();
        QApplication::restoreOverrideCursor();
    }

    QString test = "For Fun!";
    sendString(test);
}
