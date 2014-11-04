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

    ui->result123->setText("Start to run Run");
    ChatServer server;
    server.Run(9877);
    ui->result1->setText("end of the run");
    connect(ui->pushButton,SIGNAL(clicked()), this, SLOT(close()));
}

MainWindowServer::~MainWindowServer()
{
    delete ui;
}

void MainWindowServer::on_textBrowser_2_destroyed()
{

}

void MainWindowServer::on_portSettingTxt_textChanged()
{
    static int flag = 1;
    if(flag){
        printf("dfsdfsd");
    }
}
