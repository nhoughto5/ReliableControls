#include "TimeStamp.h"

//Copy Assignment operator
TimeStamp & TimeStamp::operator=(const TimeStamp & t)
{
	if (this != &t) {
		year = t.year;
		month = t.month;
		day = t.day;
		hour = t.hour;
		minute = t.minute;
		second = t.second;
	}
	return *this;
}
//Move Assignment operator
TimeStamp & TimeStamp::operator=(TimeStamp && t)
{
	year = t.year;
	month = t.month;
	day = t.day;
	hour = t.hour;
	minute = t.minute;
	second = t.second;
	return *this;
}

//Create a time stamp from a date and time string
TimeStamp::TimeStamp(std::string date, std::string time) {
	size_t pos = 0;
	std::string delimiter1 = "-", delimiter2 = ":";
	std::string token;
	std::vector<std::string> tokens;
	while ((pos = date.find(delimiter1)) != std::string::npos) {
		token = date.substr(0, pos);
		tokens.push_back(token);
		date.erase(0, pos + delimiter1.length());
	}
	year = std::stoi(tokens[0]);
	month = std::stoi(tokens[1]);
	day = std::stoi(date); //The day value is still in the day string
	tokens.clear();
	pos = 0;
	while ((pos = time.find(delimiter2)) != std::string::npos) {
		token = time.substr(0, pos);
		tokens.push_back(token);
		time.erase(0, pos + delimiter2.length());
	}
	hour = std::stoi(tokens[0]);
	minute = std::stoi(tokens[1]);
	second = std::stoi(time); //The second value is still in the time string
}

std::string TimeStamp::getTimeString()
{
	return std::to_string(hour) + ":" + std::to_string(minute) + ":" + std::to_string(second);
}

std::string TimeStamp::getDateString()
{
	return std::to_string(year) + "-" + std::to_string(month) + "-" + std::to_string(day);
}

bool TimeStamp::operator==(const TimeStamp & t)
{
	return this->year == t.year && this->month == t.month && this->day == t.day && this->hour == t.hour && this->minute == t.minute && this->second == t.second;
}

bool TimeStamp::operator!=(const TimeStamp & t)
{
	return !(*this == t);
}

bool TimeStamp::operator<(const TimeStamp & t)
{
	return !(*this > t);
}

bool TimeStamp::operator>(const TimeStamp & t)
{
	if (this->year > t.year) {
		return true;
	}
	else {
		if (this->month > t.month) {
			return true;
		}
		else {
			if (this->day > t.day) {
				return true;
			}
			else {
				if (this->hour > t.hour) {
					return true;
				}
				else {
					if (this->minute > t.minute) {
						return true;
					}
					else {
						if (this->second > t.second) {
							return true;
						}
						else {
							return false;
						}
					}
				}
			}
		}
	}
}

CString TimeStamp::getTimeStamp()
{
	CString yearStr, monthStr, dayStr, hourStr, minuteStr, secondStr;
	std::stringstream ss;
	ss << std::setw(4) << std::setfill('0') << year;
	yearStr = ss.str().c_str();
	ss.str("");
	ss << std::setw(2) << std::setfill('0') << month;
	monthStr = ss.str().c_str();
	ss.str("");
	ss << std::setw(2) << std::setfill('0') << day;
	dayStr = ss.str().c_str();
	ss.str("");
	ss << std::setw(2) << std::setfill('0') << hour;
	hourStr = ss.str().c_str();
	ss.str("");
	ss << std::setw(2) << std::setfill('0') << minute;
	minuteStr = ss.str().c_str();
	ss.str("");
	ss << std::setw(2) << std::setfill('0') << second;
	secondStr = ss.str().c_str();
	ss.str("");
	CString dash("-"), colon(":"), space(" ");
	return yearStr + dash + monthStr + dash + dayStr + space + hourStr + colon + minuteStr + colon + secondStr;
}

