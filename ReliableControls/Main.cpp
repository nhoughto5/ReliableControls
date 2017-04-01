#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "IEventCounter.h"

TEST_CASE("Hello"){
	IEventCounter ev;
	REQUIRE(ev.hello() == "Hello");
}
