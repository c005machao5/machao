#include "protocol.h"
#include <QJsonDocument>

Protocol::Type Protocol::getType() const
{
    return type;
}
void Protocol::setType(const Type &value)
{
    type = value;
}

Protocol::Protocol()
{

}


QByteArray Protocol::pack()
{
    //根据变长部分生成len
    //1. 序列化QJsonObject对象
    QByteArray obj = QJsonDocument(this->object).toJson();
    int len = obj.size();

    //2. 生成定长部分
    QByteArray head(sizeof(int) + sizeof(Type) + sizeof(float), 0);
    int* pLen = reinterpret_cast<int*>(head.data());
    *pLen = len;

    Type* pType = reinterpret_cast<Type*>(head.data() + sizeof(int));
    *pType = type;

    float* pVersion = reinterpret_cast<float*>(head.data() + sizeof(int) + sizeof(Type));
    *pVersion = 0.1;

    return head + obj;
}

bool Protocol::unpack(QByteArray &array)
{
    //array长度小于12， 定长都不够
    if(array.size() < static_cast<int>((sizeof(int) + sizeof(Type) + sizeof(float)))) return false;

    QByteArray head = array.left(sizeof(int) + sizeof(Type) + sizeof(float));
    //定长
    int* pLen = reinterpret_cast<int*>(head.data());
    int len = *pLen;

    Type* pType = reinterpret_cast<Type*>(head.data() + sizeof(int));
    Type type = *pType;

    float* pVersion = reinterpret_cast<float*>(head.data() + sizeof(int) + sizeof(Type));
    float version = *pVersion;

    Q_UNUSED(version);

    if(array.size() < static_cast<int>((sizeof(int) + sizeof(Type) + sizeof(float) + len)))   return false;

    //够定长+变长
    //去掉定长
    array = array.right(array.size() - head.size());

    this->type = type;
    this->object = QJsonDocument::fromJson(array.left(len)).object();

    //去掉变长
    array = array.right(array.size() - len);

    return true;
}
