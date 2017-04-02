#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "IEventCounter.h"


struct Log {
	TimeStamp time;
	int value;
	Log() = default;
	Log(const TimeStamp& t, int v) :time(t), value(v) {}
	CString toString() {
		return time.getTimeStamp() + CString("\t") + CString(std::to_string(value).c_str());
	}
};
inline CString getRandomValue() {
	return CString(std::to_string(rand() % 4).c_str());
}

std::vector<CString> makeNormalLogs(int n, TimeStamp* start, bool useRandom) {
	std::vector<CString> ret;
	CString space(" ");
	for (int i = 0; i < n; ++i) {

		useRandom ? ret.push_back(Log(*start, rand() % 4).toString()) : ret.push_back(Log(*start, 0).toString());
		start->minute += 5;
	}
	return ret;
}

std::vector<CString> getFault(TimeStamp* start) {
	CString space(" ");
	std::vector<CString> ret;
	ret.push_back(Log(*start, 3).toString());
	start->minute += 6;
	ret.push_back(Log(*start, 2).toString());
	int n = rand() % 15, currentValue = 2;
	for (int i = 0; i < n; ++i) {
		currentValue == 2 ? currentValue = 3 : currentValue = 2;
		start->second += 2;
		ret.push_back(Log(*start, currentValue).toString());
	}
	start->minute += 1;
	ret.push_back(Log(*start, 0).toString());
	return ret;
}

std::vector<CString> getTestLogs() {
	TimeStamp t;
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

TEST_CASE("TimeStamp_Test") {

	TimeStamp t0;
	REQUIRE(t0.getTimeStamp().Compare(CString("0000-00-00 00:00:00")) == 0);

	TimeStamp t;
	t.year = 2015;
	t.month = 4;
	t.day = 3;
	t.hour = 9;
	t.minute = 8;
	t.second = 1;
	CString answer("2015-04-03 09:08:01");
	REQUIRE(t.getTimeStamp().Compare(answer) == 0);


	TimeStamp t2("2015-09-08", "07:06:01");
	REQUIRE(t2.getTimeStamp().Compare(CString("2015-09-08 07:06:01")) == 0);

	REQUIRE(t2 > TimeStamp("2014-09-08", "07:06:01"));
	REQUIRE(t2 > TimeStamp("2015-08-08", "07:06:01"));
	REQUIRE(t2 > TimeStamp("2015-09-07", "07:06:01"));
	REQUIRE(t2 > TimeStamp("2015-09-08", "05:06:01"));
	REQUIRE(t2 > TimeStamp("2015-09-08", "07:04:01"));
	REQUIRE(t2 > TimeStamp("2015-09-08", "07:06:00"));


	REQUIRE(t2 < TimeStamp("2016-09-08", "07:06:01"));
	REQUIRE(t2 < TimeStamp("2015-10-08", "07:06:01"));
	REQUIRE(t2 < TimeStamp("2015-09-09", "07:06:01"));
	REQUIRE(t2 < TimeStamp("2015-09-08", "08:06:01"));
	REQUIRE(t2 < TimeStamp("2015-09-08", "07:07:01"));
	REQUIRE(t2 < TimeStamp("2015-09-08", "07:06:02"));

	REQUIRE(t2 == TimeStamp("2015-09-08", "07:06:01"));
	REQUIRE(t2 != TimeStamp("2012-09-08", "07:06:01"));

}

TEST_CASE("NormalLogs_Test") {
	TimeStamp t;
	t.year = 2015;
	t.month = 4;
	t.day = 3;
	t.hour = 9;
	t.minute = 8;
	t.second = 1;
	std::vector<CString> logs = makeNormalLogs(5, &t, false);
	REQUIRE(logs[0].Compare(CString("2015-04-03 09:08:01\t0")) == 0);
	REQUIRE(logs[1].Compare(CString("2015-04-03 09:13:01\t0")) == 0);
	REQUIRE(logs[2].Compare(CString("2015-04-03 09:18:01\t0")) == 0);
	REQUIRE(logs[3].Compare(CString("2015-04-03 09:23:01\t0")) == 0);
	REQUIRE(logs[4].Compare(CString("2015-04-03 09:28:01\t0")) == 0);
}

TEST_CASE("GetFault_Test") {
	TimeStamp t;
	t.year = 2015;
	t.month = 4;
	t.day = 3;
	t.hour = 9;
	t.minute = 8;
	t.second = 1;
	std::vector<CString> fault = getFault(&t);
	REQUIRE(fault[0].Compare(CString("2015-04-03 09:08:01\t3")) == 0);
	REQUIRE(fault[1].Compare(CString("2015-04-03 09:14:01\t2")) == 0);
}

TEST_CASE("IEventCounter_Utility_Test") {
	TimeStamp t1("2014-09-08", "07:11:02");
	TimeStamp t2("2014-09-08", "07:06:01");
	TimeStamp t3("2014-09-08", "08:06:01");
	IEventCounter iEventCounter;

	REQUIRE(!iEventCounter.greaterThanFiveMinutes(t1, t1));
	REQUIRE(iEventCounter.greaterThanFiveMinutes(t1, t2));
	REQUIRE(iEventCounter.greaterThanFiveMinutes(t3, t2));
}

TEST_CASE("IEventCounter_Test") {
	std::string filename = "testFile.txt";
	std::vector<CString> Logs = getTestLogs();
	REQUIRE(!Logs.empty());
	USES_CONVERSION;
	std::ofstream testFile;
	testFile.open(filename);
	for (CString c : Logs) {
		CStringA output = T2A(c);
		for (int i = 0; i < output.GetLength(); i++) {
			testFile << output[i];
		}
		testFile << "\n";
	}
	testFile.close();

	IEventCounter iEventCounter;
	iEventCounter.ParseEvents("d1", filename.c_str());
	REQUIRE(iEventCounter.GetEventCount("d1") == 1);

	iEventCounter.ParseEvents("d1", filename.c_str());
	REQUIRE(iEventCounter.GetEventCount("d1") == 2);
}
