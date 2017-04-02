#include "IEventCounter.h"



IEventCounter::IEventCounter()
{
}


IEventCounter::~IEventCounter()
{
}

void IEventCounter::ParseEvents(CString deviceID, const char * logName)
{
	std::ifstream logFile(logName);
	int count(0), prevStage(0), currentStage(0);
	char currentState('A');
	std::string date, time, value;
	while (logFile >> date >> time >> value) {

	}
	logFile.close();
	mDeviceFaultCount.at(deviceID) += count;
}

int IEventCounter::GetEventCount(CString deviceId) {
	return mDeviceFaultCount.at(deviceId);
}
