#pragma once
#include "BitMapManager.h"

//#define MOVE_SPEED 0.1
#define MOVE_SPEED 0.1
//#define JUMP_SPEED 0.03
#define PERFORMANCE_SPEED 0.4

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


enum CHARACTER_JUMP
{
	CHARACTER_JUMP_NONE,
	CHARACTER_JUMP_UP,
	CHARACTER_JUMP_DOWN,

	///CHARACTER_JUMP_GAP = 10,
	CHARACTER_JUMP_GAP = 300,

	CHARACTER_JUMP_MAX_Y = IMG_CHARACTER_Y - 100, //가장 높은 위치
	CHARACTER_JUMP_MIN_Y = IMG_CHARACTER_Y, //가장 낮은 위치 == 처음의 Y
};

enum WIN_PERFORMANCE
{
	//WIN_PERFORMANCE_X = 0,
	//WIN_PERFORMANCE_Y = 0,
	
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
	float m_MoveTime;
	float m_JumpTime;
	float m_PerformanceTime;

	CHARACTER_JUMP m_JumpState; //캐릭터의 점프 상태를 판별(일반, 점프 상승, 점프 하강)
	//이동거리
	float m_TravelDistance;
	//이동 키를 눌렀는지
	CHARACTER_MOVE m_MoveKey;


	void Update_Animation(float deltaTime);
	void Update_Input();
	float Update_Move(float deltaTime);
	void Update_Jump(float deltaTime);

public:
	Character();
	~Character();

	//초기 세팅
	void InitialSet();

	float Update(float deltaTime);
	void Draw(HDC hdc);

	//게임 승리 후 퍼포먼스
	void UpdatePerformance(float deltaTime);
	//캐릭터를 goal 중앙으로 이동시킨다.
	void Set_XY_GoalMid();

	//목숨 감소 : 목숨이 0이 될 경우 목숨 감소가 불가하므로 false를 리턴하고 GameOver가 된다.
	bool ReductionLife_End();


	float Get_TravelDistance() { return m_TravelDistance; }
	RECT* Get_CharacterRect() { return &m_CharcterRect; }
	int Get_CharacterLife() { return m_Life; }

	void Set_PerformanceMotion() { m_IMG_NowMotion = IMG_CHARACTER_GOAL_1; }
};

