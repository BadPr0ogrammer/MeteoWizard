#pragma once

#include <string>
#include <vector>

class date_c
{
public:
	int       m_year;
	int       m_mon;
	int       m_day;
	int       m_hour;
	int       m_mn;

	date_c(int year = 0, int mon = 0, int day = 0, int hour = 0, int mn = 0);
	date_c(const date_c& date);
	date_c(const char* date);
	date_c& operator = (const date_c& m);

	bool            parse(const char* date);
	std::string     date_str() const;
	int             scanf_atoi(const char* buf, int sz);

	static int  day_in_mon(int year, int mon);
	static int  day_of_week(int y, int m, int d);
	int         hour_range(const date_c& stop, std::vector<date_c>* ret) const;
	static int  date_only_cmp(const date_c& p1, const date_c& p2);
};
