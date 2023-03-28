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
	//�̵��Ÿ�
	float m_TravelDistance;
	//�̵� Ű�� ��������
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

