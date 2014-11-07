#include "mainwindowserver.h"
#include "ui_mainwindowserver.h"

#include <QLabel>

MainWindowServer::MainWindowServer(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindowServer)
{
/*
    QHBoxLayout *topLeftLayout = new QHBoxLayout;
    topLeftLayout->addWidget(label);
    topLeftLayout->addWidget(caseCheckBox);

    QVBoxLayout *leftLayout = new QVBoxLayout;
    leftLayout->addLayout(topLeftLayout);
    leftLayout->addWidget(closeButton);

    */



    socketserver = new SocketServer(this, 9877);

    ui->setupUi(this);
    ui->IP_address->setText((getIPAddress()));

    QString str;
     str.append(ui->PortUsed->toPlainText());
    qDebug() <<str;

    ui->result123->setText("Start to run Run");

    //QTcpServer newserver;
    //newserver.listen(QHostAddress::Any, 9867);

    ui->result1->setText("end of the run");

    //setWindowTitle(tr("Test-dwz-main"));
    //setFixedHeight(sizeHint().height());
}

MainWindowServer::~MainWindowServer()
{
    delete ui;
}

