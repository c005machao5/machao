#ifndef PROTOCOL_H
#define PROTOCOL_H

#include <QByteArray>
#include <QJsonObject>

class Protocol
{
public:
    enum Type{
        none = 0,
        regist,
        login,
        room,
        chat,
        charge,
        gift
    };
    Protocol();

    QJsonValue operator[](const QString& key)const{
        return object[key];
    }
    QJsonValueRef operator[](const QString& key){
         return object[key];
    }

    //生成，要发送的数据流
    QByteArray pack();
    //拆包
    bool unpack(QByteArray& array);

    Type getType() const;
    void setType(const Type &value);
private:
    Type type;
    QJsonObject object;
};

#endif // PROTOCOL_H
