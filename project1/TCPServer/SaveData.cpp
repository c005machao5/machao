#include "stdafx.h"
#include "SaveData.h"


SaveData::SaveData()
{
	m_SQL = new std::string("insert into database_management(place,unit,longitude,latitude,water_level,water_depth,communicate_status,converter_state,water_status,time) values('");
}

SaveData::~SaveData()
{
	delete m_SQL;
	m_SQL = nullptr;
}

std::string SaveData::time_t2string(const time_t time_t_time)
{
	char szTime[100] = { '\0' };

	tm *pTm = new tm;
	localtime_s(pTm, &time_t_time);
	//pTm = localtime(&time_t_time);
	pTm->tm_year += 1900;
	pTm->tm_mon += 1;

	sprintf_s(szTime, "%04d-%02d-%02d %02d:%02d:%02d",
		pTm->tm_year,
		pTm->tm_mon,
		pTm->tm_mday,
		pTm->tm_hour,
		pTm->tm_min,
		pTm->tm_sec);

	std::string strTime = szTime;

	delete pTm;
	pTm = NULL;

	return strTime;
}

const char *SaveData::getSaveDataSQL(const struct Data data)
{
	std::string name(data.name);

	*m_SQL += data.name;
	*m_SQL += "','";
	*m_SQL += data.corp;
	*m_SQL += "',";
	*m_SQL += std::to_string(data.longitude);
	*m_SQL += ",";
	*m_SQL += std::to_string(data.latitude);
	*m_SQL += ",";
	*m_SQL += std::to_string(data.level);
	*m_SQL += ",";
	*m_SQL += std::to_string(data.depth);
	*m_SQL += ",";
	*m_SQL += std::to_string(data.GPRS);
	*m_SQL += ",";
	*m_SQL += std::to_string(data.AD);
	*m_SQL += ",";
	*m_SQL += std::to_string(data.FLUG);
	*m_SQL += ",'";
	*m_SQL += time_t2string(data.time);
	*m_SQL += "')";

	return m_SQL->c_str();
}