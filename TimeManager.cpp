#include "TimeManager.h"

namespace ENGINE
{
	void TimeManager::Initialize(UINT32 FPS)
	{
		this->FPS = 1000 / FPS;
		currTime = lastTime = GetTickCount64();
	}
	BOOL TimeManager::Update()
	{
		currTime = GetTickCount64();

		elapsed = (currTime - lastTime);
		if (elapsed < FPS)
			return false;

		elapseTime = elapsed * 0.001f; //소수점 오차를 줄이기 위해
		lastTime = currTime;

		return true;
	}
}