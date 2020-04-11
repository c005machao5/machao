#include "mainwindowreg.h"
#include "ui_mainwindowreg.h"
#include <QDebug>
#include <unistd.h>

MainWindowReg::MainWindowReg(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindowReg)
{
    ui->setupUi(this);
    //设置背景图片
    setAutoFillBackground(true);
    QPalette pale=this->palette();
    pale.setBrush(backgroundRole(),QPixmap("C:/Users/4006006655/Desktop/003.jfif"));
    setPalette(pale);
    //设置窗口大小
    setMinimumSize(500,500);
    setMaximumSize(500,500);
    //设置界面标题
    setWindowTitle("注册界面");
    //隐藏提示信息
    ui->reg_reged_label->hide();
    ui->reg_success_label->hide();
    ui->reg_erropass_label->hide();
    //结构体初始化
   reuserdata.age=0;
   client=new ClientSocket;
   sig  = new signal_s;

    //连接函数
   qDebug()<<client->m_connect_socket("192.168.31.27",8977);
   connect(this,&MainWindowReg::my_signal_reg_commit,this,&MainWindowReg::my_slots_reg_commit);
   connect(sig,QOverload<UserData>::of(&signal_s::client_socket_signal),this,&MainWindowReg::my_recv_slots);
}

MainWindowReg::~MainWindowReg()
{
    delete ui;
}
//向服务端发送注册信息函数
void MainWindowReg::SendRegInfo(UserData& ud)
{
    client->sendMSG(ud);
}
//接收服务端返回信息函数
void MainWindowReg::RecvRegInfo()
{
    if(reuserdata.age!=0)
    {
        int result=reuserdata.right;
        if(result==0){//返回0显示已注册提示
            ui->reg_reged_label->show();
        }
        //返回值不为0显示注册成功的提示
        else{
           ui->reg_success_label->show();
        }
    }
}

void MainWindowReg::my_slots_reg_commit()
{
    //判断两次密码是否一致
    QString str1=ui->reg_pass_lineEdit->text();
    QString str2=ui->reg_pass2_lineEdit->text();
    if(str1!=str2){
       ui->reg_erropass_label->show();
    }
    //提取用户注册信息
//int page,int pright,char* psex,char* ptel,char* ppass,char* pname,char* pbirthday
     UserData senduserdata(ui->reg_agelineEdit->text().toInt(),
             ui->reg_right_lineEdit->text().toInt(),
             ui->reg_sex_lineEdit->text().toStdString().c_str(),
             ui->reg_tel_lineEdit->text().toStdString().c_str(),
             ui->reg_pass_lineEdit->text().toStdString().c_str(),
             ui->reg_name_lineEdit->text().toStdString().c_str(),
             ui->reg_date_lineEdit->text().toStdString().c_str());
     //清空文本框内容
     ui->reg_agelineEdit->clear();
     ui->reg_right_lineEdit->clear();
     ui->reg_sex_lineEdit->clear();
     ui->reg_tel_lineEdit->clear();
     ui->reg_pass_lineEdit->clear();
     ui->reg_name_lineEdit->clear();
     ui->reg_date_lineEdit->clear();
    //调用发送函数
     SendRegInfo(senduserdata);
}

void MainWindowReg::my_recv_slots(UserData reuserdata)
{
    RecvRegInfo();
}

void MainWindowReg::on_reg_commit_btn_clicked()
{
    emit my_signal_reg_commit();
}

void MainWindowReg::on_reg_back_btn_clicked()
{
    emit my_signal_reg_back();
}
