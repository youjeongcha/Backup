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
	FirJar m_FirJar[OBSTACLE_COUNT]; //불항아리
	FirRing_B m_FirRing_B[OBSTACLE_COUNT]; //불링Big
	FirRing_S m_FirRing_S; //불링Small
public:

	//초기 세팅
	void InitialSet(SET setType);

	//ObjectMgr에서 rect 체크 후에 해당 object의 범위와 캐릭터의 범위가 겹치면 ture를 리턴한다.
	//왼쪽 링 + 불 항아리 + 골 등의 장애물
	void Draw(HDC hdc);
	void Draw_OnCharacter(HDC hdc);
	void Update(float deltaTime, float thisTurn_MoveDistance, float _Prev_MoveDistance);
	//현재 겹친 object의 속성에 따라 처리를 다르게 한다.(ex.골-게임 클리어, 장애물-목숨감소+게임오버)
	int ColliderCheck(RECT* characterRect);
	

	void DrawCashScoreText(HDC hdc) { m_FirRing_S.DrawCashScoreText(hdc); }

	bool Get_GoalEndPositionCheck() { return m_Goal.Get_EndPositionCheck(); }
	//Goal이 그려짐+이동+충돌체크가 가능한 상태
	void Set_Goal_ActiveCheck(bool _ActiveCheck) { m_Goal.Set_ActiveCheck(_ActiveCheck); }
	void Set_GoalEndPositionCheck(bool _EndPositionCheck) { m_Goal.Set_EndPositionCheck(_EndPositionCheck); }
	//복주머니 해당 ring읜 현재 xy 기준으로 text 출력 좌표 설정
	void Set_Text_XY() { m_FirRing_S.Set_Text_XY(); }
	//void Set_Goal_X(float _X) { m_Goal.Set_Goal_X(_X); } //M가 0이 출력될 차례가 오면 goal의 x 좌표 세팅
};

