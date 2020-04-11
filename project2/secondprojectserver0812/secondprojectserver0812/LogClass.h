#pragma once
#include "spdlog/spdlog.h"
#include "spdlog/sinks/daily_file_sink.h"
#include <iostream>
#include<sstream>
namespace spd = spdlog;
class LogClass
{
public:	
	LogClass(const char* predix_name, const char* path); //path 日志路径 predix_name日志前缀
	void write_Info(std::string info,int line,std::string filename, std::string functionname);//写入的信息 第一个参数为写入的信息 第二个为行号 文件名 函数名 输入 __LINE__, __FILE__, __FUNCTION__
	void write_error(std::string error, int line, std::string filename, std::string functionname);//写入的信息 第一个参数为写入的信息 第二个为行号 文件名 函数名 输入 __LINE__, __FILE__, __FUNCTION__
	~LogClass();
private:	std::shared_ptr<spdlog::logger> daily_logger;
};

