#include "mainwindoworduser.h"
#include "ui_mainwindoworduser.h"

MainWindowOrdUser::MainWindowOrdUser(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindowOrdUser)
{
    ui->setupUi(this);
    //设置界面标题
    setWindowTitle("普通用户界面");
    //设置界面大小
    setMinimumSize(300,300);
    setMaximumSize(300,300);
    //插入界面背景
    setAutoFillBackground(true);
    QPalette pale2=this->palette();
    pale2.setBrush(backgroundRole(),QPixmap("C:/Users/4006006655/Desktop/003.jfif"));
    setPalette(pale2);
    //初始化
    //chart=new WidgetRealtimeChart;
    ordanl=new HistoryDataAnalyse;
    ordquery= new History_Data_Query;
    orddis=new RealTimeDisplay;
    //connect
   connect(this,&MainWindowOrdUser::my_signal_ord_history,this,&MainWindowOrdUser::my_slots_ord_history);
   connect(this,&MainWindowOrdUser::my_signal_ord_sta_data,this,&MainWindowOrdUser::my_slots_ord_sta_data);
   connect(this,&MainWindowOrdUser::my_signal_ord_newest,this,&MainWindowOrdUser::my_slots_ord_newest);
   qRegisterMetaType<Data>("Data"); //娉ㄥ唽鑷畾涔夌被鍨嬬敤浜庝俊鍙锋Ы鍑芥暟
   connect(this, QOverload<Data>::of(&MainWindowOrdUser::my_signal_ord_update),orddis , QOverload<Data>::of(&RealTimeDisplay::updateData));
   connect(this, &MainWindowOrdUser::my_signal_send_orddata, orddis, &RealTimeDisplay::updateData);
}

MainWindowOrdUser::~MainWindowOrdUser()
{
    delete ui;
    delete ordanl;
    delete ordquery;
}
//菜单设置
void MainWindowOrdUser::contextMenuEvent(QContextMenuEvent *event)
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
     connect(statistic_data,SIGNAL(triggered(bool)),this,SLOT(my_slots_ord_sta_data()));
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
void MainWindowOrdUser::OrdWarnPrompt()
{
    /*
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

void MainWindowOrdUser::my_slots_ord_history()
{
    //show相应的窗口
    ordquery->show();
}

void MainWindowOrdUser::my_slots_ord_sta_data()
{
    //show相应的窗口
    ordanl->show();
}

void MainWindowOrdUser::my_slots_ord_newest()
{
    //show相应的窗口
    orddis->show();
}

void MainWindowOrdUser::on_ord_history_btn_clicked()
{
    emit my_signal_ord_history();
}

void MainWindowOrdUser::on_ord_sta_btn_clicked()
{
   emit my_signal_ord_sta_data();
}

void MainWindowOrdUser::on_ord_newest_btn_clicked()
{
    emit my_signal_ord_newest();
}

void MainWindowOrdUser::recvData(Data data)
{
    m_data=data;
    emit my_signal_send_orddata(data);
}
