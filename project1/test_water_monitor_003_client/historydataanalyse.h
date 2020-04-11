#ifndef HISTORYDATAANALYSE_H
#define HISTORYDATAANALYSE_H
#include "showbarchart.h"
#include <QMainWindow>
#include "clientsocket.h"
namespace Ui {
class HistoryDataAnalyse;
}

class HistoryDataAnalyse : public QMainWindow
{
    Q_OBJECT

public:
    explicit HistoryDataAnalyse(QWidget *parent = 0);
    ~HistoryDataAnalyse();

private slots:
    void on_btn_query_clicked();

private:
    Ui::HistoryDataAnalyse *ui;
    ShowBarChart* m_show_bar_chart;
    struct Data_Analysis  m_data_analysis;
    ClientSocket clientsocket1;
signals:
    void my_bar_chart_show_signal(std::map<int,std::map<double,double>>data_analysis,QStringList list);

};

#endif // HISTORYDATAANALYSE_H
