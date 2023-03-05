#pragma once
#include "Mecro.h"

enum TIMER_TYPE // Ÿ�̸Ӱ� ��ȸ������ ��� �����ϴ� ������ ����
{
	TIMER_TYPE_ONCE, // ��ȸ��
	TIMER_TYPE_LOOP, // ���ѹݺ�
	TIMER_TYPE_COUNT // ���� Ƚ���� ���� //����Ƚ���� ����?
};

class Timer
{
private:
	int m_iOldTime; // �����ð�
	int m_iSecond; // ���ؽð�
	bool m_bLive; // Ÿ�̸� ON / OFF
	TIMER_TYPE Timer_Type;
	int m_iMaxCount;
	int m_iCurCount;
	std::function<void()> m_callbackFunc; //�� ����ߴ��� �ľ�

public:
	Timer();
	~Timer();

	void SetTimer(TIMER_TYPE Type, int iSecond, std::function<void()> _callbackFunc, int iMaxCount = -1); // Ÿ�̸Ӱ� ����
	bool CheckTimer(); // Ÿ�̸� ���

};

