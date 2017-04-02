#include "IEventCounter.h"

/*
	Initialize static members of IEventCounter class
	================================================
*/

std::mutex IEventCounter::mMutex;

std::map<CString, int> initMap() {
	std::map<CString, int> i;
	return i;
}
std::map<CString, int> IEventCounter::mDeviceFaultCount(initMap());
//================================================================

IEventCounter::IEventCounter()
{
}


IEventCounter::~IEventCounter()
{
}

bool IEventCounter::greaterThanFiveMinutes(TimeStamp &currentTime, TimeStamp &previousTime) {
	if (currentTime.year > previousTime.year || currentTime.month > previousTime.month || currentTime.day > previousTime.day) {
		return true;
	}
	else {
		// More than an hour has passed
		if (currentTime.hour - previousTime.hour > 1) {
			return true;
		}
		// Within the same hour
		if (currentTime.hour == previousTime.hour) {
			int curMin = currentTime.minute * 60 + currentTime.second;
			int prevMin = previousTime.minute * 60 + previousTime.second;
			if (curMin - prevMin > (5 * 60)) {
				return true;
			}
			else {
				return false;
			}
		}
		// In the subsequent hour
		else {
			int curMin = (currentTime.minute + 60) * 60 + currentTime.second;
			int prevMin = previousTime.minute * 60 + previousTime.second;
			if (curMin - prevMin > (5 * 60)) {
				return true;
			}
			else {
				return false;
			}
		}
	}
}

void IEventCounter::ParseEvents(CString deviceID, const char * logName)
{
	std::ifstream logFile(logName);
	int count(0), prevStage(0);
	char currentState('A');
	std::string dateStr, timeStr, valueStr;
	TimeStamp prevTimeStamp;

	while (logFile >> dateStr >> timeStr >> valueStr) {
		TimeStamp currentTime(dateStr, timeStr);
		int currentStage = std::stoi(valueStr);

		//Transition to state B if time greater than 5 minutes
		if (currentState == 'A' && currentStage == 2 && prevStage == 3) {
			//5 min time has expired
			if (greaterThanFiveMinutes(currentTime, prevTimeStamp)) {
				currentState = 'B';
			}
		}
		if (currentState == 'A' && prevStage != 3) {
			prevTimeStamp = currentTime;
		}

		//In stage b and reset
		if (currentState == 'B' && currentStage == 1) {
			currentState = 'A';
		}

		//Fault
		if (currentState == 'B' && currentStage == 0) {
			currentState = 'A';
			count++;
			currentStage = 0;
		}
		prevStage = currentStage;
	}
	logFile.close();

	// Close scope to allow the unique lock to break
	// at the end of the scope.
	{
		std::unique_lock<std::mutex> lock(mMutex);
		mDeviceFaultCount[deviceID] += count;
	}
}

int IEventCounter::GetEventCount(CString deviceId) {
	return mDeviceFaultCount.at(deviceId);
}
