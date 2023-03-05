#include "Timer.h"

Timer::Timer()
{
}
Timer::~Timer()
{
}
void Timer::SetTimer(TIMER_TYPE Type, int iSecond, std::function<void()> _callbackFunc, int iMaxCount) //기본값 -1로 설정
{//함수 포인터
	Timer_Type = Type;
	m_iSecond = iSecond;
	m_bLive = true; //지속적 사용, 일회성 사용 판단
	m_iOldTime = clock();
	m_iMaxCount = iMaxCount;
	if (Timer_Type == TIMER_TYPE_COUNT)
		m_iCurCount = 0; //사용하므로 0으로 초기화
	else
		m_iCurCount = -1; //사용하지 않을거라 -1으로 설정
	m_callbackFunc = _callbackFunc; //함수포인터
}
bool Timer::CheckTimer()
{//리턴받은 bool 사용을 안 함 //일단 리턴 true일때만 움직이고 false는 안 움직인다.
	if (m_bLive == true && clock() - m_iOldTime >= m_iSecond)
	{
		m_callbackFunc(); //_callbackFunc에 무엇을 받아오는지에 따라
		switch (Timer_Type)
		{
		case TIMER_TYPE_ONCE:
			m_bLive = false; //일회성 사용 판단
			return true;
			break;
		case TIMER_TYPE_LOOP:
			m_iOldTime = clock();
			return true;
			break;
		case TIMER_TYPE_COUNT:
			m_iCurCount++; //m_iCurCount을 0으로 설정해둔 이유
			if(m_iCurCount == m_iMaxCount) //m_iMaxCount 현재 코드에서 사용 안 함
				m_bLive = false; //지속적 사용 후 횟수 다 차면 사용 끝.
			else
				m_iOldTime = clock();
			return true;
			break;
		default: //dfault값이 있는 이유 : 코드 확장 고려 보험
			break;
		}
	}
	else
		return false;
}