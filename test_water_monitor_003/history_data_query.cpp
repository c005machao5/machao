#include "history_data_query.h"
#include "ui_history_data_query.h"
#include<QDebug>


History_Data_Query::History_Data_Query(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::History_Data_Query)
{
    ui->setupUi(this);
    m_table_show=new ShowTable;
    m_line_chart_show=new ShowLineChart;
    bool ok;
        ok= clientsocket.m_connect_socket("192.168.31.84",8888);
        qDebug()<<ok<<endl;


    connect(this,QOverload<std::map<int,double>,QStringList>::of(&History_Data_Query::my_line_chart_show_signal),m_line_chart_show,QOverload<std::map<int,double>,QStringList>::of(&ShowLineChart::m_show_line_chart_slot));
    //connect(this,QOverload<>::of(&History_Data_Query::my_table_show_signal),m_table_show,QOverload<>::of(&ShowTable::m_show_table_slot));
    connect(this,QOverload<std::map<int,double>,QStringList>::of(&History_Data_Query::my_table_show_signal),m_table_show,QOverload<std::map<int,double>,QStringList>::of(&ShowTable::m_show_table_slot));
    ui->label_date_type->setGeometry(50,100,100,30);
    ui->comboBox_date_type_selection->setGeometry(150,100,100,30);

    ui->label_oberve_well->setGeometry(50,200,100,30);
    ui->comboBox_observe_well_selection->setGeometry(150,200,100,30);

    ui->label_observe_type->setGeometry(50,300,100,30);
    ui->comboBox_observe_type_selection->setGeometry(150,300,140,30);

    ui->label_date->setGeometry(50,400,100,30);
    ui->lineEdit_input_date->setGeometry(150,400,150,30);
    ui->btn_table_show_query->setGeometry(400,400,100,30);
    ui->btn_line_chart_show_query->setGeometry(550,400,100,30);
        QStringList  str_date_type;
       str_date_type<<"bymonth"<<"byday"<<"byhour";
      // 将字符串列表绑定QCombeBox控件
       ui->comboBox_date_type_selection->addItems(str_date_type);
       QStringList  str_oberve_type;
      str_oberve_type<<"water_level"<<"water_depth";
       ui->comboBox_observe_type_selection->addItems(str_oberve_type);
        QStringList  str_well_name;
       str_well_name<<"observefirst"<<"observetwo"<<"observethree"<<"observefour";
       ui->comboBox_observe_well_selection->addItems(str_well_name);
    m_table_show=new ShowTable;
    m_line_chart_show=new ShowLineChart;
}

History_Data_Query::~History_Data_Query()
{
    delete ui;
}



void History_Data_Query::on_btn_line_chart_show_query_clicked()
{

    Data_Selection m_data_selection(ui->comboBox_date_type_selection->currentText().toStdString().c_str(),
                                ui->comboBox_observe_well_selection->currentText().toStdString().c_str(),
                                ui->comboBox_observe_type_selection->currentText().toStdString().c_str(),
                                ui->lineEdit_input_date->text().toStdString().c_str());

     clientsocket.sendMSG(m_data_selection);//发送数据

     std::map<int,double>data_map;
     data_map.insert(std::pair<int,double>(1,2));
     data_map.insert(std::pair<int,double>(2,8));
     data_map.insert(std::pair<int,double>(3,19));
     data_map.insert(std::pair<int,double>(4,12));
     data_map.insert(std::pair<int,double>(5,0));
     data_map.insert(std::pair<int,double>(6,4));
     data_map.insert(std::pair<int,double>(7,-2));
     data_map.insert(std::pair<int,double>(8,-5));
     data_map.insert(std::pair<int,double>(9,-9));
     data_map.insert(std::pair<int,double>(10,-5));
      data_map.insert(std::pair<int,double>(11,-8));
       data_map.insert(std::pair<int,double>(12,-12));
       data_map.insert(std::pair<int,double>(13,8));
     QStringList list_selection;
     list_selection<<ui->comboBox_date_type_selection->currentText()
                  <<ui->comboBox_observe_type_selection->currentText();
     emit my_line_chart_show_signal(data_map,list_selection);
}

void History_Data_Query::on_btn_table_show_query_clicked()
{

//    qDebug()<<ui->comboBox_date_type_selection->currentText()<<endl;
//    qDebug()<<ui->comboBox_observe_well_selection->currentText()<<endl;
//     qDebug()<<ui->comboBox_observe_type_selection->currentText()<<endl;
//     qDebug()<<ui->lineEdit_input_date->text()<<endl;
     //socket  获取数据
    Data_Selection m_data_selection(ui->comboBox_date_type_selection->currentText().toStdString().c_str(),
                                ui->comboBox_observe_well_selection->currentText().toStdString().c_str(),
                                ui->comboBox_observe_type_selection->currentText().toStdString().c_str(),
                                ui->lineEdit_input_date->text().toStdString().c_str());

     clientsocket.sendMSG(m_data_selection);//发送数据

     std::map<int,double>data_map;
     data_map.insert(std::pair<int,double>(1,2));
     data_map.insert(std::pair<int,double>(2,8));
     data_map.insert(std::pair<int,double>(3,19));
     data_map.insert(std::pair<int,double>(4,12));
     data_map.insert(std::pair<int,double>(5,0));
     data_map.insert(std::pair<int,double>(6,4));
     data_map.insert(std::pair<int,double>(7,-2));
     data_map.insert(std::pair<int,double>(8,-5));
     data_map.insert(std::pair<int,double>(9,-9));
     data_map.insert(std::pair<int,double>(10,-5));
      data_map.insert(std::pair<int,double>(11,-8));
       data_map.insert(std::pair<int,double>(12,-12));
       data_map.insert(std::pair<int,double>(13,8));
     QStringList list_selection;
     list_selection<<ui->comboBox_date_type_selection->currentText()
                  <<ui->comboBox_observe_type_selection->currentText();
     emit my_table_show_signal(data_map,list_selection);
}
