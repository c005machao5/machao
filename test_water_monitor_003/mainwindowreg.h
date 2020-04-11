#ifndef MAINWINDOWREG_H
#define MAINWINDOWREG_H

#include <QMainWindow>
#include "mainwindowreg.h"
#include "clientsocket.h"
#include "signal_s.h"
namespace Ui {
class MainWindowReg;
}

class MainWindowReg : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindowReg(QWidget *parent = 0);
    ~MainWindowReg();
    void SendRegInfo(UserData& ud);
    void RecvRegInfo();
signals:
    void my_signal_reg_commit();
    void my_signal_reg_back();

private slots:
    void my_slots_reg_commit();
    void my_recv_slots(UserData reuserdata);


    void on_reg_commit_btn_clicked();

    void on_reg_back_btn_clicked();

private:
    Ui::MainWindowReg *ui;
    UserData userdata;//发
    UserData reuserdata;//收
    ClientSocket* client;
    signal_s *sig;
};

#endif // MAINWINDOWREG_H
