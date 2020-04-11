#pragma once
#ifndef CLIENTSOCKET_H
#define CLIENTSOCKET_H

#include<time.h>
struct Head_Packet
{
	int cmdType;
	int totalbytes;
};

struct UserData {

	int  age;//判断标识
	int  right;
	char sex[4];    //性别
	char tel[24];    //联系方式
	char passward[24];  //密码
	char name[32];   //姓名
	char birthday[64];   //出生日期
};


struct Data_Selection       //cmdType2
{
	char data_time_type[30];   //时间类型
	char  observe_well[10];    //观测井
	char  show_type[20];       //查看的类型 选项有水埋深最大值 水位最大值
	char  time_select[15];     //输入的时间
	
};


struct Data_Analysis            //cmdType3
{
	char start_year[20];        //起始年份
	char end_year[20];          //结束年份
	char  observe_well[20];     //观测井
	char  select_month[20];     //选择观测的月份
};

//李迪
struct Data                     //cmdType4
{
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
	
};

struct LoginInfo
{
	char name[32];     //用户名
	char passward[24]; //密码
	int userright;     //服务器返回权限标识

};

#endif // CLIENTSOCKET_H



