#ifndef HISTORY_DATA_QUERY_H
#define HISTORY_DATA_QUERY_H

#include <QMainWindow>
#include "showtable.h"
#include "showlinechart.h"
#include<clientsocket.h>

namespace Ui {
class History_Data_Query;
}

class History_Data_Query : public QMainWindow
{
    Q_OBJECT

public:
    explicit History_Data_Query(QWidget *parent = 0);
    ~History_Data_Query();

private slots:


    void on_btn_line_chart_show_query_clicked();
    void on_btn_table_show_query_clicked();

signals:
    void my_table_show_signal(std::map<int,double> data_map,QStringList list_selection);
    void my_line_chart_show_signal(std::map<int,double> data_map,QStringList list_selection);

private:
    Ui::History_Data_Query *ui;
    ShowTable* m_table_show;
    ShowLineChart* m_line_chart_show;
    struct Data_Selection m_data_selection;
    ClientSocket clientsocket;
};

#endif // HISTORY_DATA_QUERY_H
