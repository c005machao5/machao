#ifndef STRUCTURAL_H
#define STRUCTURAL_H
#include <QObject>
//*****************结构体声明
//声明包头结构体
struct Head_Packet
{
    int cmd;
    int totalbytes;
};
Q_DECLARE_METATYPE(Head_Packet)
//声明用户信息结构体
struct UserData{
    int cmd;
    int totalsize;
    int  age;
    char sex[4];    //性别
    char passward[24];  //密码
    char name[32];   //姓名
    char birthday[64];   //出生日期
    UserData()
    {
        age = 0;
        memset(sex, 0, sizeof(sex));
        memset(passward, 0, sizeof(passward));
        memset(name, 0, sizeof(name));
        memset(birthday, 0, sizeof(birthday));
    }
    UserData(int page, const char* psex,const char* ppass, \
             const char* pname, const char* pbirthday)
    {
        age = page;
        strcpy(sex, psex);
        strcpy(passward, ppass);
        strcpy(name, pname);
        strcpy(birthday, pbirthday);
    }
};
Q_DECLARE_METATYPE(UserData)
struct FileMsg{
    int cmd;
    int num;
    unsigned long int ptotalsize;
    int totalblock;
    FileMsg()
    {
        ptotalsize=20;
        totalblock=2;
    }
    FileMsg(int a,int b)
    {
        ptotalsize=a;
        totalblock=b;
    }
};
class Structural
{
public:
    Structural();
};

#endif // STRUCTURAL_H
