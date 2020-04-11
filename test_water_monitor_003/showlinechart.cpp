#include "showlinechart.h"
#include "ui_showlinechart.h"
#include<QCategoryAxis>
#include<QDebug>

ShowLineChart::ShowLineChart(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ShowLineChart)
{
    ui->setupUi(this);

}

ShowLineChart::~ShowLineChart()
{
    delete ui;
}
void ShowLineChart::m_show_line_chart_slot(std::map<int,double> data_map,QStringList list_selection)
{
    series=new QLineSeries();//实例化一个QLineSeries对象
    int x_max=0; //横坐标最大值
    QCategoryAxis*axisX=new QCategoryAxis;
    for(std::map<int,double>::iterator it=data_map.begin();it!=data_map.end();++it)
    {

        series->append(it->first,it->second);//添加坐标点
        auto its=it;
        if((++its)==data_map.end())
        {
            x_max=it->first;
        }
    }
    if(list_selection[0]=="bymonth")
    {
        axisX->setMin(0);
            axisX->setMax(x_max);
            axisX->setStartValue(0);

            for(int i=1;i<=x_max;++i)
            {
                QString str=QString::number(i);
                str.append("月");
                axisX->append(str,i);
            }


    }

    if(list_selection[0]=="byday")
    {
        axisX->setMin(0);
            axisX->setMax(x_max);
            axisX->setStartValue(0);
            for(int i=1;i<=x_max;++i)
            {
                QString str=QString::number(i);
                str.append("日");
                axisX->append(str,i);
            }

    }
    if(list_selection[0]=="byhour")
    {

            axisX->setMin(0);
            axisX->setMax(x_max);
            axisX->setStartValue(0);
            for(int i=1;i<=x_max;++i)
            {
                QString str=QString::number(i,10);
                str.append("小时");
                axisX->append(str,i);
            }
    }
    chart=new QChart();
     chart->addSeries(series);//添加系列到QChart
    series->setUseOpenGL(true);
           //下边这一句代码的作用是让刻度线和刻度的label对齐
           axisX->setLabelsPosition(QCategoryAxis::AxisLabelsPositionOnValue);

    chart->createDefaultAxes();//创建默认轴
    if(list_selection[0]=="bymonth")
    {
         chart->setTitle("按月查询结果");//设置标题
    }
    else if(list_selection[0]=="byday")
    {
        chart->setTitle("按天查询结果");//设置标题
    }
    else
    {
         chart->setTitle("按小时查询结果");//设置标题
    }

    chartView=new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->resize(1000,300);
   // axisX=new QValueAxis;
    if(list_selection[0]=="bymonth")
    {
         chart->setTitle("按月查询结果");
    }
    else if(list_selection[0]=="byday")
    {
        chart->setTitle("按天查询结果");
    }
    else
    {
         chart->setTitle("按小时查询结果");
    }
    axisX->setTitleText("时间");
    axisY=new QValueAxis;

    axisY->setTickCount(18);
     axisY->setRange(-20,20);
     axisY->setLabelFormat("%d");

     if(list_selection[1]=="water_level")
     {
         axisY->setTitleText("水位最大值 单位：米");
     }
     else
     {
         axisY->setTitleText("水埋深最大值 单位：米");
     }

    chart->setAxisX(axisX,series);
    chart->setAxisY(axisY,series);
    chartView->show();
    this->hide();
}
