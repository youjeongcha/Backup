#pragma once
#include "Goal.h"
#include "FireObstacle.h"

class ObjectManager
{
private:
	Goal m_Goal;
public:
	//ObjectMgr에서 rect 체크 후에 해당 object의 범위와 캐릭터의 범위가 겹치면 ture를 리턴한다.
	void Draw(HDC hdc);
	void Update(float deltaTime, float thisTurn_MoveDistance);
	bool BumpCheck();

	bool Get_EndCheck() { return m_Goal.Get_EndCheck(); };
};

