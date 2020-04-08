#include "sqldao.h"
#include "sqlmanager.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QVariant>

SqlDao::SqlDao()
{

}
bool SqlDao::insertUser(const User &user)
{
    bool ret = false;

    //SqlManager::getInstance()->open();

    QSqlQuery query;
    query.prepare("insert into user(username, userpwd)"
                  "values(:username, :userpwd);");
    query.bindValue(":username", user.getUsername());
    query.bindValue(":userpwd", user.getUserpwd());

    ret = query.exec();
    if(!ret){
        qDebug()<<query.lastError().text();
    }

    //SqlManager::getInstance()->close();

    return ret;
}

bool SqlDao::selectUserByUsername(const QString &username, User &user)
{
    bool ret = false;

    //SqlManager::getInstance()->open();

    QSqlQuery query;
    query.prepare("select username, userpwd, online,balance from user"
                  " where username = :username;");
    query.bindValue(":username", username);

    ret = query.exec();
    if(!ret){
        qDebug()<<query.lastError().text();
    }else{
        ret = query.next();
        if(ret){
            //有数据，找到了
            user.setUsername(query.value(0).toString());
            user.setUserpwd(query.value(1).toString());
            user.setOnline(query.value(2).toBool());
            user.setBalance(query.value(3).toInt());
        }
    }

    //SqlManager::getInstance()->close();

    return ret;
}

void SqlDao::updateUserOnline(const QString &username, bool online)
{
    //SqlManager::getInstance()->open();

    QSqlQuery query;
    query.prepare("update user set online = :online "
                  "where username = :username;");
    query.bindValue(":online", online);
    query.bindValue(":username", username);

    if(!query.exec()){
        qDebug()<<query.lastError().text();
    }else{
    }

    //SqlManager::getInstance()->close();

    return;
}

void SqlDao::updateUserBalance(const QString &username, int balance)
{
    //SqlManager::getInstance()->open();

    QSqlQuery query;
    query.prepare("update user set balance = :balance "
                  "where username = :username;");
    query.bindValue(":balance", balance);
    query.bindValue(":username", username);

    if(!query.exec()){
        qDebug()<<query.lastError().text();
    }else{
    }

    //SqlManager::getInstance()->close();

    return;
}

void SqlDao::updateAllOnline()
{
    QSqlQuery query;
    query.prepare("update user set online = 0");

    if(!query.exec()){
        qDebug()<<query.lastError().text();
    }else{
    }
}


