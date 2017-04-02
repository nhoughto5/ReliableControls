# Log Event Detector
This project was completed in correspondence with the interview test provided by [Reliable Controls](http://www.reliablecontrols.com/)

### Objective
Implement a processor that looks for and counts specific patterns in an event log.

### Problem Overview

A design flaw has been found in a type of HVAC unit. The unit can be in one of four stages (0-3) depending on environmental conditions. The manufacturer has noted a design flaw where the unit can accidentally go through a specific sequence of stages leading to possible damage. The manufacturer has noted that a fault is indicated by four operations that occur in sequence:
1. Stage 3 for five minutes or more
2. Stage 2,
3. Any number of cycles between stage 2 and 3 for any duration
4. Stage 0

Your task is to implement a log parser that detects and counts occurrences of this fault sequence.
You should create a class called IEventCounter which supplies an implementation for two methods:
1. void ParseEvents(CString deviceID, const char* logName) – Open and parse a file of
operation records associated with the given device ID, and count occurrences of the “fault”
sequence. The name of the file is indicated by logName.
2. int GetEventCount(CString deviceId) – Gets the total number of “fault” sequences
observed for the given device.

## Solution
The system which parses the logs employs a finite state machine (FSM) logic design. As can be seen in the image below there are three states in the machine.
![alt tag](http://i66.tinypic.com/20jlijs.png)
When the log parser is detecting that the device is operating normally the FSM stays within state 'A'. When criteria 1 above is detected it moves to state 'B', other wise it remains in state 'A'. While in state 'B' the system remains such unless a stage 0 or 1 is read from the logs. If a 1 is read it returns to state 'A'. If a 0 is read it moves to state 'C' where an error is detected. State 'C' is a redundant state. As soon as it reaches state 'C' it always returns to state 'A' immediately after incrementing the error count. The code implementation of the ParseEvents method does not employ state 'C'; it is used only to explain the logic behind its operation.

The IEventCounter class has a static map data structure as a member variable. This map is used to keep track of the log count for multiple devices. The GetEventCount method simply returns the value in the map with the 'deviceId' key.

## Testing
The IEventCounter class is tested using the [Catch](https://github.com/philsquared/Catch) test framework. The main file has no main method. The Catch framework runs a main from within itself which calls each of the test cases. The test cases generate a list of logs which are then fed into the IEventCounter class. The helper methods 'makeNormalLogs' and 'getFault' can be used to automatically generate as many faults and as much normal operation as the test desires.

## Threading
The IEventCounter class contains two static members which are shared between potential threads. The first is the 'mDeviceFaultCount' map which stores the accumulated log error counts. Secondly there is a mutex, this must be shared between all threads to ensure the shared resource is never accessed by multiple threads simultaneously. 

In the implementation file, when the recorded count of errors is added to the map value it must be locked. A unique lock is used because it calls unlock on the mutex in it's destructor, this is why it is given a closed scope. The benefit of this is that in case some exception is thrown, the mutex will unlock when leaving the scope in which it is defined.

