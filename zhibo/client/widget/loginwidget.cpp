#include "loginwidget.h"
#include "ui_loginwidget.h"
#include <QMessageBox>

#include "socket/socketmanager.h"
#include "protocol/protocol.h"
LoginWidget::LoginWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LoginWidget)
{
    ui->setupUi(this);
}

LoginWidget::~LoginWidget()
{
    delete ui;
}

void LoginWidget::on_btnRegister_clicked()
{
    //注册
    //1. 账号+密码获取
    QString username = ui->leUsername->text();
    QString userpwd = ui->leUserpwd->text();

    ui->leUsername->clear();
    ui->leUserpwd->clear();

    if(username.isEmpty() || userpwd.isEmpty()){
        QMessageBox::warning(this, "注册信息", "账号或密码不能为空");
        return;
    }

    //2. 将账号与密码，发送给服务器，打包
    Protocol p;
    p.setType(Protocol::regist);
    p["username"] = username;
    p["userpwd"] = userpwd;
    p["type"] = "register";

    SocketManager::getInstance()->write(p.pack());
}

void LoginWidget::on_btnLogin_clicked()
{
    QString username = ui->leUsername->text();
    QString userpwd = ui->leUserpwd->text();

    ui->leUsername->clear();
    ui->leUserpwd->clear();

    if(username.isEmpty() || userpwd.isEmpty()){
        QMessageBox::warning(this,"登录信息","账号或密码不能为空");
        return;
    }

    Protocol p;
    p.setType(Protocol::login);
    p["username"] = username;
    p["userpwd"] = userpwd;
    p["type"] = "login";

    SocketManager::getInstance()->write(p.pack());
}
