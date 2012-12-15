#include "DXTimer.h"

//----------------------------------------------------------------
// Author: Dhanus
//----------------------------------------------------------------

//----------------------------------------------------------------
//					DXTimer Definition
//----------------------------------------------------------------


DXTimer::DXTimer()
{
	m_secondsPerCount  = 0.0f;
	m_deltaTime = -1.0f;
	m_baseTime = 0.0f;
	m_pausedTime = 0.0f;
	m_prevTime = 0.0f;
	m_currTime = 0.0f;
	m_stopped = false;

	__int64 countsPerSec;
	QueryPerformanceFrequency((LARGE_INTEGER*)&countsPerSec);
	m_secondsPerCount  = 1.0f / (double)countsPerSec;
}

//----------------------------------------------------------------
// Name: float DXTimer::GetTotalTime()const
// Desc: Return the total time elapsed since from the point of calling
//		 Reset (ignoring the paused time)
//----------------------------------------------------------------
float DXTimer::GetTotalTime()const
{
	if(m_stopped)
	{
		return (m_stopTime - m_pausedTime - m_baseTime) * m_secondsPerCount;
	}
	else
		return (m_currTime - m_pausedTime - m_baseTime) * m_secondsPerCount;
}

float DXTimer::GetPausedTime()const
{
	return m_pausedTime;
}

//----------------------------------------------------------------
// Name: void DXTimer::Stop()
// Desc: Stop the timer (Pause)
//----------------------------------------------------------------
void DXTimer::Stop()
{
	if(!m_stopped)
	{
		QueryPerformanceCounter((LARGE_INTEGER*)&m_stopTime);
		m_stopped = true;
	}
}

//----------------------------------------------------------------
// Name: void DXTimer::Start()
// Desc: Resume the timer if it was stopped state
//----------------------------------------------------------------
void DXTimer::Start()
{
	
	if(m_stopped)
	{
		__int64 resumeTime;
		QueryPerformanceCounter((LARGE_INTEGER*)&resumeTime);
		m_pausedTime += (resumeTime - m_stopTime);
		m_prevTime = resumeTime;
		m_stopTime = 0;
		m_stopped = false;
	}
}

void DXTimer::Reset()
{
	__int64 currentTime;
	QueryPerformanceCounter((LARGE_INTEGER*)&currentTime);
	m_baseTime = m_prevTime = currentTime;
	m_stopped = false;
	m_stopTime = 0;
}

float DXTimer::GetDeltaTime()const
{
	return m_deltaTime;
}

//----------------------------------------------------------------
// Name: void DXTimer::Tick()
// Desc: Called in each frame to advance the timer
//----------------------------------------------------------------
void DXTimer::Tick()
{
	// if we stoped
	if(m_stopped)
	{
		m_deltaTime = 0.0f;
		return;
	}

	__int64 currentTime;
	QueryPerformanceCounter((LARGE_INTEGER*)&currentTime);
	m_deltaTime = (currentTime - m_prevTime) * m_secondsPerCount;
	m_prevTime = currentTime;

	//note According to the DXSDK the value can be neative if the 
	// processor in power save mode / shuffled to another processor
	if(m_deltaTime < 0.0f)
		m_deltaTime = 0.0f;

}