#include "historydataanalyse.h"
#include "ui_historydataanalyse.h"
#include<QDebug>
HistoryDataAnalyse::HistoryDataAnalyse(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::HistoryDataAnalyse)
{
    ui->setupUi(this);
    clientsocket1.m_connect_socket("192.168.31.84",8888);
    //分析界面图
     m_show_bar_chart=new ShowBarChart;
     connect(this,QOverload<std::map<int,std::map<double,double>>,
     QStringList>::of(&HistoryDataAnalyse::my_bar_chart_show_signal),

     m_show_bar_chart,QOverload<std::map<int,std::map<double,double>>,
             QStringList>::of(&ShowBarChart::m_show_bar_chart_slot));
    ui->label_start_date->setGeometry(50,100,100,30);
    ui->comboBox_date_start_selection->setGeometry(150,100,100,30);

    ui->label_end_date->setGeometry(50,200,100,30);
    ui->comboBox_date_end_selection->setGeometry(150,200,100,30);

    ui->label_observe_well->setGeometry(50,300,100,30);
    ui->comboBox_observe_well_selection->setGeometry(150,300,140,30);

       ui->label_month->setGeometry(50,400,100,30);
        ui->comboBox_month->setGeometry(150,400,150,30);
    ui->btn_query->setGeometry(400,400,100,30);


    QStringList  str_start_date;
   str_start_date<<"2007"<<"2008"<<"2009"<<"2010"<<"2011"<<"2012"<<"2013";
   //将字符串列表绑定QCombeBox控件
   ui->comboBox_date_start_selection->addItems(str_start_date);
   QStringList  str_end_date;
  str_end_date<<"2007"<<"2008"<<"2009"<<"2010"<<"2011"<<"2012"<<"2013";
   ui->comboBox_date_end_selection->addItems(str_end_date);
    QStringList  str_well_name;
   str_well_name<<"observefirst"<<"observetwo"<<"observethree"<<"observefour";
   ui->comboBox_observe_well_selection->addItems(str_well_name);
   QStringList  str_month;
  str_month<<"1"<<"2"<<"3"<<"4"<<"5"<<"6"<<"7"<<"8"<<"9"<<"10"<<"11"<<"12";
  ui->comboBox_month->addItems(str_month);
}

HistoryDataAnalyse::~HistoryDataAnalyse()
{
    delete ui;
}

void HistoryDataAnalyse::on_btn_query_clicked()
{
    Data_Analysis  m_data_analysis(ui->comboBox_date_start_selection->currentText().toStdString().c_str(),
                                  ui->comboBox_date_end_selection->currentText().toStdString().c_str(),
                                   ui->comboBox_observe_well_selection->currentText().toStdString().c_str(),
                                   ui->comboBox_month->currentText().toStdString().c_str());
    std::map<int,std::map<double,double>>data_analysis;
    std::map<double,double>data_mapp;

     data_mapp.insert(std::pair<double,double>(-5,12));
     data_analysis.insert(std::pair<int,std::map<double,double>>(1,data_mapp));
     data_mapp.clear();
     data_mapp.insert(std::pair<double,double>(-19,20));
     data_analysis.insert(std::pair<int,std::map<double,double>>(2,data_mapp));
     data_mapp.clear();
     data_mapp.insert(std::pair<double,double>(-29,39));
     data_analysis.insert(std::pair<int,std::map<double,double>>(3,data_mapp));
     data_mapp.clear();
     data_mapp.insert(std::pair<double,double>(-15,30));
     data_analysis.insert(std::pair<int,std::map<double,double>>(4,data_mapp));
     data_mapp.clear();
     data_mapp.insert(std::pair<double,double>(-20,35));
     data_analysis.insert(std::pair<int,std::map<double,double>>(5,data_mapp));
     data_mapp.clear();
     data_mapp.insert(std::pair<double,double>(-32,40));
     data_analysis.insert(std::pair<int,std::map<double,double>>(6,data_mapp));
     data_mapp.clear();
     data_mapp.insert(std::pair<double,double>(-12,30));
     data_analysis.insert(std::pair<int,std::map<double,double>>(7,data_mapp));
     data_mapp.clear();
     data_mapp.insert(std::pair<double,double>(-1,20));
     data_analysis.insert(std::pair<int,std::map<double,double>>(8,data_mapp));
     data_mapp.clear();
     data_mapp.insert(std::pair<double,double>(-2,25));
     data_analysis.insert(std::pair<int,std::map<double,double>>(9,data_mapp));
     data_mapp.clear();

            clientsocket1.sendMSG(m_data_analysis);
 //socket  获取数据
     QStringList list={ui->comboBox_date_start_selection->currentText(),
                       ui->comboBox_date_end_selection->currentText()
                       ,ui->comboBox_month->currentText()};
     emit my_bar_chart_show_signal(data_analysis,list);
}
