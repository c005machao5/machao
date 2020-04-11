#pragma once
#include "spdlog/spdlog.h"
#include "spdlog/sinks/daily_file_sink.h"
#include <iostream>
#include<sstream>
namespace spd = spdlog;
class LogClass
{
public:	
	LogClass(const char* predix_name, const char* path); //path ��־·�� predix_name��־ǰ׺
	void write_Info(std::string info,int line,std::string filename, std::string functionname);//д�����Ϣ ��һ������Ϊд�����Ϣ �ڶ���Ϊ�к� �ļ��� ������ ���� __LINE__, __FILE__, __FUNCTION__
	void write_error(std::string error, int line, std::string filename, std::string functionname);//д�����Ϣ ��һ������Ϊд�����Ϣ �ڶ���Ϊ�к� �ļ��� ������ ���� __LINE__, __FILE__, __FUNCTION__
	~LogClass();
private:	std::shared_ptr<spdlog::logger> daily_logger;
};

