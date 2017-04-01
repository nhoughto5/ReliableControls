#include "IEventCounter.h"



IEventCounter::IEventCounter(): mCount(0)
{
}


IEventCounter::~IEventCounter()
{
}

void IEventCounter::ParseEvents(CString deviceID, const char * logName)
{
}

int IEventCounter::GetEventCount(CString deviceId) {
	return mDeviceFaultCount.at(deviceId);
}
