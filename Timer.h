#pragma once
#include <chrono>
// c++11���� �߰��� �ð� ���� ���̺귯��.
// c�� time ���� �پ��� ����� �����ϸ� ����� ����.
// ����(nano) �и�(milli) ��(seconds) �������� ���� ����.
// OS�� ���������� ���е� ���� �ð� ������ ����.

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

