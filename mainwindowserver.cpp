#include "mainwindowserver.h"
#include "ui_mainwindowserver.h"
#include "somFun.h"
#include <QLabel>

MainWindowServer::MainWindowServer(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindowServer)
{

    ui->setupUi(this);

    connect(ui->serverWork, SIGNAL(clicked()), this, SLOT(serverConnect()));

}

void MainWindowServer::serverConnect()
{
    static bool flag = true;
    if (flag)
    {
        flag = !flag;
        ui->serverWork->setText("Disconnect");
        // make the text ineditable
        ui->PortUsed->setReadOnly(true);
        // looks like be ineditable
        GloPalette *pal = new GloPalette();
        ui->PortUsed->setPalette(*(pal->palette_base));

        // set the local ip address
        ui->IP_address->setText((getIPAddress()));
        // read the port and connect
        QString strPort;
        strPort.append(ui->PortUsed->toPlainText());
        bool flagTmp;
        int port = strPort.toInt(&flagTmp, 10);
        qDebug() << strPort;
        qDebug() << port;
        if (!flagTmp)
        {
            qDebug() << "Error for the wrong input of port!";
            qDebug() << "Failed to init server for the wrong port";
            return;
        }
        socketserver = new SocketServer(this, port);
    } else {
        flag = !flag;
        ui->serverWork->setText("Connect");
        // make the text editable
        ui->PortUsed->setReadOnly(false);

        // looks like be editable
        GloPalette *pal = new GloPalette();
        ui->PortUsed->setPalette(*(pal->palette_norm));

        delete socketserver;
    }


}

MainWindowServer::~MainWindowServer()
{
    delete ui;
}

