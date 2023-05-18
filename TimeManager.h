#pragma once
#include "Singleton.h"
#ifndef TIME_MANAGER_H
#define TIME_MANAGER_H

//TimerManager Ŭ������ �����ڰ� private�̱� ������ Singleton class�� friend�� ������ش�.

namespace ENGINE
{
	class TimeManager : public Singleton<TimeManager>
	{
	private:
		UINT32 FPS;
		FLOAT elapseTime; //��� �ð�
		ULONGLONG currTime, lastTime, elapsed;

		TimeManager() : FPS(0), elapseTime(0.0f), currTime(0), lastTime(0) { }
	public:
		void Initialize(UINT32 FPS);
		BOOL Update();
		float DeltaTime() const { return elapseTime; }

		friend Singleton; //friend�� ����ϴ� �ʿ��� public���� ����-����� �����ϸ�, �̱��� new ������ pInstance ���ٿ� ���ǰ� �ִ�.
	};

	#define TimeMgr TimeManager::GetInstance()
}

#endif // !TIME_MANAGER_H