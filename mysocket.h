#ifndef MYSOCKET_H
#define MYSOCKET_H
#include <QThread>
#include <QTcpSocket>


class MySocket : public QTcpSocket
{
    Q_OBJECT
public:
    explicit MySocket(QObject *parent = 0);
    ~MySocket   ();

signals:

public slots:
    void onReadyRead ();

};

#endif // MYSOCKET_H
