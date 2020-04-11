#ifndef MAINWINDOWORDUSER_H
#define MAINWINDOWORDUSER_H

#include <QMainWindow>
//#include "widgetrealtimechart.h"
#include "historydataanalyse.h"
#include "history_data_query.h"
#include "realtimedisplay.h"

namespace Ui {
class MainWindowOrdUser;
}

class MainWindowOrdUser : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindowOrdUser(QWidget *parent = 0);
    ~MainWindowOrdUser();
    void contextMenuEvent(QContextMenuEvent* event);
    void OrdWarnPrompt();//告警函数
signals:
    void my_signal_ord_history();
    void my_signal_ord_sta_data();
    void my_signal_ord_newest();
    void my_signal_ord_update(Data);
    void my_signal_send_orddata(Data);
private slots:
    void my_slots_ord_history();
    void my_slots_ord_sta_data();
    void my_slots_ord_newest();

    void on_ord_history_btn_clicked();

    void on_ord_sta_btn_clicked();

    void on_ord_newest_btn_clicked();
public slots:
    void recvData(Data data);

private:
    Ui::MainWindowOrdUser *ui;

    HistoryDataAnalyse* ordanl;
    History_Data_Query* ordquery;
    RealTimeDisplay* orddis;

    Data m_data;
};

#endif // MAINWINDOWORDUSER_H
