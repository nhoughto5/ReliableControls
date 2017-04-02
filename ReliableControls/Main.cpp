#define CATCH_CONFIG_MAIN
#include <fstream>
#include <vector>
#include "catch.hpp"
#include "IEventCounter.h"
#include "Helpers.h"


TEST_CASE("TimeStamp_Test") {
	timeStamp t;
	t.year = 2015;
	t.month = 4;
	t.day = 3;
	t.hour = 9;
	t.minute = 8;
	t.second = 1;
	CString answer("2015-04-03 09:08:01");
	REQUIRE(t.getTimeStamp().Compare(answer) == 0);


	timeStamp t2("2015-09-08", "07:06:01");
	REQUIRE(t2.getTimeStamp().Compare(CString("2015-09-08 07:06:01")) == 0);

	REQUIRE(t2 > timeStamp("2014-09-08", "07:06:01"));
	REQUIRE(t2 > timeStamp("2015-08-08", "07:06:01"));
	REQUIRE(t2 > timeStamp("2015-09-07", "07:06:01"));
	REQUIRE(t2 > timeStamp("2015-09-08", "05:06:01"));
	REQUIRE(t2 > timeStamp("2015-09-08", "07:04:01"));
	REQUIRE(t2 > timeStamp("2015-09-08", "07:06:00"));


	REQUIRE(t2 < timeStamp("2016-09-08", "07:06:01"));
	REQUIRE(t2 < timeStamp("2015-10-08", "07:06:01"));
	REQUIRE(t2 < timeStamp("2015-09-09", "07:06:01"));
	REQUIRE(t2 < timeStamp("2015-09-08", "08:06:01"));
	REQUIRE(t2 < timeStamp("2015-09-08", "07:07:01"));
	REQUIRE(t2 < timeStamp("2015-09-08", "07:06:02"));

	REQUIRE(t2 == timeStamp("2015-09-08", "07:06:01"));
	REQUIRE(t2 != timeStamp("2012-09-08", "07:06:01"));

}

TEST_CASE("NormalLogs_Test") {
	timeStamp t;
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
	timeStamp t;
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

	//IEventCounter iEventCounter;
	//iEventCounter.ParseEvents("d1", filename.c_str());
}
