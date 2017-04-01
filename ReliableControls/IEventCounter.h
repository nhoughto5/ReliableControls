#ifndef IEVENTCOUNTER_H
#define IEVENTCOUNTER_H


#pragma once
#include <atlstr.h>
#include <map>
class IEventCounter
{
public:
	IEventCounter();
	~IEventCounter();

	void ParseEvents(CString deviceID, const char* logName);
	int GetEventCount(CString deviceId);
private:
	unsigned int mCount;
	std::map<CString, int> mDeviceFaultCount;
};

#endif // !IEVENTCOUNTER_H