#pragma once
#include "BitMapManager.h"
#include "framework.h"

#define MOVE_SPEED 0.1
#define PERFORMANCE_SPEED 0.4
#define BUMP_TIME 1

enum LIFE
{
	LIFE_MAX = 3,
};

enum CHARACTER_MOVE
{
	CHARACTER_MOVE_NONE,
	CHARACTER_MOVE_LEFT,
	CHARACTER_MOVE_RIGHT,
};




enum WIN_PERFORMANCE //클리어 퍼모먼스의 XY좌표
{
	WIN_PERFORMANCE_X = GOAL_IMG_ARRIVE_X,// + GOAL_IMG_W / 2,
	WIN_PERFORMANCE_Y = GOAL_IMG_Y - IMG_CHARACTER_H + 7,
};

class Character
{
private:
	float m_X;
	float m_Y;
	RECT m_CharcterRect; //TODO::Rect로 xy와 Draw를 조정한다.
	//유저 목숨
	int m_Life;
	IMG m_IMG_NowMotion;
	float m_AnimationTime;

	CHARACTER_JUMP m_JumpState; //캐릭터의 점프 상태를 판별(일반, 점프 상승, 점프 하강)
	//이동거리
	float m_TravelDistance;
	//이동 키를 눌렀는지
	CHARACTER_MOVE m_MoveKey;
	//현재 object와 접촉 상태인지
	BUMP_CHECK m_Bump_Check;


	void Update_Input();
	float Update_Move(float deltaTime);
	void Update_Jump(float deltaTime);

public:
	Character();
	~Character();

	//초기 세팅
	void InitialSet(SET setType);

	float Update(float deltaTime);
	void Update_Animation(float deltaTime); //GameClear하고 Animation 보여줄때 조작 되면 안되므로 이것만 따로 호출
	void Draw(HDC hdc);

	//캐릭터를 goal 중앙으로 이동시킨다.
	void Set_XY_GoalMid();

	//목숨 감소 : 목숨이 0이 될 경우 목숨 감소가 불가하므로 false를 리턴하고 GameOver가 된다.
	bool ReductionLife_End();

	RECT* Get_CharacterRect() { return &m_CharcterRect; }


	float Get_TravelDistance() { return m_TravelDistance; }
	int Get_CharacterLife() { return m_Life; }
	BUMP_CHECK Get_Bump_Check() { return m_Bump_Check; }

	void Set_PerformanceMotion() { m_IMG_NowMotion = IMG_CHARACTER_GOAL_1; }
	void Set_Bump_Check(BUMP_CHECK _Bump_Check) { m_Bump_Check = _Bump_Check; };
};

