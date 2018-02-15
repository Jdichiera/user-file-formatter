#pragma once
#include <chrono>
#include <string>
#include <iostream>
class Timer
{
public:
	Timer();
	~Timer();

	void clearTime();
	void startTime();
	void endTime();
	void getDuration();

private:
	std::chrono::steady_clock::time_point m_startTime;
	std::chrono::steady_clock::time_point m_endTime;
	std::chrono::duration<double> m_duration;
};

