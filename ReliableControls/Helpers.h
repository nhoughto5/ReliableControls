#pragma once
#include <atlstr.h>
#include <vector>
#include <sstream>
#include <iomanip>

struct timeStamp {
	int year{ 0 }, month{ 0 }, day{ 0 }, hour{ 0 }, minute{ 0 }, second{ 0 };

	CString getTimeStamp() {
		CString yearStr, monthStr, dayStr, hourStr, minuteStr, secondStr;
		std::stringstream ss;

		yearStr = std::to_string(year).c_str();
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
};

struct Log {
	timeStamp time;
	int value;
	Log() = default;
	Log(timeStamp t, int v) :time(t), value(v) {}
	CString toString() {
		CString space(" ");
		return time.getTimeStamp() + space +CString(std::to_string(value).c_str());
	}
};
inline CString getRandomValue() {
	return CString(std::to_string(rand()%4).c_str());
}
std::vector<CString> makeNormalLogs(int n, timeStamp* start, bool useRandom) {
	std::vector<CString> ret;
	CString space(" ");
	for (int i = 0; i < n; ++i) {
		
		useRandom ? ret.push_back(Log(*start, rand()%4).toString()) : ret.push_back(Log(*start, 0).toString());
		start->minute += 5;
	}
	return ret;
}

std::vector<CString> getFault(timeStamp* start) {
	CString space(" ");
	std::vector<CString> ret;
	ret.push_back(CString(start->getTimeStamp() + space + CString('3')));
	start->minute += 6;
	ret.push_back(CString(start->getTimeStamp() + space + CString('2')));
	int n = rand() % 15, currentValue = 2;
	for (int i = 0; i < n; ++i) {
		currentValue = 2 ? currentValue = 3 : currentValue = 2;
		start->second += 2;
		ret.push_back(Log(*start, currentValue).toString());
	}
	start->minute += 1;
	ret.push_back(Log(*start, 0).toString());
	return ret;
}

std::vector<CString> getTestLogs() {
	timeStamp t;
	t.year = 2015;
	t.month = 4;
	t.day = 3;
	t.hour = 0;
	t.minute = 0;
	t.second = 0;
	std::vector<CString> ret;
	std::vector<CString> n1 = makeNormalLogs(5, &t, true);
	std::vector<CString> fault1 = getFault(&t);
	std::vector<CString> n2 = makeNormalLogs(5, &t, true);
	ret.insert(ret.end(), n1.begin(), n1.end());
	ret.insert(ret.end(), fault1.begin(), fault1.end());
	ret.insert(ret.end(), n2.begin(), n2.end());
	return ret;
}