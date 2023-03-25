#pragma once
#include "BitMapManager.h"

#define MOVE_SPEED 0.1
#define JUMP_SPEED 0.03


enum IMG_CHARACTER
{
	//타이틀
	IMG_CHARACTER_X = 100,
	IMG_CHARACTER_Y = MAIN_H - 150,
	IMG_CHARACTER_W = 60,
	IMG_CHARACTER_H = IMG_CHARACTER_W + 10,
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

//-----------거리-------------
enum TRAVELDISTANCE //사실상 배경이 움직이는 범위값이라고 보아도 무방하다
{
	TRAVELDISTANCE_START = 0,
	TRAVELDISTANCE_END = 1000, //골이 나타나고 배경 움직임 > 캐릭터 움직임으로 전환되는 시점

	TRAVELDISTANCE_MOVE_PER_SEC = 10, //초당 움직이는 거리
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


	void UpdateIMG(float deltaTime);
	float Update_XY(float deltaTime);
	void Update_Jump(float deltaTime);

public:
	Character();
	~Character();

	float Update(float deltaTime);
	void Draw(HDC hdc);

	float Get_TravelDistance() { return m_TravelDistance; }
};

