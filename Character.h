#pragma once
#include "BitMapManager.h"

#define MOVE_SPEED 0.1
#define JUMP_SPEED 0.03


enum IMG_CHARACTER
{
	//Ÿ��Ʋ
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

	CHARACTER_JUMP_MAX_Y = IMG_CHARACTER_Y - 100, //���� ���� ��ġ
	CHARACTER_JUMP_MIN_Y = IMG_CHARACTER_Y, //���� ���� ��ġ == ó���� Y
};

class Character
{
private:
	/*float m_X;
	float m_Y;*/
	RECT m_CharcterRect; //TODO::Rect�� xy�� Draw�� �����Ѵ�.
	IMG m_IMG_NowMotion;
	float m_MoveTime;
	float m_JumpTime;
	CHARACTER_JUMP m_JumpState; //ĳ������ ���� ���¸� �Ǻ�(�Ϲ�, ���� ���, ���� �ϰ�)

public:
	Character();
	~Character();

	void UpdateIMG(float deltaTime);
	void Update_XY(float deltaTime);
	//void Set_XY();
	void Draw(HDC hdc);
};

