#include "SocketServer.h"
#include <QHostAddress>
#include <QtWidgets>
#include <QtNetwork>
#include "tcpthread.h"

#include <stdlib.h>
SocketServer::SocketServer( QWidget *parent)
    : QDialog(parent), tcpServer(0), networkSession(0)
{
    statusLabel = new QLabel;
    quitButton = new QPushButton(tr("Quit"));
    quitButton->setAutoDefault(false);

    sendTest = new QPushButton(tr("sendTest"));
    sendTest->setAutoDefault(false);

    QNetworkConfigurationManager manager;
    if (manager.capabilities() & QNetworkConfigurationManager::NetworkSessionRequired) {
        // Get saved network configuration
        QSettings settings(QSettings::UserScope, QLatin1String("QtProject"));
        settings.beginGroup(QLatin1String("QtNetwork"));
        const QString id = settings.value(QLatin1String("DefaultNetworkConfiguration")).toString();
        settings.endGroup();

        // If the saved network configuration is not currently discovered use the system default
        QNetworkConfiguration config = manager.configurationFromIdentifier(id);
        if ((config.state() & QNetworkConfiguration::Discovered) !=
                QNetworkConfiguration::Discovered) {
            config = manager.defaultConfiguration();
        }

        networkSession = new QNetworkSession(config, this);
        connect(networkSession, SIGNAL(opened()), this, SLOT(sessionOpened()));

        statusLabel->setText(tr("Opening network session."));
        networkSession->open();
    } else {
        sessionOpened();
    }

    connect(quitButton, SIGNAL(clicked()), this, SLOT(close()));

    connect(sendTest, SIGNAL(clicked()), this, SLOT(confirmID()));

    //connect(tcpServer, SIGNAL(newConnection()), this, SLOT(confirmID()));


    QHBoxLayout *buttonLayout = new QHBoxLayout;
    buttonLayout->addStretch(1);
    buttonLayout->addWidget(quitButton);
    buttonLayout->addStretch(1);
    buttonLayout->addWidget(sendTest);
    buttonLayout->addStretch(1);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(statusLabel);
    mainLayout->addLayout(buttonLayout);
    setLayout(mainLayout);

    setWindowTitle(tr("Qt TCP Server"));
}


SocketServer::~SocketServer()
{

}

void SocketServer::incomingConnection  ( int handle )
{
    TcpThread *thread = new TcpThread(handle, this);
    //将线程结束信号与线程的deleteLater槽关联
    connect(thread, SIGNAL(finished()),
            thread, SLOT(deleteLater()));
    //关联相应的UI更新槽
    connect(thread,SIGNAL(bytesArrived(qint64,qint32,int)),
            this,SIGNAL(bytesArrived(qint64,qint32,int)));
    //QT的线程都是从start开始，调用run()函数
    thread->start();

}

void SocketServer::sessionOpened()
{
    // Save the used configuration
    if (networkSession) {
        QNetworkConfiguration config = networkSession->configuration();
        QString id;
        if (config.type() == QNetworkConfiguration::UserChoice)
            id = networkSession->sessionProperty(QLatin1String("UserChoiceConfiguration")).toString();
        else
            id = config.identifier();

        QSettings settings(QSettings::UserScope, QLatin1String("QtProject"));
        settings.beginGroup(QLatin1String("QtNetwork"));
        settings.setValue(QLatin1String("DefaultNetworkConfiguration"), id);
        settings.endGroup();
    }

    tcpServer = new QTcpServer(this);
    if (!tcpServer->listen(QHostAddress::Any, 9877)) {
        QMessageBox::critical(this, tr("Fortune Server"),
                              tr("Unable to start the server: %1.")
                              .arg(tcpServer->errorString()));
        close();
        return;
    }

    QString ipAddress;
    QList<QHostAddress> ipAddressesList = QNetworkInterface::allAddresses();
    // use the first non-localhost IPv4 address
    for (int i = 0; i < ipAddressesList.size(); ++i) {
        if (ipAddressesList.at(i) != QHostAddress::LocalHost &&
                ipAddressesList.at(i).toIPv4Address()) {
            ipAddress = ipAddressesList.at(i).toString();
            break;
        }
    }
    // if we did not find one, use IPv4 localhost
    if (ipAddress.isEmpty())
        ipAddress = QHostAddress(QHostAddress::LocalHost).toString();
    statusLabel->setText(tr("The server is running on\n\nIP: %1\nport: %2\n\n"
                            "Run the Qt TCP Client now.\n\n\n")
                         .arg(ipAddress).arg(tcpServer->serverPort()));
}


void SocketServer::confirmID()
{

    QString infoToConfirm;
    infoToConfirm = tr("This is a test!\n");

    QTcpSocket *clientConnection = tcpServer->nextPendingConnection();

    sendString(infoToConfirm, clientConnection);


    //clientConnection->disconnectFromHost();

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
