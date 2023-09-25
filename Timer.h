#pragma once
#include <chrono>
// c++11에서 추가된 시간 관련 라이브러리.
// c의 time 보다 다양한 기능을 제공하며 사용이 쉽다.
// 나노(nano) 밀리(milli) 초(seconds) 단위까지 측정 가능.
// OS와 독립적으로 정밀도 높은 시간 측정이 가능.

class Timer
{
private:
	bool isRunning;
#ifdef _WIN32
	std::chrono::time_point<std::chrono::steady_clock> start;
	std::chrono::time_point<std::chrono::steady_clock> stop;
#else
	std::chrono::time_point<std::chrono::system_clock> start;
	std::chrono::time_point<std::chrono::system_clock> stop;
#endif

public:
	Timer();
	~Timer();

	double GetMilisecondsElapesed();

	bool Start();
	bool Stop();
	void Restart();
};

