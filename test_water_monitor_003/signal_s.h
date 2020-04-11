#ifndef SIGNAL_S_H
#define SIGNAL_S_H

#include <QObject>



struct Head_Packet
{
    int cmdType;
    int totalbytes;
};
Q_DECLARE_METATYPE(Head_Packet)

struct UserData{
    int cmdnum;
    int totalsize;
    int  age;//判断标识
    int  right;
    char sex[4];    //性别
    char tel[24];    //联系方式
    char passward[24];  //密码
    char name[32];   //姓名
    char birthday[64];   //出生日期
    UserData()
    {

        age = 0;
        right = 0;
        memset(sex, 0, sizeof(sex));
        memset(tel, 0, sizeof(tel));
        memset(passward, 0, sizeof(passward));
        memset(name, 0, sizeof(name));
        memset(birthday, 0, sizeof(birthday));
    }
    UserData(int page, int pright, const char* psex, const char* ptel, const char* ppass, const char* pname, const char* pbirthday)
    {
        age = page;
        right = pright;
        strcpy(sex, psex);
        strcpy(tel, ptel);
        strcpy(passward, ppass);
        strcpy(name, pname);
        strcpy(birthday, pbirthday);
    }
};
Q_DECLARE_METATYPE(UserData)

struct Data_Selection       //cmdType2
{
    int cmdnum;
    int totalsize;
    char data_time_type[30];   //时间类型
    char  observe_well[10];    //观测井
    char  show_type[20];       //查看的类型 选项有水埋深最大值 水位最大值
    char  time_select[15];     //输入的时间
    Data_Selection()
    {
        cmdnum = 0;
        memset(data_time_type, 0, sizeof(data_time_type));
        memset(observe_well, 0, sizeof(observe_well));
        memset(show_type, 0, sizeof(show_type));
        memset(time_select, 0, sizeof(time_select));
    }
    Data_Selection(const char* pdata_time_type, const char* pobserve_well, const char* pshow_type, const char* ptime_select)
    {
        strcpy(data_time_type, pdata_time_type);
        strcpy(observe_well, pobserve_well);
        strcpy(show_type, pshow_type);
        strcpy(time_select, ptime_select);
    }
};
Q_DECLARE_METATYPE(Data_Selection)

struct Data_Analysis            //cmdType3
{
    int cmdnum;
    int totalsize;
    char start_year[20];        //起始年份
    char end_year[20];          //结束年份
    char  observe_well[20];     //观测井
    char  select_month[20];     //选择观测的月份
    Data_Analysis()
    {
        cmdnum = 0;
        memset(start_year, 0, sizeof(start_year));
        memset(end_year, 0, sizeof(end_year));
        memset(observe_well, 0, sizeof(observe_well));
        memset(select_month, 0, sizeof(select_month));
    }
    Data_Analysis(const char* pstart_year, const char* pend_year, const char* pobserve_well, const char* pselect_month)
    {
        strcpy(start_year, pstart_year);
        strcpy(end_year, pend_year);
        strcpy(observe_well, pobserve_well);
        strcpy(select_month, pselect_month);
    }
};
Q_DECLARE_METATYPE(Data_Analysis)
//李迪
struct Data                     //cmdType4
{
    int cmdnum;
    int totalsize;
    char name[128];
    char corp[128];
    double longitude;
    double latitude;
    double level;
    double depth;
    int GPRS;
    int AD;
    int FLUG;
    time_t time;
    Data()
    {
        cmdnum = 0;
        memset(name, 0, sizeof(name));
        memset(corp, 0, sizeof(corp));
        longitude = 0;
        latitude = 0;
        level = 0;
        depth = 0;
        GPRS = 0;
        AD = 0;
        FLUG = 0;
        time = 0;
    }
    Data(const char* pname, const char* pcorp, double plongitude, double platitude, double plevel, double pdepth, int pGPRS, int pAD, int pFLUG, time_t ptime)
    {
        strcpy(name, pname);
        strcpy(corp, pcorp);
        longitude = plongitude;
        latitude = platitude;
        level = plevel;
        depth = pdepth;
        GPRS = pGPRS;
        AD = pAD;
        FLUG = pFLUG;
        time = ptime;
    }
};
Q_DECLARE_METATYPE(Data)

struct LoginInfo
{
    int cmdnum;
    int totalsize;
    char name[32];     //用户名
    char passward[24]; //密码
    int userright;     //服务器返回权限标识
    LoginInfo()
    {
        cmdnum = 0;
        memset(name, 0, sizeof(name));
        memset(passward, 0, sizeof(passward));
        userright = 0;
    }
    LoginInfo(const char* pname, const char* ppassward, int puserright)
    {
        strcpy(name, pname);
        strcpy(passward, ppassward);
        userright = puserright;
    }
};
Q_DECLARE_METATYPE(LoginInfo)
class signal_s : public QObject
{
    Q_OBJECT
public:
    explicit signal_s(QObject *parent = nullptr);


signals:
    void client_socket_signal(UserData);
    void client_socket_signal(Data_Selection);
    void client_socket_signal(Data_Analysis);
    void client_socket_signal(Data);
    void client_socket_signal(LoginInfo);
public:
    void recvData(Data data)
    {
        emit client_socket_signal(data);
    }

};

#endif // SIGNAL_S_H
