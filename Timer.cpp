#include "Timer.h"

Timer::Timer()
{
}
Timer::~Timer()
{
}
void Timer::SetTimer(TIMER_TYPE Type, int iSecond, std::function<void()> _callbackFunc, int iMaxCount) //�⺻�� -1�� ����
{//�Լ� ������
	Timer_Type = Type;
	m_iSecond = iSecond;
	m_bLive = true; //������ ���, ��ȸ�� ��� �Ǵ�
	m_iOldTime = clock();
	m_iMaxCount = iMaxCount;
	if (Timer_Type == TIMER_TYPE_COUNT)
		m_iCurCount = 0; //����ϹǷ� 0���� �ʱ�ȭ
	else
		m_iCurCount = -1; //������� �����Ŷ� -1���� ����
	m_callbackFunc = _callbackFunc; //�Լ�������
}
bool Timer::CheckTimer()
{//���Ϲ��� bool ����� �� �� //�ϴ� ���� true�϶��� �����̰� false�� �� �����δ�.
	if (m_bLive == true && clock() - m_iOldTime >= m_iSecond)
	{
		m_callbackFunc(); //_callbackFunc�� ������ �޾ƿ������� ����
		switch (Timer_Type)
		{
		case TIMER_TYPE_ONCE:
			m_bLive = false; //��ȸ�� ��� �Ǵ�
			return true;
			break;
		case TIMER_TYPE_LOOP:
			m_iOldTime = clock();
			return true;
			break;
		case TIMER_TYPE_COUNT:
			m_iCurCount++; //m_iCurCount�� 0���� �����ص� ����
			if(m_iCurCount == m_iMaxCount) //m_iMaxCount ���� �ڵ忡�� ��� �� ��
				m_bLive = false; //������ ��� �� Ƚ�� �� ���� ��� ��.
			else
				m_iOldTime = clock();
			return true;
			break;
		default: //dfault���� �ִ� ���� : �ڵ� Ȯ�� ��� ����
			break;
		}
	}
	else
		return false;
}