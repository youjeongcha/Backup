#include "Character.h"
#include "GameManager.h"

Character::Character()
{
	m_IMG_NowMotion = IMG_CHARACTER_FRONT_1;
	m_MoveTime = 0;
	m_JumpTime = 0;
	m_JumpState = CHARACTER_JUMP_NONE;
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
	IMG imgLimit = IMG_CHARACTER_BUMP;

	if (m_MoveTime >= MOVE_SPEED)
	{
		m_MoveTime = 0;

		if ((m_JumpState != CHARACTER_JUMP_NONE) || (GetAsyncKeyState(VK_SPACE) & 0x8000))	//점프
			m_IMG_NowMotion = IMG_CHARACTER_FRONT_3;
		else if (GetAsyncKeyState(VK_RIGHT) & 0x8000) //오른쪽 이동
		{
			m_IMG_NowMotion = (IMG)(m_IMG_NowMotion + 1);

			imgLimit = IMG_CHARACTER_GOAL_1; //달리는 IMG 안에서만 작동하기 위해 IMG 범위 제한걸기
		}
		else if (GetAsyncKeyState(VK_LEFT) & 0x8000) //왼쪽 이동
		{
			m_IMG_NowMotion = (IMG)(m_IMG_NowMotion + 1);
			
			imgLimit = IMG_CHARACTER_FRONT_3; //뒤로 가는 IMG 안에서만 작동하기 위해 IMG 범위 제한걸기
		}
		else //멈춤 상태
			m_IMG_NowMotion = IMG_CHARACTER_FRONT_1;

		//해당 움직임 모션 범위 IMG 안에서만 작동하기 위해 IMG 범위 제한걸기
		if (m_IMG_NowMotion >= imgLimit) //점프 + 뒤이동의 경우 imgLmit를 넘어서 >=가 필요
 			m_IMG_NowMotion = IMG_CHARACTER_FRONT_1;
	}

	m_MoveTime += deltaTime;
}

void Character::Update_XY(float deltaTime)
{
	//TODO::마지막 목표에 도달하기 전까지는 배경을 움직인다.(목표가 멀어지면 다시 배경 움직임)
	//GM에서 goal 위치 확인 bool값 받아와서 제한 걸기

	if (GetAsyncKeyState(VK_SPACE) & 0x8000 && (m_JumpState == CHARACTER_JUMP_NONE)) //캐릭터가 원 상태일때만 점프 가능
		m_JumpState = CHARACTER_JUMP_UP;
	/*else if (GetAsyncKeyState(VK_LEFT) & 0x8000)
		m_CharcterRect.left -= 20;
	else if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
		m_CharcterRect.left += 20;*/


	//캐릭터가 점프 키를 누르고 공중에 떠있는 상태
	if (m_JumpState != CHARACTER_JUMP_NONE) 
	{
		if (m_JumpTime >= JUMP_SPEED)
		{
			m_JumpTime = 0;
			
			if ((m_JumpState == CHARACTER_JUMP_UP) && (m_CharcterRect.top <= CHARACTER_JUMP_MAX_Y))
			{
				m_CharcterRect.top = CHARACTER_JUMP_MAX_Y;
				m_JumpState = CHARACTER_JUMP_DOWN;
			}
			else if ((m_JumpState == CHARACTER_JUMP_DOWN) && (m_CharcterRect.top >= CHARACTER_JUMP_MIN_Y))
			{
				m_CharcterRect.top = CHARACTER_JUMP_MIN_Y;
				m_JumpState = CHARACTER_JUMP_NONE;
			}

			switch (m_JumpState)
			{
			case CHARACTER_JUMP_UP:
				m_CharcterRect.top -= CHARACTER_JUMP_GAP;
				break;
			case CHARACTER_JUMP_DOWN:
				m_CharcterRect.top += CHARACTER_JUMP_GAP;
				break;
			}
		}
		
		m_JumpTime += deltaTime;
	}
}

//void Character::Set_XY()
//{
//}

void Character::Draw(HDC hdc)
{
	BitMapMgr->GetImage(m_IMG_NowMotion)->DrawTransparent(hdc, m_CharcterRect.left, m_CharcterRect.top, IMG_CHARACTER_W, IMG_CHARACTER_H);
}