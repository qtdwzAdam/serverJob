#include "mainwindowserver.h"
#include "ui_mainwindowserver.h"

#include "SocketServer.h"
#include <QLabel>

MainWindowServer::MainWindowServer(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindowServer)
{
    ChatServer tt;

    ui->setupUi(this);
    ui->portSetting_2->setText(getIPAddress());

    ui->result123->setText("Start to run Run");

    //QTcpServer newserver;
    //newserver.listen(QHostAddress::Any, 9867);

    ChatServer server;
    server.Run(9877);
    ui->result1->setText("end of the run");
    connect(ui->pushButton,SIGNAL(clicked()), this, SLOT(close()));
}

MainWindowServer::~MainWindowServer()
{
    delete ui;
}

