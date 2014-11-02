#include "mainwindowserver.h"
#include "ui_mainwindowserver.h"

MainWindowServer::MainWindowServer(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindowServer)
{
    ui->setupUi(this);
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
