#include "mainwindowserver.h"
#include <QApplication>
#include <QtCore/QCoreApplication>
#include "SocketServer.h"
using namespace std;
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //MainWindowServer w;
    //w.show();
    SocketServer server;
    server.show();
    return a.exec();
}
