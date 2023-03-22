#include "Character.h"
#include "GameManager.h"

Character::Character()
{
	m_IMG_NowMotion = IMG_CHARACTER_FRONT_1;
	//m_X = IMG_CHARACTER_X;
	//m_Y = IMG_CHARACTER_Y;
	m_CharcterRect.left = IMG_CHARACTER_X;
	m_CharcterRect.top = IMG_CHARACTER_Y;
	m_CharcterRect.right = m_CharcterRect.left + IMG_CHARACTER_W;
	m_CharcterRect.bottom = m_CharcterRect.top + IMG_CHARACTER_H;
}

Character::~Character()
{
}

void Character::UpdateIMG(float deltaTime)
{
	if (m_MoveTime >= MOVE_SPEED)
	{
		m_MoveTime = 0;

		if (m_IMG_NowMotion == IMG_CHARACTER_FRONT_3)
			m_IMG_NowMotion = IMG_CHARACTER_FRONT_1;

		m_IMG_NowMotion = (IMG)(m_IMG_NowMotion + 1);
	}

	m_MoveTime += deltaTime;
}

void Character::Update_XY(float deltaTime)
{
	//TODO::마지막 목표에 도달하기 전까지는 배경을 움직인다.
	if (GetAsyncKeyState(VK_SPACE) & 0x8000)
	{
		m_CharcterRect.top -= 20;
	}
	else if (GetAsyncKeyState(VK_LEFT) & 0x8000)
		m_CharcterRect.left -= 20;
	else if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
		m_CharcterRect.left += 20;


}

//void Character::Set_XY()
//{
//}

void Character::Draw(HDC hdc)
{
	BitMapMgr->GetImage(m_IMG_NowMotion)->DrawTransparent(hdc, m_CharcterRect.left, m_CharcterRect.top, IMG_CHARACTER_W, IMG_CHARACTER_H);
}
