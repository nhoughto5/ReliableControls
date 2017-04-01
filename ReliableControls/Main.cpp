#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "IEventCounter.h"
#include "Helpers.h"
#include <vector>

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
	REQUIRE(logs[0].Compare(CString("2015-04-03 09:08:01 0")) == 0);
	REQUIRE(logs[1].Compare(CString("2015-04-03 09:13:01 0")) == 0);
	REQUIRE(logs[2].Compare(CString("2015-04-03 09:18:01 0")) == 0);
	REQUIRE(logs[3].Compare(CString("2015-04-03 09:23:01 0")) == 0);
	REQUIRE(logs[4].Compare(CString("2015-04-03 09:28:01 0")) == 0);
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
	REQUIRE(fault[0].Compare(CString("2015-04-03 09:08:01 3")) == 0);
	REQUIRE(fault[1].Compare(CString("2015-04-03 09:14:01 2")) == 0);
}

TEST_CASE("IEventCounter_Test") {
	std::vector<CString> Logs = getTestLogs();
	REQUIRE(!Logs.empty());
}
