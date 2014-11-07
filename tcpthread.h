#ifndef TCPTHREAD_H
#define TCPTHREAD_H

#include <QThread>
#include <QTcpSocket>
#include <QtNetwork>

class  QFile;
class QTcpSocket;


class TcpThread : public QThread
{
    Q_OBJECT
public:
    explicit TcpThread(int handle, QObject *parent);
    void run();

signals:
    void error(QTcpSocket::SocketError socketError);
    void bytesArrived(qint64, qint32, int);

public slots:
    void receiveFile();

private:
    int handle;
    qint64 bytesReceived;   // all bytes received
    qint64 byteToRead;      // ready to read such bytes
    qint32 TotalBytes;      // all to transfer
    QTcpSocket *tcpSocket;
    QHostAddress fileName;
    QFile *localFile;
    QByteArray inBlock;

};

#endif // TCPTHREAD_H
