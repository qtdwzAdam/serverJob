#ifndef MAINWINDOWSERVER_H
#define MAINWINDOWSERVER_H

#include <QMainWindow>
#include <QLabel>
#include <QLineEdit>
#include <QCheckBox>
#include <QPushButton>
#include "SocketServer.h"
namespace Ui {
class MainWindowServer;
}

class MainWindowServer : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindowServer(QWidget *parent = 0);
    ~MainWindowServer();

private slots:


private:
    Ui::MainWindowServer *ui;
    QLabel          *label;
    QLineEdit       *caseCheckBox;
    QCheckBox       *backwardCheckbox;
    QPushButton     *closeButton;

    SocketServer * socketserver;
    int port;

};

#endif // MAINWINDOWSERVER_H
