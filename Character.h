#pragma once
#include "BitMapManager.h"

#define MOVE_SPEED 0.1
#define JUMP_SPEED 0.03

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

	CHARACTER_JUMP_GAP = 10,

	CHARACTER_JUMP_MAX_Y = IMG_CHARACTER_Y - 100, //가장 높은 위치
	CHARACTER_JUMP_MIN_Y = IMG_CHARACTER_Y, //가장 낮은 위치 == 처음의 Y
};


class Character
{
private:
	/*float m_X;
	float m_Y;*/
	RECT m_CharcterRect; //TODO::Rect로 xy와 Draw를 조정한다.
	IMG m_IMG_NowMotion;
	float m_MoveTime;
	float m_JumpTime;
	CHARACTER_JUMP m_JumpState; //캐릭터의 점프 상태를 판별(일반, 점프 상승, 점프 하강)
	//이동거리
	float m_TravelDistance;
	//이동 키를 눌렀는지
	CHARACTER_MOVE m_MoveKey;


	void Update_Animation(float deltaTime);
	void Update_Input(float deltaTime);
	float Update_Move(float deltaTime);
	void Update_Jump(float deltaTime);

public:
	Character();
	~Character();

	float Update(float deltaTime);
	void Draw(HDC hdc);

	float Get_TravelDistance() { return m_TravelDistance; }
};

