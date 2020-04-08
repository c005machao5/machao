#include "user.h"

QString User::getUsername() const
{
    return username;
}

void User::setUsername(const QString &value)
{
    username = value;
}

QString User::getUserpwd() const
{
    return userpwd;
}

void User::setUserpwd(const QString &value)
{
    userpwd = value;
}

bool User::getOnline() const
{
    return online;
}

void User::setOnline(bool value)
{
    online = value;
}

int User::getBalance() const
{
    return balance;
}

void User::setBalance(int value)
{
    balance = value;
}

User::User()
{
    
}
User::User(const QString &username, const QString &userpwd, bool online)
    : username(username), userpwd(userpwd), online(online)
{

}
