#pragma once
#include "Singleton.h"
#ifndef TIME_MANAGER_H
#define TIME_MANAGER_H

//TimerManager 클래스의 생성자가 private이기 때문에 Singleton class를 friend로 만들어준다.

namespace ENGINE
{
	class TimeManager : public Singleton<TimeManager>
	{
	private:
		UINT32 FPS;
		FLOAT elapseTime; //경과 시간
		ULONGLONG currTime, lastTime, elapsed;

		TimeManager() : FPS(0), elapseTime(0.0f), currTime(0), lastTime(0) { }
	public:
		void Initialize(UINT32 FPS);
		BOOL Update();
		float DeltaTime() const { return elapseTime; }

		friend Singleton; //?
	};

	#define TimeMgr TimeManager::GetInstance()
}

#endif // !TIME_MANAGER_H