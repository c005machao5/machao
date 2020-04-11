#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //设置背景图片
    setAutoFillBackground(true);
    QPalette pal=this->palette();
    pal.setBrush(backgroundRole(),QPixmap("C:/Users/4006006655/Desktop/001.jfif"));
    setPalette(pal);
    //设置窗口下方标签颜色
    ui->under_label->setStyleSheet("background-color:rgb(255,255,255);");
    //给标签设置图片
    QPixmap pix("C:/Users/4006006655/Desktop/005.jpg");
    pix=pix.scaled(QSize(80,80),Qt::KeepAspectRatio);
    ui->picture_label->setPixmap(pix);
    //设置窗口大小
    setMinimumSize(370,300);
    setMaximumSize(370,300);
    //设置界面标题
    setWindowTitle("登陆界面");
    //初始化指针
    reg=new MainWindowReg;
    logclient=new ClientSocket;
    admuser=new MainWindowAdmUser;
    orduser=new MainWindowOrdUser;
    //sig = new signal_s;
    //连接函数
    qDebug()<<logclient->m_connect_socket("127.0.0.1",8977);
    connect(this,&MainWindow::my_signal_main_reg,this,&MainWindow::my_slots_main_reg);
    connect(reg,&MainWindowReg::my_signal_reg_back,this,&MainWindow::my_slots_reg_back);
    connect(this,&MainWindow::my_signal_main_confirmlog,this,&MainWindow::my_slots_main_confirmlog);
    //connect(sig,QOverload<LoginInfo>::of(&signal_s::client_socket_signal),this,&MainWindow::my_slots_logrecv);
    connect(&logclient->sig, QOverload<Data>::of(&signal_s::client_socket_signal), admuser, QOverload<Data>::of(&MainWindowAdmUser::recvData));
    connect(&logclient->sig, QOverload<Data>::of(&signal_s::client_socket_signal), orduser, QOverload<Data>::of(&MainWindowOrdUser::recvData));
    //connect(&logclient->sig,)
}


MainWindow::~MainWindow(){
    delete ui;
}

void MainWindow::SendLogInfo(LoginInfo& logud)
{
    //调用客户端socket发送函数

    logclient->sendMSG(logud);
}
//接收服务端信息
void MainWindow::RecvLogInfo()
{
    //logclient.recveMsg();
    //int relog=recvlogdata.right;
    int rt=1;
    if(rt==0){
        //跳转至普通用户界面
        this->hide();
        orduser->show();
    }
    else{
    //跳转至管理员界面
        this->hide();
        admuser->show();
    }
}

void MainWindow::on_main_reg_btn_clicked()
{
    emit my_signal_main_reg();
}

void MainWindow::my_slots_main_reg()
{
    this->hide();
    reg->show();
}

void MainWindow::my_slots_reg_back()
{
    reg->hide();
    this->show();
}
//确认登陆按钮槽函数
void MainWindow::my_slots_main_confirmlog()
{

   //提取用户注册信息并将其存放至结构体中
    LoginInfo logsenddata(ui->log_user_lineEdit->text().toStdString().c_str(),
                         ui->log_pass_lineEdit->text().toStdString().c_str(),0);
    qDebug()<<"**************";
    qDebug()<<logsenddata.name<<" "<<logsenddata.passward<<" "<<logsenddata.userright;
   //logsenddata.right=0;//默认赋值为0
   //清空文本内容
   ui->log_user_lineEdit->clear();
   ui->log_pass_lineEdit->clear();
   //调用发送登陆信息函数
   SendLogInfo(logsenddata);
   RecvLogInfo();//检测用
}

void MainWindow::my_slots_logrecv()
{
    RecvLogInfo();
}

void MainWindow::on_main_confirmlog_btn_clicked()
{
    emit my_signal_main_confirmlog();
}
