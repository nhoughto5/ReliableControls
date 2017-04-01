#pragma once
#include <string>
class IEventCounter
{
public:
	IEventCounter();
	~IEventCounter();

	std::string hello();
private:
};

