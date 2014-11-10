#ifndef TCPTHREAD_H
#define TCPTHREAD_H

#include <QThread>
#include <QTcpSocket>
#include <QtNetwork>
class QFile;
class QTcpSocket;

class TcpThread:public QThread
{
    Q_OBJECT
public:
    TcpThread(int socketDescriptor,QObject *parent);
    ~TcpThread();
    void run();

public slots:
    //void receiveFile();
signals:
    void bytesArrived(qint64,qint32,QByteArray,int);
private:
    int socketDescriptor;

};

class Object:public QObject {
    Q_OBJECT
public:
    Object  (int socketDescriptor);
    ~Object ();

    void    sendString(QString str);

signals:
    void error(QTcpSocket::SocketError socketError);
    void bytesArrived(qint64,qint32,QByteArray,int);
    void receiveSgl(QTcpSocket*);

public slots:
    void receiveFile();
    void receiveString();

private:
    QTcpSocket      *tcpSocket;
    int     socketDescriptor;
    qint64  bytesReceived;
    qint64  byteToRead;
    qint32  TotalBytes;
    QFile   *localFile;
    QHostAddress    fileNameIp;//文件名Ip部分
    QByteArray      inBlock;//读取缓存
    QByteArray      received;
};


#endif // TCPTHREAD_H
