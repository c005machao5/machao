#ifndef SQLMANAGER_H
#define SQLMANAGER_H

#include <QSqlDatabase>

class SqlManager
{
private:
    SqlManager();
    static SqlManager* instance;
    QSqlDatabase db;

public:
    static SqlManager* getInstance();
    void open();
    void close();
};

#endif // SQLMANAGER_H
