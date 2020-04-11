#pragma once
#include <io.h>
#include <direct.h>
#define PATH_DELIMITER '\\'
#include<string>
class CreatDir
{
public:
	CreatDir();
	~CreatDir();
	bool createDirectory( std::string folder);//给路径即可格式niuxin\\niuxinword
};

