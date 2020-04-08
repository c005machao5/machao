#ifndef CLIENTSOCKET_H
#define CLIENTSOCKET_H

#include <QObject>
#include <QTcpSocket>
#include <QTimer>

#include "protocol/protocol.h"

class ClientSocket : public QObject
{
    Q_OBJECT
public:
    explicit ClientSocket(QObject *parent = nullptr);

    void initSocket(QString ip, int port);
    inline qint64 write(const QByteArray& array){
        return this->socket->write(array);
    }

signals:

private slots:
    void onReadyRead();
    void onTimeout();
    void onConnected();
    void onDisConnected();
private:
    QTcpSocket* socket;
    QTimer* timer;

    QString ip;
    int port;

    QByteArray buffer;

    void registHandler(Protocol p);
    void loginHandler(Protocol p);
    void roomHandler(Protocol p);
    void chatHandler(Protocol p);
    void chargeHandler(Protocol p);
    void giftHandler(Protocol p);
};

#endif // CLIENTSOCKET_H
