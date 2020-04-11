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

	int  age;//�жϱ�ʶ
	int  right;
	char sex[4];    //�Ա�
	char tel[24];    //��ϵ��ʽ
	char passward[24];  //����
	char name[32];   //����
	char birthday[64];   //��������
};


struct Data_Selection       //cmdType2
{
	char data_time_type[30];   //ʱ������
	char  observe_well[10];    //�۲⾮
	char  show_type[20];       //�鿴������ ѡ����ˮ�������ֵ ˮλ���ֵ
	char  time_select[15];     //�����ʱ��
	
};


struct Data_Analysis            //cmdType3
{
	char start_year[20];        //��ʼ���
	char end_year[20];          //�������
	char  observe_well[20];     //�۲⾮
	char  select_month[20];     //ѡ��۲���·�
};

//���
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
	char name[32];     //�û���
	char passward[24]; //����
	int userright;     //����������Ȩ�ޱ�ʶ

};

#endif // CLIENTSOCKET_H



