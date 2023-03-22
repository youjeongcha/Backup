#pragma once
#include "BitMapManager.h"

#define MOVE_SPEED 0.1

enum IMG_CHARACTER
{
	//Ÿ��Ʋ
	IMG_CHARACTER_X = 100,
	IMG_CHARACTER_Y = MAIN_H - 150,
	IMG_CHARACTER_W = 60,
	IMG_CHARACTER_H = IMG_CHARACTER_W + 10,
};

class Character
{
private:
	/*float m_X;
	float m_Y;*/
	RECT m_CharcterRect; //TODO::Rect�� xy�� Draw�� �����Ѵ�.
	IMG m_IMG_NowMotion;
	float m_MoveTime;

public:
	Character();
	~Character();

	void UpdateIMG(float deltaTime);
	void Update_XY(float deltaTime);
	//void Set_XY();
	void Draw(HDC hdc);
};

