#pragma once
#include "Includes.h"
class TimeStamp
{
public:
	TimeStamp() = default;

	//Copy Constructor
	TimeStamp(const TimeStamp& t) : year(t.year), month(t.month), day(t.day), hour(t.hour), minute(t.minute), second(t.second) {}

	//Move Constructor
	TimeStamp(TimeStamp&& t) : year(t.year), month(t.month), day(t.day), hour(t.hour), minute(t.minute), second(t.second) {}

	//Copy Assignment operator
	TimeStamp& operator=(const TimeStamp& t);

	//Move Assignment operator
	TimeStamp& operator=(TimeStamp&& t);

	~TimeStamp() = default;

	//Create a time stamp from a date and time string
	TimeStamp(std::string date, std::string time);

	bool operator==(const TimeStamp& t);
	bool operator!=(const TimeStamp& t);
	bool operator<(const TimeStamp &t);
	bool operator>(const TimeStamp& t);

	CString getTimeStamp();
	std::string getDateString();
	std::string getTimeString();

	int year{ 0 }, month{ 0 }, day{ 0 }, hour{ 0 }, minute{ 0 }, second{ 0 };
private:
};

