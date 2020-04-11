#ifndef SHOWBARCHART_H
#define SHOWBARCHART_H

#include <QMainWindow>
#include<QChart>
#include <QBarSet>
#include<QStackedBarSeries>
#include<QBarCategoryAxis>
#include<QChartView>
QT_CHARTS_USE_NAMESPACE
namespace Ui {
class ShowBarChart;
}

class ShowBarChart : public QMainWindow
{
    Q_OBJECT

public:
    explicit ShowBarChart(QWidget *parent = 0);
    ~ShowBarChart();

private:
    Ui::ShowBarChart *ui;

    QBarSet* low;
    QBarSet* high;
    QStackedBarSeries* series;
    QChart* chart;
    QBarCategoryAxis *axis;
     QChartView* chartView;
public:
    void m_show_bar_chart_slot(std::map<int,std::map<double,double>>data_analysis,QStringList list);
};

#endif // SHOWBARCHART_H
