#include "stdafx.h"
#include "CreatDir.h"
#include<string>

CreatDir::CreatDir()
{

}
CreatDir::~CreatDir()
{
}

bool CreatDir::createDirectory( std::string folder)
{
	std::string temp = "D:\\user\\";
	std::string transfer = folder;
	folder = temp;
	folder += transfer;
	std::string folder_builder;
	std::string sub;
	sub.reserve(folder.size());
	for (auto it = folder.begin(); it != folder.end(); ++it) {
		//cout << *(folder.end()-1) << endl;
		const char c = *it;
		sub.push_back(c);
		if (c == PATH_DELIMITER || it == folder.end() - 1) {
			folder_builder.append(sub);
			if (0 != ::_access(folder_builder.c_str(), 0)) {
				// this folder not exist
				if (0 != ::_mkdir(folder_builder.c_str())) {
					// create failed
					return false;
				}
			}
			sub.clear();
		}
	}
	return false;
}
