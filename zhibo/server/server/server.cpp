#include "server.h"
#include <QHostAddress>
#include <QTcpSocket>
#include <QDebug>

#include "socket/clientsocket.h"
#include "sql/sqldao.h"

#define ADDR "192.168.1.101"
#define PORT (11111)

Server::Server(QObject *parent)
    : QObject(parent)
{
    //1. 创建套接字
    server = new QTcpServer(this);
    SqlManager::getInstance()->open();
    SqlDao sd;
    sd.updateAllOnline();

    //2. 绑定 + 监听
    server->listen(QHostAddress(ADDR), PORT);

    //3. 建立连接
    QObject::connect(server, SIGNAL(newConnection()), this, SLOT(onNewConnection()));
}

Server::~Server()
{
    SqlManager::getInstance()->close();
}
void Server::onNewConnection()
{
    while(server->hasPendingConnections()){
        QTcpSocket* socket = server->nextPendingConnection();
        qDebug()<<"新的连接 ip:"<<socket->peerAddress().toString()<<" port:"<<socket->peerPort();

        new ClientSocket(socket, this);
    }
}

