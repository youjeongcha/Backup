#pragma once
#include "Mecro.h"

enum TIMER_TYPE // 타이머가 일회성인지 계속 동작하는 것인지 구분
{
	TIMER_TYPE_ONCE, // 일회성
	TIMER_TYPE_LOOP, // 무한반복
	TIMER_TYPE_COUNT // 일정 횟수만 동작 //일정횟수의 기준?
};

class Timer
{
private:
	int m_iOldTime; // 이전시간
	int m_iSecond; // 기준시간
	bool m_bLive; // 타이머 ON / OFF
	TIMER_TYPE Timer_Type;
	int m_iMaxCount;
	int m_iCurCount;
	std::function<void()> m_callbackFunc; //왜 사용했는지 파악

public:
	Timer();
	~Timer();

	void SetTimer(TIMER_TYPE Type, int iSecond, std::function<void()> _callbackFunc, int iMaxCount = -1); // 타이머가 설정
	bool CheckTimer(); // 타이머 기능

};

