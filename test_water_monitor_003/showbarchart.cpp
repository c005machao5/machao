#include "showbarchart.h"
#include "ui_showbarchart.h"

ShowBarChart::ShowBarChart(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ShowBarChart)
{
    ui->setupUi(this);
}

ShowBarChart::~ShowBarChart()
{
    delete ui;
}
void ShowBarChart::m_show_bar_chart_slot(std::map<int,std::map<double,double>>data_analysis,QStringList list)
{
    low=new QBarSet("min");
    high=new QBarSet("max");
    for(std::map<int,std::map<double,double>>\
        ::iterator iter=data_analysis.begin();iter!=data_analysis.end();++iter)
    {

        for(std::map<double,double>::iterator its=iter->second.begin();\
            its!=iter->second.end();++its)
        {
            *low<<its->first;
            *high<<its->second;
        }
    }
    series=new QStackedBarSeries();
    series->append(low);
    series->append(high);
    chart=new QChart();
  //  chart->legend()->hide();
    chart->addSeries(series);
    chart->setTitle("单观测井多年同月水位分析图");
    chart->setAnimationOptions(QChart::SeriesAnimations);
    QStringList categories;
    bool ok;
    for(int i=list[0].toInt(&ok,10);i<=list[1].toInt(&ok,10);++i )
    {
        QString str=QString::number(i);
        str.append("年");
        str.append(list[2]);
        str.append("月");
        categories<<str;
    }
    axis=new QBarCategoryAxis();
    axis->append(categories);
    axis->setTitleText("时间");
    chart->createDefaultAxes();
    chart->setAxisX(axis,series);
    chart->axisY(series)->setRange(-52,52);
    chart->axisY(series)->setTitleText("地下水水位值 单位:米");
    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignBottom);
    chartView=new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->resize(500,400);
    chartView->show();

}
