#include "stdafx.h"
#include "Sqladd.h"


Sqladd::Sqladd()
{
}


Sqladd::~Sqladd()
{
}

const string Sqladd::inquire_name(const UserData name)//注册查重复
{
	string str = ("slecet count(1) from user_surface where user_name=");
	str += " \" ";
	str += name.name;
	str += " \" ";

	return str;
}

const string Sqladd::RegSql(const UserData senduserdata)//登录查询成功失败
{
	string regstr = "select count(1) from user_surface where user_usrface.user_name=";
	regstr += " \" ";
	regstr += senduserdata.name;
	regstr += " \" ";
	regstr += " ";
	regstr += "and user_surface.passward=";
	regstr += " \" ";
	regstr += senduserdata.passward;
	regstr += " \" ";
	return regstr;
}

const string Sqladd::Logstr(const LoginInfo loguserdata)//查权限
{
	string logstr = "select user_surface.jurisdiction from user_face where user_usrface.user_name=";
	logstr += " \" ";
	logstr += loguserdata.name;
	logstr += " \" ";
	return logstr;
}

string Sqladd::insert(UserData userinfo)//插入注册信息
{
	time_t  t = time(NULL);//时间函数
	tm buf;
	gmtime_s(&buf, &t);
	char buffer[122] = { 0 };
	sprintf_s(buffer, "%d-%02d-%02d %02d:%02d:%02d", buf.tm_year + 1900, \
		buf.tm_mon + 1, buf.tm_mday, buf.tm_hour + 8, buf.tm_min, buf.tm_sec);
	string time_str = buffer;
	string str = "insert into user_surface(user_name,user_password,registration_time,\
                                            jurisdiction,age,sex,birthdate,contact)\
                   values(";
	str += " \" ";
	str += userinfo.name;
	str += " \" ";
	str += ",";
	str += " \" ";
	str += userinfo.passward;
	str += " \" ";
	str += ",";
	str += " \" ";
	str += time_str;
	str += " \" ";
	str += ",";
	str += std::to_string(userinfo.right);
	str += ",";
	str += std::to_string(userinfo.age);
	str += ",";
	str += " \" ";
	str += userinfo.sex;
	str += " \" ";
	str += ",";
	str += " \" ";
	str += userinfo.birthday;
	str += " \" ";
	str += ",";
	str += " \" ";
	str += userinfo.tel;
	str += " \" ";
	str += ");";
	cout << str << endl;
	return str;
}

string Sqladd::createSql(Data_Selection m_data_selection)
{
	std::string str_month = "month";
	std::string str_hour = "hour";
	std::string str_day = "day";
	std::string str_max = "max";
	std::string str_left_brackets = "(";
	std::string str_right_brackets = ")";
	std::string str_space = " ";
	std::string str_from = "from";
	std::string str_observe_name = "监测点1";
	std::string str_where = "where";
	std::string str_and = "and";
	std::string str_date_time_floor = "2019-01-01 00:00:00";
	std::string str_date_time_ceil = "2020-01-01 00:00:00";
	std::string str_group_by = "group by";
	std::string str_order_by = "order by";
	std::string str_condition_name_observe_name = "place";
	std::string str_conditon_date_time = "datatime";
	std::string str_less_than = "<";
	std::string str_more_than = ">";
	std::string str_equal = "=";
	std::string str_select = "select";
	std::string str_comma = ",";
	std::string str_observe_type = "grooudwaterlevel";
	std::string str_table_name = "database_management";
	std::string str_quotation = "'";
	string str_time_suffix = "-01-01 00:00:00";
	string str_time_bar = "-";
	string str_time_bar_plus = "-01";
	string str_time_zero = " 00:00:00";
	string str_time_end = " 23:59:59";
	if (strcmp(m_data_selection.data_time_type, "bymonth") == 0)
	{
		str_observe_name = m_data_selection.observe_well;
		str_observe_type = m_data_selection.observe_well;
		string str_time;
		char str[5] = { 0 };

		strncpy(str, m_data_selection.time_select, 4);
		str_time = str;
		str_date_time_floor = str_time + str_time_suffix;
		int time_value = stoi(str_time);
		++time_value;
		str_time = to_string(time_value);
		str_date_time_ceil = str_time + str_time_suffix;
		str_observe_type = m_data_selection.show_type;

		std::string str_sql_month = str_select + str_space + str_month + str_left_brackets + str_conditon_date_time +
			str_right_brackets + str_comma + str_max + str_left_brackets + str_observe_type + str_right_brackets
			+ str_space + str_from + str_space + str_table_name + str_space + str_where + str_space + str_condition_name_observe_name + str_equal +
			str_quotation + str_observe_name + str_quotation + str_space + str_and + str_space + str_conditon_date_time
			+ str_more_than + str_equal + str_quotation + str_date_time_floor + str_quotation + str_space +
			str_and + str_space + str_conditon_date_time + str_less_than + str_quotation + str_date_time_ceil
			+ str_quotation + str_space + str_group_by + str_space + str_month + str_left_brackets + str_conditon_date_time +
			str_right_brackets + str_space + str_order_by + str_space + str_conditon_date_time;
		string str_sql_month1 = string::fromStdString(str_sql_month);
		return str_sql_month1;

	}
	else if (strcmp(m_data_selection.data_time_type, "byday") == 0)
	{

		str_observe_name = m_data_selection.observe_well;
		str_observe_type = m_data_selection.observe_well;

		char str[20] = { 0 };
		strncpy(str, m_data_selection.time_select, 20);

		string  str_time = str;
		string str_time_month = str_time.substr(5, 2);
		string str_time_year = str_time.substr(0, 4);
		str_date_time_floor = str_time_year + str_time_bar + str_time_month + str_time_bar_plus;


		int month = stoi(str_time_month);
		int time_value_year = stoi(str_time_year);
		if (month == 12)
		{
			month = 1;
			str_time_month = to_string(month);
			string str_time_month_temp = "0";
			str_time_month_temp.append(str_time_month);
			str_time_month = str_time_month_temp;
			++time_value_year;
		}
		else
		{
			++month;
			str_time_month = to_string(month);
			if (str_time_month.size() == 1)
			{
				
				string str_time_month_temp = "0";
				cout << str_time_month_temp.c_str() << "\n";
				str_time_month_temp.append(str_time_month);
				cout << str_time_month_temp.c_str() << "\n";
				str_time_month = str_time_month_temp;
			}
		}
		str_time_year = to_string(time_value_year);
		str_date_time_ceil = str_time_year + str_time_bar + str_time_month + str_time_bar_plus;
		str_observe_type = m_data_selection.show_type;

		std::string str_sql_day = str_select + str_space + str_day + str_left_brackets + str_conditon_date_time +
			str_right_brackets + str_comma + str_max + str_left_brackets + str_observe_type + str_right_brackets
			+ str_space + str_from + str_space + str_table_name + str_space + str_where + str_space + str_condition_name_observe_name + str_equal +
			str_quotation + str_observe_name + str_quotation + str_space + str_and + str_space + str_conditon_date_time
			+ str_more_than + str_equal + str_quotation + str_date_time_floor + str_quotation + str_space +
			str_and + str_space + str_conditon_date_time + str_less_than + str_quotation + str_date_time_ceil
			+ str_quotation + str_space + str_group_by + str_space + str_day + str_left_brackets + str_conditon_date_time +
			str_right_brackets + str_space + str_order_by + str_space + str_conditon_date_time;

		

		return str_sql_day;
	}

	else if (strcmp(m_data_selection.data_time_type, "byhour") == 0)
	{
		str_observe_name = m_data_selection.observe_well;
		str_observe_type = m_data_selection.observe_well;

		char str[20] = { 0 };
		strncpy(str, m_data_selection.time_select, 20);

		string  str_time = str;
		string str_time_time = str_time.substr(0, 10);

		str_date_time_floor = str_time_time + str_time_zero;

		str_date_time_ceil = str_time_time + str_time_end;
		str_observe_type = m_data_selection.show_type;

		std::string str_sql_hour = str_select + str_space + str_hour + str_left_brackets + str_conditon_date_time +
			str_right_brackets + str_comma + str_max + str_left_brackets + str_observe_type + str_right_brackets
			+ str_space + str_from + str_space + str_table_name + str_space + str_where + str_space + str_condition_name_observe_name + str_equal +
			str_quotation + str_observe_name + str_quotation + str_space + str_and + str_space + str_conditon_date_time
			+ str_more_than + str_equal + str_quotation + str_date_time_floor + str_quotation + str_space +
			str_and + str_space + str_conditon_date_time + str_less_than + str_quotation + str_date_time_ceil
			+ str_quotation + str_space + str_group_by + str_space + str_hour + str_left_brackets + str_conditon_date_time +
			str_right_brackets + str_space + str_order_by + str_space + str_conditon_date_time;

		

		return str_sql_hour;
	}
}

string Sqladd::createSql(Data_Analysis m_data_analysis)
{
	std::string str_year = "year";
	std::string str_max = "max";
	std::string str_left_brackets = "(";
	std::string str_right_brackets = ")";
	std::string str_space = " ";
	std::string str_from = "from";
	std::string str_observe_name = "监测点1";
	std::string str_where = "where";
	std::string str_and = "and";
	std::string str_date_time_floor = "2019-01-01 00:00:00";
	std::string str_date_time_ceil = "2020-01-01 00:00:00";
	std::string str_group_by = "group by";
	std::string str_condition_name_observe_name = "place";
	std::string str_conditon_date_time = "datatime";
	std::string str_less_than = "<";
	std::string str_more_than = ">";
	std::string str_equal = "=";
	std::string str_select = "select";
	std::string str_comma = ",";
	std::string str_observe_type = "grooudwaterlevel";
	std::string str_table_name = "database_management";
	std::string str_quotation = "'";
	std::string str_like = "like";
	std::string str_min = "min";
	std::string str_like_type;
	string str_time_bar = "-";
	string str_time_suffix = "-01-01";

	str_observe_name = m_data_analysis.observe_well;
	str_observe_type = "water_level";


	char str[20] = { 0 };
	strncpy(str, m_data_analysis.start_year, 20);

	string  str_time_start = str;

	string str_time_year = str_time_start.substr(0, 4);

	str_date_time_floor = str_time_year + str_time_suffix;

	strncpy(str, m_data_analysis.end_year, 20);
	string  str_time_end = str;
	str_time_year = str_time_end.substr(0, 4);
	int time_value_year = stoi(str_time_year);
	++time_value_year;
	str_time_year = to_string(time_value_year);
	str_date_time_ceil = str_time_year + str_time_suffix;
	strncpy(str, m_data_analysis.select_month, 20);
	string str_month = str;
	if (str_month.size() == 1)
	{

		string str_time_month_temp = "0";
		str_time_month_temp += str_month;
		str_month = str_time_month_temp;
	}
	str_like_type.append("%");
	str_like_type += str_time_bar;
	str_like_type += str_month;
	str_like_type += str_time_bar;
	str_like_type.append("%");

	std::string str_sql_comparison = str_select + str_space + str_year + str_left_brackets + str_conditon_date_time +
		str_right_brackets + str_comma + str_max + str_left_brackets + str_observe_type + str_right_brackets
		+ str_comma + str_min + str_left_brackets + str_observe_type + str_right_brackets
		+ str_space + str_from + str_space + str_table_name + str_space + str_where + str_space + str_condition_name_observe_name + str_equal +
		str_quotation + str_observe_name + str_quotation + str_space + str_and + str_space + str_conditon_date_time
		+ str_more_than + str_equal + str_quotation + str_date_time_floor + str_quotation + str_space +
		str_and + str_space + str_conditon_date_time + str_less_than + str_quotation + str_date_time_ceil

		+ str_quotation + str_space + str_and + str_space + str_conditon_date_time + str_space
		+ str_like + str_space + str_quotation + str_like_type + str_quotation + str_space + str_group_by + str_space + str_year + str_left_brackets + str_conditon_date_time + str_right_brackets;
	
	return str_sql_comparison;
}
