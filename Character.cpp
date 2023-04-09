#include "Character.h"
#include "GameManager.h"

Character::Character()
{
	InitialSet(SET_INIT);
	m_Prev_TravelDiatance = METER_RATIO_100;
}

Character::~Character()
{
}


void Character::InitialSet(SET setType)
{
	switch (setType)
	{
	case SET_INIT: //목숨 + 하단 처리
		m_Life = LIFE_MAX; //목숨
		m_TravelDistance = TRAVELDISTANCE_START; //이동 거리량
		break;
	case SET_RESPAWN:
		m_TravelDistance = m_Prev_TravelDiatance;
		break;
	}

	m_IMG_NowMotion = IMG_CHARACTER_FRONT_1;
	m_JumpState = CHARACTER_JUMP_NONE;
	m_Bump_Check = BUMP_NONE;

	m_X = IMG_CHARACTER_X;
	m_Y = IMG_CHARACTER_Y;

	m_CharcterRect.left = m_X + BUMP_RECT_GAP;
	m_CharcterRect.top = m_Y + BUMP_RECT_GAP;
	m_CharcterRect.right = m_CharcterRect.left + IMG_CHARACTER_COLLIDER_W;
	m_CharcterRect.bottom = m_CharcterRect.top + IMG_CHARACTER_COLLIDER_H;
}


float Character::Update(float deltaTime)
{//질문 ::Update_XY먼저 호출한 다음 Jump를 해줘야하나. 어차피 조건안이면 다음번 함수 접근에 Jump를 참조하므로 상관 없나? 
	float totalDistance;

	Update_Input();

	totalDistance = Update_Move(deltaTime); //키 입력 받기 + 이동

	//이동 거리 백업

	if (totalDistance >= m_Prev_TravelDiatance + METER_GAP) //M 하나 사이의 거리만큼 >>앞으로<< 이동했을 경우 백업한다.
	{
		m_Prev_TravelDiatance += METER_GAP;
	}
	else if (totalDistance <= m_Prev_TravelDiatance) //M 하나 사이의 거리만큼 >>뒤로<< 이동했을 경우 백업한다.
		m_Prev_TravelDiatance -= METER_GAP;

	Update_Animation(deltaTime); //캐릭터 IMG

	Update_Jump(deltaTime);
	return totalDistance;
}

void Character::Update_Animation(float deltaTime)
{
	switch (m_Bump_Check)
	{
	case BUMP_NONE: //게임 진행
	{
		IMG imgLimit = IMG_CHARACTER_BUMP;

		//이동 + 점프
		if (m_AnimationTime >= MOVE_SPEED)
		{
			m_AnimationTime = 0; //초기화는 Update_XY에서 이루어진다.

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

			if ((m_JumpState != CHARACTER_JUMP_NONE))	//점프중이면
				m_IMG_NowMotion = IMG_CHARACTER_FRONT_3;
			//해당 움직임 모션 범위 IMG 안에서만 작동하기 위해 IMG 범위 제한걸기
			else if (m_IMG_NowMotion >= imgLimit) //점프 + 뒤이동의 경우 imgLmit를 넘어서 >=가 필요
				m_IMG_NowMotion = IMG_CHARACTER_FRONT_1;
		}
		break;
	}
	case BUMP_OBSTACLE: //장애물 부딪힘
		if (m_AnimationTime >= BUMP_TIME) //부딪힘 애니메이션 대기 시간
			m_Bump_Check = BUMP_NONE; //m_Bump_Check을 바꾸고(부딪ㅎ미 상태 판별 기준) 함수 GM에서 게임 상태를 리세팅한다.
		else
			m_IMG_NowMotion = IMG_CHARACTER_BUMP;
		break;
	//case BUMP_SCORE:
	//	m_Bump_Check = BUMP_SCORE;
		break;
	case BUMP_GOAL: //승리
		if (m_AnimationTime >= PERFORMANCE_SPEED)
		{
			m_AnimationTime = 0;

			if (m_IMG_NowMotion == IMG_CHARACTER_GOAL_1)
				m_IMG_NowMotion = IMG_CHARACTER_GOAL_2;
			else if (m_IMG_NowMotion == IMG_CHARACTER_GOAL_2)
				m_IMG_NowMotion = IMG_CHARACTER_GOAL_1;
		}
		break;
	}

	m_AnimationTime += deltaTime;
}

void Character::Update_Input()
{
	//if (m_Bump_Check == BUMP_NONE) //캐릭터가 부딪히거나 게임 클리어했을 시 조작 불가
	{
		switch (m_JumpState)
		{
		case CHARACTER_JUMP_NONE:

			if (GetAsyncKeyState(VK_LEFT) & 0x8000)
				m_MoveKey = CHARACTER_MOVE_LEFT;
			else if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
				m_MoveKey = CHARACTER_MOVE_RIGHT;
			else
				m_MoveKey = CHARACTER_MOVE_NONE;

			//점프는 방향고 별도로 체크가 이루어져야 한다. 키 하나만 입력 체크되기 때문에
			if ((GetAsyncKeyState(VK_SPACE) & 0x8000)) //캐릭터가 원 상태일때만 점프 가능
				m_JumpState = CHARACTER_JUMP_UP;
			break;
		default:
			break;
		}
	}
}

float Character::Update_Move(float deltaTime)
{
	float thisTurn_MoveDistance = 0;
	float residualDistance = 0;
	//TODO::마지막 목표에 도달하기 전까지는 배경을 움직인다.(목표가 멀어지면 다시 배경 움직임)
	//GM에서 goal 위치 확인 bool값 받아와서 제한 걸기

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

	//캐릭터 이동 상태
	if (GMMgr->Get_GoalEndPositionCheck())
	{
		m_X += thisTurn_MoveDistance * deltaTime;

		if (m_X <= IMG_CHARACTER_X) //캐릭터 이동 > 배경 이동으로 전환
		{
			m_TravelDistance += m_X - IMG_CHARACTER_X;
			m_X = IMG_CHARACTER_X;
			GMMgr->Set_GoalEndPositionCheck(false);
		}

		m_CharcterRect.left = m_X + BUMP_RECT_GAP;
		m_CharcterRect.right = m_CharcterRect.left + IMG_CHARACTER_COLLIDER_W; //m_CharcterRect.right는 left가 변할때마다 갱신시켜주어야 한다.
	}
	else
	{ //배경 이동 상태
		m_TravelDistance += thisTurn_MoveDistance * deltaTime;

		//거리 이동에 제한을 두기 위해(배경의 움직임 제한, 배경 고정)
		if (m_TravelDistance <= TRAVELDISTANCE_START)
			m_TravelDistance = TRAVELDISTANCE_START;
		else if (m_TravelDistance >= TRAVELDISTANCE_END)
		{ //배경이동이 끝나고 남은 거리 캐릭터에게 주기
			m_X += m_TravelDistance - TRAVELDISTANCE_END; //배경 이동이 끝나고 캐릭터 이동으로 전환되는 것
			m_TravelDistance = TRAVELDISTANCE_END;
		}
	}

	return m_TravelDistance;
}

void Character::Update_Jump(float deltaTime)
{
	switch (m_JumpState)
	{
	case CHARACTER_JUMP_UP:
		m_Y -= CHARACTER_JUMP_GAP * deltaTime;

		if ((m_Y <= CHARACTER_JUMP_MAX_Y))
		{
			m_Y = CHARACTER_JUMP_MAX_Y;
			m_JumpState = CHARACTER_JUMP_DOWN;
		}
		break;
	case CHARACTER_JUMP_DOWN:
		m_Y += CHARACTER_JUMP_GAP * deltaTime;
		if ((m_Y >= CHARACTER_JUMP_MIN_Y))
		{
			m_Y = CHARACTER_JUMP_MIN_Y;
			m_JumpState = CHARACTER_JUMP_NONE;
		}
		break;
	}

	m_CharcterRect.top = m_Y + BUMP_RECT_GAP;
	m_CharcterRect.bottom = m_CharcterRect.top + IMG_CHARACTER_COLLIDER_H;
}


void Character::Draw(HDC hdc)
{
	BitMapMgr->GetImage(m_IMG_NowMotion)->DrawTransparent(hdc, m_X, m_Y, IMG_CHARACTER_W, IMG_CHARACTER_H);
}

bool Character::ReductionLife_End()
{
	m_Life--;
	
	if (m_Life == 0)
		return true;

	return false;
}

bool Character::MoveRightCheck()
{
	if (m_MoveKey == CHARACTER_MOVE_RIGHT)
		return true;
	return false;
}


void Character::Set_XY_GoalMid()
{
	m_X = WIN_PERFORMANCE_X;
	m_Y = WIN_PERFORMANCE_Y;
}