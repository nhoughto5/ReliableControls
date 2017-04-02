#ifndef IEVENTCOUNTER_H
#define IEVENTCOUNTER_H


#pragma once
#include <atlstr.h>
#include <map>
#include <fstream>
#include <string>
#include <iostream>

class IEventCounter
{
public:
	IEventCounter();
	~IEventCounter();

	void ParseEvents(CString deviceID, const char* logName);
	int GetEventCount(CString deviceId);
private:
	std::map<CString, int> mDeviceFaultCount;
};

#endif // !IEVENTCOUNTER_H