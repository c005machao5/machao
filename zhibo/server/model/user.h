#ifndef USER_H
#define USER_H

#include <QString>

class User
{
private:
    QString username;
    QString userpwd;
    bool online;
    int balance;
public:
    User();
    User(const QString& username, const QString& userpwd, bool online);
    QString getUsername() const;
    void setUsername(const QString &value);
    QString getUserpwd() const;
    void setUserpwd(const QString &value);
    bool getOnline() const;
    void setOnline(bool value);
    int getBalance() const;
    void setBalance(int value);
};

#endif // USER_H
