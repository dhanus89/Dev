#ifndef DXTIMER_H
#define DXTIMER_H
#include <Windows.h>
/*
	Author: Dhanus
	Class DXTimer implements High Precision Timer
*/

class DXTimer
{
public:
	DXTimer();


	float GetTotalTime()const;
	float GetDeltaTime()const;
	void Reset();// 
	void Start();
	void Stop();
	void Tick();// called in every Frame
	float GetPausedTime()const;

private:
	__int64 m_currTime;
	__int64 m_baseTime;// the time at the Applicaiton started
	__int64 m_pausedTime;// all time that passes during the app is being paused
	__int64 m_stopTime;// the time at the applciation being paused.
	__int64 m_prevTime;

	double m_secondsPerCount;
	double m_deltaTime;

	bool m_stopped;
};



#endif