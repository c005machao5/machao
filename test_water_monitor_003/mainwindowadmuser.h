#ifndef MAINWINDOWADMUSER_H
#define MAINWINDOWADMUSER_H

#include <QMainWindow>
#include "historydataanalyse.h"
#include "history_data_query.h"
#include "realtimedisplay.h"



namespace Ui {
class MainWindowAdmUser;
}

class MainWindowAdmUser : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindowAdmUser(QWidget *parent = 0);
    ~MainWindowAdmUser();
     void contextMenuEvent(QContextMenuEvent* event);
     void WarnPrompt();//告警函数
     HistoryDataAnalyse* analyse;
     History_Data_Query* query;
     RealTimeDisplay* timedis;
     Data m_data;
signals:
    void my_signal_history();
    void my_signal_sta_data();
    void my_signal_newest();
    void my_signal_send_data(Data);
private slots:
    void my_slots_history();
    void my_slots_sta_data();
    void my_slots_newest();

    void on_adm_history_btn_clicked();

    void on_adm_sta_btn_clicked();

    void on_adm_newest_btn_clicked();
public slots:
    void recvData(Data);

private:
    Ui::MainWindowAdmUser *ui;


};

#endif // MAINWINDOWADMUSER_H
