#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    client=new FileclientSocket;
    client->socketConnect("127.0.0.1",8977);
    //起收包线程
    qDebug()<<"before  thread"<<endl;
    std::thread recv_t1(&MainWindow::recvThread,this);
    recv_t1.detach();
    qDebug()<<"init ok"<<endl;

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::recvThread()
{
    int len =1024;
    char buf[1024]={0};
    QByteArray recv_buf;
    Head_Packet head;
    UserData user;
    while(true){
        recv_buf.resize(len);
        int recv_res=client->socketRecv(buf,len);
        memcpy(recv_buf.data(),buf,len);
        memcpy(&head,recv_buf.data(),sizeof(Head_Packet));
        if(recv_res>0){
            qDebug()<<"succes to recv data!"<<endl;
        }
        else if(recv_res<=0){
            qDebug()<<"expection to the program"<<endl;
        }
        //数据解析部分
        if(head.cmd==1){
            memcpy(&user,recv_buf.data(),sizeof(UserData));
            //send signal
            //********to check
            qDebug()<<"age:"<<user.age<<";"
                   <<"birthday:"<<user.birthday;
        }
       recv_buf.resize(0);
    }
}
//接口
void MainWindow::sendThread(char * buf,int len,int number)
{
    qDebug()<<"sendThread"<<buf<<" "<<number<<endl;
    qDebug()<<"for sendThread...."<<endl;
    FileclientSocket* sendsocket=new FileclientSocket;
    sendsocket->socketConnect("127.0.0.1",8977);
    qDebug()<<"connect childthread"<<endl;
    int pnumber=number;
    int k=len/10;//每次传10个字节
    QByteArray send_arry;
    int i=0;
    while(k>0){
        send_arry.resize(10);
        //strncpy(send_arry,buf+k*10,10);//'\0'问题  // 任何类型的数据，不只是字符串
        memcpy(send_arry.data(),buf+i*10,10);
        qDebug()<<"send_arry"<<send_arry.data()<<endl;
        sendsocket->sendMsg(send_arry.data(),pnumber);//调用发送函数
        //qDebug()<<"sendMsg....."<<endl;
        --k;++i;
        send_arry.resize(0);

    }
    delete sendsocket;
    sendsocket=nullptr;
}

//按钮触发多线程发包
void MainWindow::on_pushButton_clicked()
{
//    UserData user(23,"m","324534","niuxinxin","1999-09-02");
//    client->sendMsg(user);
    char  buffer1[1024]={"qwertyuiopasdfghjklz"};//文件块内容20
    char buffer2[1024]={"12345678900987654321"};
    int len=20;
    int number1=1;
    int number2=2;
    qDebug()<<"for....thread"<<endl;
        //buffer每一块文件内容，len每一块文件长度,number文件块识别号
//        std::thread t1(&MainWindow::sendThread,this,buffer1,len,number1);//this紧跟函数
//        t1.detach();
//        qDebug()<<"t1.....thread"<<endl;
        std::thread t2(&MainWindow::sendThread,this,buffer2,len,number2);//this紧跟函数
        t2.detach();
        qDebug()<<"t2.....thread"<<endl;
}
