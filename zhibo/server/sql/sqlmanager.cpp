#include "sqlmanager.h"

SqlManager::SqlManager()
    : db(QSqlDatabase::addDatabase("QMYSQL"))
{
    db.setHostName("localhost");
    db.setUserName("root");
    db.setPassword("root");
    db.setDatabaseName("user");
}
SqlManager* SqlManager::instance = new SqlManager;

SqlManager* SqlManager::getInstance()
{
    return instance;
}

void SqlManager::open()
{
    db.open();
}

void SqlManager::close()
{
    db.close();
}
