#include "Character.h"
#include "GameManager.h"

Character::Character()
{
	m_IMG_NowMotion = IMG_CHARACTER_FRONT_1;
	m_MoveTime = 0;
	m_JumpTime = 0;
	m_JumpState = CHARACTER_JUMP_NONE;

	m_CharcterRect.left = IMG_CHARACTER_X;
	m_CharcterRect.top = IMG_CHARACTER_Y;
	m_CharcterRect.right = m_CharcterRect.left + IMG_CHARACTER_W;
	m_CharcterRect.bottom = m_CharcterRect.top + IMG_CHARACTER_H;

	m_TravelDistance = TRAVELDISTANCE_START;
}

Character::~Character()
{
}

float Character::Update(float deltaTime)
{//질문 ::Update_XY먼저 호출한 다음 Jump를 해줘야하나. 어차피 조건안이면 다음번 함수 접근에 Jump를 참조하므로 상관 없나? 
	float distance;

	Update_Animation(deltaTime); //캐릭터 IMG
	Update_Input(deltaTime);

	distance = Update_Move(deltaTime); //키 입력 받기 + 이동



	Update_Jump(deltaTime);
	return distance;
}

void Character::Update_Animation(float deltaTime)
{
	IMG imgLimit = IMG_CHARACTER_BUMP;

	if (m_MoveTime >= MOVE_SPEED)
	{
		//m_MoveTime = 0; //초기화는 Update_XY에서 이루어진다.
		if ((m_JumpState != CHARACTER_JUMP_NONE) || (GetAsyncKeyState(VK_SPACE) & 0x8000))	//점프
			m_IMG_NowMotion = IMG_CHARACTER_FRONT_3;

		switch (m_MoveKey)
		{
		case CHARACTER_MOVE_NONE: //멈춤 상태
			m_IMG_NowMotion = IMG_CHARACTER_FRONT_1;
			break;
		case CHARACTER_MOVE_LEFT: //왼쪽 이동
			m_IMG_NowMotion = (IMG)(m_IMG_NowMotion + 1);
			imgLimit = IMG_CHARACTER_FRONT_3; //뒤로 가는 IMG 안에서만 작동하기 위해 IMG 범위 제한걸기
			break;
		case CHARACTER_MOVE_RIGHT: //오른쪽 이동
			m_IMG_NowMotion = (IMG)(m_IMG_NowMotion + 1);
			imgLimit = IMG_CHARACTER_GOAL_1; //달리는 IMG 안에서만 작동하기 위해 IMG 범위 제한걸기
			break;
		default:
			break;
		}
		

		//해당 움직임 모션 범위 IMG 안에서만 작동하기 위해 IMG 범위 제한걸기
		if (m_IMG_NowMotion >= imgLimit) //점프 + 뒤이동의 경우 imgLmit를 넘어서 >=가 필요
 			m_IMG_NowMotion = IMG_CHARACTER_FRONT_1;
	}

	m_MoveTime += deltaTime;
}

void Character::Update_Input(float deltaTime)
{
	//if (m_JumpState != CHARACTER_JUMP_NONE) //Jump 한 상태에서는 이동키 누르지 못하게 해야한다.
	{
		if (GetAsyncKeyState(VK_LEFT) & 0x8000)
			m_MoveKey = CHARACTER_MOVE_LEFT;
		else if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
			m_MoveKey = CHARACTER_MOVE_RIGHT;
		else
			m_MoveKey = CHARACTER_MOVE_NONE;

		//점프는 방향고 별도로 체크가 이루어져야 한다. 키 하나만 입력 체크되기 때문에
		if ((GetAsyncKeyState(VK_SPACE) & 0x8000) && (m_JumpState == CHARACTER_JUMP_NONE)) //캐릭터가 원 상태일때만 점프 가능
			m_JumpState = CHARACTER_JUMP_UP;
	}
}

float Character::Update_Move(float deltaTime)
{
	float thisTurn_MoveDistance = 0;
	//TODO::마지막 목표에 도달하기 전까지는 배경을 움직인다.(목표가 멀어지면 다시 배경 움직임)
	//GM에서 goal 위치 확인 bool값 받아와서 제한 걸기

	if (m_MoveTime >= MOVE_SPEED)
	{
		m_MoveTime = 0;

		//점프는 좌우 이동과 별도로 측정을 해야 좌우이동 중에 점프를 했을 때 배경 끊김 현상이 발생X

		switch (m_MoveKey)
		{
		case CHARACTER_MOVE_LEFT:
			thisTurn_MoveDistance = -TRAVELDISTANCE_MOVE_PER_SEC;
			break;
		case CHARACTER_MOVE_RIGHT:
			thisTurn_MoveDistance = TRAVELDISTANCE_MOVE_PER_SEC;
			break;
		}

		m_TravelDistance += thisTurn_MoveDistance;


		//캐릭터의 x좌표 이동
		if (GMMgr->Get_GoalEndPositionCheck())
			m_CharcterRect.left += thisTurn_MoveDistance;


		//거리 이동에 제한을 두기 위해(배경의 움직임 제한, 배경 고정)
		if (m_TravelDistance < TRAVELDISTANCE_START)
		{
			thisTurn_MoveDistance = 0; 
			m_TravelDistance = TRAVELDISTANCE_START;
		}
		else if (m_TravelDistance > TRAVELDISTANCE_END)
		{
			thisTurn_MoveDistance = 0;
			m_TravelDistance = TRAVELDISTANCE_END;
		}
	}

	m_MoveTime += deltaTime;

	return thisTurn_MoveDistance;
}

void Character::Update_Jump(float deltaTime)
{
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