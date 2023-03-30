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

	bool Get_GoalEndPositionCheck() { return m_Goal.Get_EndPositionCheck(); };
	void Set_ActiveCheck(bool _ActiveCheck) { m_Goal.Set_ActiveCheck(_ActiveCheck); }
	//void Set_Goal_X(float _X) { m_Goal.Set_Goal_X(_X); } //M가 0이 출력될 차례가 오면 goal의 x 좌표 세팅
};

