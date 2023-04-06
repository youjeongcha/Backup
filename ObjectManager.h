#pragma once
#include "Goal.h"
#include "FirJar.h"
#include "FirRing_B.h"
#include "FirRing_S.h"

enum OBSTACLE_COUNT
{
	OBSTACLE_ONE,
	OBSTACLE_TWO,
	OBSTACLE_COUNT,
};

class ObjectManager
{
private:
	Goal m_Goal;
	FirJar m_FirJar[OBSTACLE_COUNT];
public:

	//초기 세팅
	void InitialSet();

	//ObjectMgr에서 rect 체크 후에 해당 object의 범위와 캐릭터의 범위가 겹치면 ture를 리턴한다.
	void Draw(HDC hdc);
	void Update(float thisTurn_MoveDistance, float _Prev_MoveDistance);
	//ObjectMgr에서 rect 체크 후에 해당 object의 범위와 캐릭터의 범위가 겹치면 true를 리턴한다.
	bool ColliderCheck_Goal(RECT* characterRect);
	bool ColliderCheck_Obstacle(RECT* characterRect);
	

	bool Get_GoalEndPositionCheck() { return m_Goal.Get_EndPositionCheck(); };
	//Goal이 그려짐+이동+충돌체크가 가능한 상태
	void Set_Goal_ActiveCheck(bool _ActiveCheck) { m_Goal.Set_ActiveCheck(_ActiveCheck); }
	void Set_GoalEndPositionCheck(bool _EndPositionCheck) { m_Goal.Set_EndPositionCheck(_EndPositionCheck); }
	//void Set_Goal_X(float _X) { m_Goal.Set_Goal_X(_X); } //M가 0이 출력될 차례가 오면 goal의 x 좌표 세팅
};

