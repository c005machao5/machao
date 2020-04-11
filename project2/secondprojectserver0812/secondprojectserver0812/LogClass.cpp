#include "stdafx.h"
#include "LogClass.h"


LogClass::LogClass(const char* predix_name, const char* path)
{
	daily_logger = spd::daily_logger_mt(predix_name, path);
	daily_logger->flush_on(spd::level::err); 
}	

void LogClass::write_Info(std::string info, int line, std::string filename, std::string functionname)
{
	std::ostringstream os;
	//os << "�к�:" << __LINE__ << " �ļ���: " << __FILE__ << " ������: " << __FUNCTION__;
	os << "�к�:" << line << " �ļ���: " << filename << " ������: " << functionname<<" ";
	os << info;
	daily_logger->info(os.str());	
}

void LogClass::write_error(std::string error, int line, std::string filename, std::string functionname)
{
	std::ostringstream os;
	//os << "�к�:" << __LINE__ << " �ļ���: " << __FILE__ << " ������: " << __FUNCTION__;
	os << "�к�:" << line << " �ļ���: " << filename << " ������: " << functionname << " ";
	os << error;
	daily_logger->error(os.str());
}

LogClass::~LogClass()
{
}
