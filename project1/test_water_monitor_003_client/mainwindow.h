#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "mainwindowreg.h"
#include "mainwindowadmuser.h"
#include "mainwindoworduser.h"
#include "clientsocket.h"
#include "signal_s.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void SendLogInfo(LoginInfo& logud);
    void RecvLogInfo();

private:
    Ui::MainWindow *ui;
    MainWindowReg* reg;
    MainWindowAdmUser* admuser;
    MainWindowOrdUser* orduser;
    ClientSocket* logclient;
    LoginInfo sendlogdata;
    LoginInfo recvlogdata;
    signal_s * sig;

signals:
    void my_signal_main_reg();
    void my_signal_main_confirmlog();
private slots:
    void my_slots_main_reg();
    void my_slots_reg_back();
    void my_slots_main_confirmlog();
    void my_slots_logrecv();

    void on_main_confirmlog_btn_clicked();
    void on_main_reg_btn_clicked();
};

#endif // MAINWINDOW_H
