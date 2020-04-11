#pragma once

#include <string>

class HttpFile
{
public:
	HttpFile();
	~HttpFile();

	int write(const char* buf, int len);

	int readLine(std::string& buf);

	int read(std::string& buf, int len);

	int seek(int pos);

	void clear();
private:
	char* ptr;   //缓存区
	int   size;  //缓存区大小
	int   offset; //写指针
	int   pos; //读指针
};

