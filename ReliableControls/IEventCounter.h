#ifndef IEVENTCOUNTER_H
#define IEVENTCOUNTER_H
#pragma once
#include "Includes.h"
#include "TimeStamp.h"

class IEventCounter
{
public:
	IEventCounter();
	~IEventCounter();

	bool greaterThanFiveMinutes(TimeStamp & currentTime, TimeStamp & previousTime);

	void ParseEvents(CString deviceID, const char* logName);
	int GetEventCount(CString deviceId);
private:
	static std::map<CString, int> mDeviceFaultCount;
	static std::mutex mMutex;
};

#endif // !IEVENTCOUNTER_H