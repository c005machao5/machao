#include "client.h"
#include "socket/socketmanager.h"
#include "widget/widgetmanager.h"
Client::Client(QObject *parent)
    : QObject(parent)
{
    SocketManager::getInstance();
}

void Client::show()
{
    WidgetManager::getInstance()->getLoginWidget()->show();//将注册和登录窗口show出来
}
