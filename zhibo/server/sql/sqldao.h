#ifndef SQLDAO_H
#define SQLDAO_H
#include "model/user.h"

class SqlDao
{
public:
    SqlDao();

    bool insertUser(const User& user);
    bool selectUserByUsername(const QString& username, User& user);
    void updateUserOnline(const QString& username, bool online);
    void updateUserBalance(const QString& username,int balance);
    void updateAllOnline();
};

#endif // SQLDAO_H
