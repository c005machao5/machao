#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <fileclientsocket.h>
#include <thread>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void recvThread();//收包线程
    void sendThread(char * buf,int len,int number);

private slots:
    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    FileclientSocket* client;
};

#endif // MAINWINDOW_H
