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
	char* ptr;   //������
	int   size;  //��������С
	int   offset; //дָ��
	int   pos; //��ָ��
};

