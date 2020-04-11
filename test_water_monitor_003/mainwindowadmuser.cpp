#include "mainwindowadmuser.h"
#include "ui_mainwindowadmuser.h"

MainWindowAdmUser::MainWindowAdmUser(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindowAdmUser)
{
    ui->setupUi(this);
    //设置界面标题
    setWindowTitle("管理员界面");
    //设置界面大小
    setMinimumSize(500,500);
    setMaximumSize(500,500);
    //插入界面背景
    setAutoFillBackground(true);
    QPalette pale1=this->palette();
    pale1.setBrush(backgroundRole(),QPixmap("C:/Users/4006006655/Desktop/003.jfif"));
    setPalette(pale1);
    //设置tablewidget
    //
    //初始化
    //timedis=new RealTimeDisplay;
    analyse=new HistoryDataAnalyse;
    query=new History_Data_Query;
    timedis=new RealTimeDisplay;
    //连接函数
    connect(this,&MainWindowAdmUser::my_signal_history,this,&MainWindowAdmUser::my_slots_history);
    connect(this,&MainWindowAdmUser::my_signal_sta_data,this,&MainWindowAdmUser::my_slots_sta_data);
    connect(this,&MainWindowAdmUser::my_signal_newest,this,&MainWindowAdmUser::my_slots_newest);
    connect(this, &MainWindowAdmUser::my_signal_send_data, timedis, &RealTimeDisplay::updateData);
}

MainWindowAdmUser::~MainWindowAdmUser()
{
    delete ui;
    delete analyse;
    analyse=nullptr;
    delete query;
    query=nullptr;
}
//设置菜单
void MainWindowAdmUser::contextMenuEvent(QContextMenuEvent *event)
{
    //主菜单
     QMenu* MainMenu=new QMenu(this);
     //主菜单子项
     QAction* option=new QAction(MainMenu);
     option->setText("选项");
     QAction* about=new QAction(MainMenu);
     about->setText("关于");
     QList<QAction*> actionList;
     actionList<<option<<about;
     //添加子项到菜单
     MainMenu->addActions(actionList);

     //设置子菜单
     QMenu* childMenu=new QMenu();
     //子菜单子项
     QAction* history_find=new QAction(childMenu);
     history_find->setText("历史查询");
     connect(history_find,SIGNAL(triggered(bool)),this,SLOT(my_slots_ord_history()));
     QAction* statistic_data=new QAction(childMenu);
     statistic_data->setText("统计分析");
     connect(statistic_data,SIGNAL(triggered(bool)),this,SLOT(my_slots_ord_statistics()));
     QAction* newest_data=new QAction(childMenu);
     newest_data->setText("实时显示");
     connect(newest_data,SIGNAL(triggered(bool)),this,SLOT(my_slots_ord_newest()));

     QList<QAction*> childActionlist;
     childActionlist<<history_find<<statistic_data<<newest_data;
     childMenu->addActions(childActionlist);

     //设置子菜单归属
     option->setMenu(childMenu);
     //主菜单添加子菜单
     MainMenu->addMenu(childMenu);
     //移动到当前鼠标位置
     MainMenu->exec(QCursor::pos());
}
//告警信息函数
void MainWindowAdmUser::WarnPrompt()
{/*
    //int t=read();
       int t=4;
       switch(t)
       {
       //qDebug()临时测试用
       case 0:qDebug()<<"A处有处于不安全状态！";break;
       case 1:qDebug()<<"B处有处于不安全状态！";break;
       case 2:qDebug()<<"C处有处于不安全状态！";break;
       case 3:qDebug()<<"D处有处于不安全状态！";break;
       }*/
}

void MainWindowAdmUser::my_slots_history()
{
    //show对应的窗口
    query->show();
}

void MainWindowAdmUser::my_slots_sta_data()
{
    //show对应的窗口
    analyse->show();
}

void MainWindowAdmUser::my_slots_newest()
{
    //show对应的窗口
    timedis->show();
}

void MainWindowAdmUser::on_adm_history_btn_clicked()
{
    emit my_signal_history();
}

void MainWindowAdmUser::on_adm_sta_btn_clicked()
{
   emit my_signal_sta_data();
}

void MainWindowAdmUser::on_adm_newest_btn_clicked()
{
    emit my_signal_newest();
}

void MainWindowAdmUser::recvData(Data data)
{
    m_data = data;
    qDebug()<<"name:"<<data.name<<"\n"\
             <<"latitude:"<<data.latitude<<"\n"\
             <<"level:"<<data.level<<"\n"\
             <<"GPRS:"<<data.GPRS<<"\n"\
             <<"latitude:"<<data.latitude<<"\n"\
             <<"longitude:"<<data.longitude<<"\n"\
             <<"FLUG:"<<data.FLUG;
    emit my_signal_send_data(m_data);
}
