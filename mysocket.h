#ifndef MYSOCKET_H
#define MYSOCKET_H
#include <QThread>
#include <QTcpSocket>


class MySocket : public QTcpSocket
{
    Q_OBJECT
public:
    explicit MySocket(QObject *parent = 0);

private slots:
    void readClient();

private:

    quint16 nextBlockSize;
};

#endif // MYSOCKET_H
