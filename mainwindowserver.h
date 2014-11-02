#ifndef MAINWINDOWSERVER_H
#define MAINWINDOWSERVER_H

#include <QMainWindow>

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
    void on_textBrowser_2_destroyed();

    void on_portSettingTxt_textChanged();

private:
    Ui::MainWindowServer *ui;
};

#endif // MAINWINDOWSERVER_H
