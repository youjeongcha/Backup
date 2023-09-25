#include "Timer.h"

Timer::Timer() : isRunning(false)
{
	start = std::chrono::high_resolution_clock::now();
	stop = std::chrono::high_resolution_clock::now();
}

Timer::~Timer()
{
}

double Timer::GetMilisecondsElapesed()
{
	std::chrono::duration<double, std::milli> elapsed;
	if (isRunning)
	{
		elapsed = std::chrono::duration<double, std::milli>(std::chrono::high_resolution_clock::now() - start);
		return elapsed.count();
	}
	elapsed = std::chrono::duration<double, std::milli>(stop - start);
	return elapsed.count();
}

bool Timer::Start()
{
	if (isRunning) return false;

	start = std::chrono::high_resolution_clock::now();
	isRunning = true;
	return true;
}

bool Timer::Stop()
{
	if (!isRunning) return false;

	stop = std::chrono::high_resolution_clock::now();
	isRunning = false;
	return true;
}

void Timer::Restart()
{
	start = std::chrono::high_resolution_clock::now();
	isRunning = true;
}
