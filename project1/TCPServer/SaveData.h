#pragma once
#include <string>
#include <time.h>
#include"StructData.h"


class SaveData
{
private:
	std::string *m_SQL;

	std::string time_t2string(const time_t time_t_time);

public:
	SaveData();
	~SaveData();
	const char *getSaveDataSQL(const struct Data data);
};

