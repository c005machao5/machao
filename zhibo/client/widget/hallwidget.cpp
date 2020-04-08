#include "hallwidget.h"
#include "ui_hallwidget.h"

#include "protocol/protocol.h"
#include "socket/socketmanager.h"

#include "widgetmanager.h"
HallWidget::HallWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HallWidget)
{
    ui->setupUi(this);
}

HallWidget::~HallWidget()
{
    delete ui;
}

void HallWidget::refleshRoomname(QStringList roomList)
{
    ui->lwRoom->clear();
    ui->lwRoom->addItems(roomList);
}

void HallWidget::closeEvent(QCloseEvent *event)
{
    event->ignore();
    {
        Protocol p;
        p.setType(Protocol::room);
        p["type"] = "quit";
        p["username"] = this->windowTitle();
        p["roomname"] = "";

        //先从大厅中出来
        SocketManager::getInstance()->write(p.pack());
    }
    {
        Protocol p;
        p.setType(Protocol::login);
        p["type"] = "quit";
        p["username"] = this->windowTitle();

        //再返回到登录界面
        SocketManager::getInstance()->write(p.pack());
    }

}

void HallWidget::showEvent(QShowEvent *)
{
    {
        //1.进入大厅
        Protocol p;
        p.setType(Protocol::room);
        p["type"] = "join";
        p["roomname"] = "";//分配一个虚拟的房间
        p["username"] = this->windowTitle();

        SocketManager::getInstance()->write(p.pack());
    }
    {
        //刷新房间
        Protocol p;
        p.setType(Protocol::room);
        p["type"] = "refresh";

        SocketManager::getInstance()->write(p.pack());
    }
}

void HallWidget::hideEvent(QHideEvent *)
{
    {
        //从大厅中出来
        Protocol p;
        p.setType(Protocol::room);
        p["type"] = "quit";
        p["username"] = this->windowTitle();
        p["roomname"] = "";

        SocketManager::getInstance()->write(p.pack());
    }

    //event->accept();
}

void HallWidget::on_btnCreate_clicked()//创建房间按钮的槽函数
{
    Protocol p;
    p.setType(Protocol::room);
    p["type"] = "create";
    p["roomname"] = this->windowTitle();
    p["username"] = p["roomname"];

    SocketManager::getInstance()->write(p.pack());
}

void HallWidget::on_lwRoom_itemDoubleClicked(QListWidgetItem *item)
{
    Protocol p;
    p.setType(Protocol::room);
    p["type"] = "join";
    p["roomname"] = item->text();
    p["username"] = this->windowTitle();

    SocketManager::getInstance()->write(p.pack());
}

void HallWidget::on_btnCharge_clicked()
{
    WidgetManager::getInstance()->getChargeWidget()->setWindowTitle(
                this->windowTitle());
    this->hide();
    WidgetManager::getInstance()->getChargeWidget()->show();
}
