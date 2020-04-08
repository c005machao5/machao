#ifndef CLIENTSOCKET_H
#define CLIENTSOCKET_H

#include <QObject>
#include <QTcpSocket>

#include "protocol/protocol.h"

class ClientSocket : public QObject
{
    Q_OBJECT
public:
    explicit ClientSocket(QTcpSocket* socket,QObject *parent = nullptr);

signals:

private slots:
    void onReadyRead();
    void onDisConnected();
private:
    QTcpSocket* socket;
    QByteArray buffer;

    void registHandler(Protocol p);
    void loginHandler(Protocol p);
    void roomHandler(Protocol p);
    void chatHandler(Protocol p);
    void chargeHandler(Protocol p);
    void giftHandler(Protocol p);

    void giftScroll(QString username,QString roomname,int money);
    void refreshRoom();
    void refreshUser(QString roomname);
};

#endif // CLIENTSOCKET_H
