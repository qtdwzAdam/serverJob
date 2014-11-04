#include "mainwindowserver.h"
#include <QApplication>
#include <QtCore/QCoreApplication>
using namespace std;
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindowServer w;
    w.show();
    return a.exec();
}
