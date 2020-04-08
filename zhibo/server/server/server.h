#ifndef SERVER_H
#define SERVER_H

#include <QObject>
#include <QTcpServer>
#include "sql/sqlmanager.h"

class Server : public QObject
{
    Q_OBJECT
public:
    explicit Server(QObject *parent = nullptr);
    ~Server();

signals:

private slots:
    void onNewConnection();

private:
    QTcpServer* server;
};

#endif // SERVER_H
