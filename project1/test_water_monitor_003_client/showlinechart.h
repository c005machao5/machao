#ifndef SHOWLINECHART_H
#define SHOWLINECHART_H

#include <QMainWindow>
#include <QChartView>
#include <QLineSeries>
#include <QMainWindow>
#include <QValueAxis>
QT_CHARTS_USE_NAMESPACE
namespace Ui {
class ShowLineChart;
}

class ShowLineChart : public QMainWindow
{
    Q_OBJECT

public:
    explicit ShowLineChart(QWidget *parent = 0);
    ~ShowLineChart();
public slots:
   void  m_show_line_chart_slot(std::map<int,double> data_map,QStringList list_selection);
private:
    Ui::ShowLineChart *ui;
    QLineSeries *series;
    QChart *chart;
    QChartView* chartView;
    QValueAxis* axisX;
    QValueAxis* axisY;
};

#endif // SHOWLINECHART_H
