#include "showtable.h"
#include "ui_showtable.h"
#include<QDebug>
ShowTable::ShowTable(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ShowTable)
{
    ui->setupUi(this);
}

ShowTable::~ShowTable()
{
    delete ui;
}
void ShowTable::m_show_table_slot(std::map<int,double> data_map,QStringList list_selection)
{
    ui->tableWidget_history_data->setColumnCount(data_map.size());
    ui->tableWidget_history_data->setRowCount(1);
    ui->tableWidget_history_data->setGeometry(50,50,1000,150);
    QStringList column_header;
    int column=0;
    for(std::map<int,double>::iterator it=data_map.begin();it!=data_map.end();++it)
    {
        column_header<<std::to_string(it->first).c_str();
        QTableWidgetItem* item=new QTableWidgetItem(std::to_string(it->second).c_str());

        ui->tableWidget_history_data->setItem(0,column++,item);
    }
//    column_header<<"2009年1月"<<"2009年2月"<<"2009年3月"<<"2009年4月"<<"2009年5月"<<"2009年6月"
//         <<"2009年7月"<<"2009年8月"<<"2009年9月"<<"2009年10月"<<"2009年11月"<<"2009年12月";
    ui->tableWidget_history_data->setHorizontalHeaderLabels(column_header);
    QStringList row_header;
    row_header<<list_selection[1];
    ui->tableWidget_history_data->setVerticalHeaderLabels(row_header);
    this->show();

}
