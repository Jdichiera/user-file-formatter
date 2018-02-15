#include "timer.h"



Timer::Timer()
{
}


Timer::~Timer()
{
}

void Timer::clearTime()
{
	
}

void Timer::startTime()
{
	m_startTime = std::chrono::steady_clock::now();
}

void Timer::endTime()
{
	m_endTime = std::chrono::steady_clock::now();
}

void Timer::getDuration()
{
	m_duration = m_endTime - m_startTime;
	std::cout << "[TIMER] " << m_duration.count() << std::endl;
}
