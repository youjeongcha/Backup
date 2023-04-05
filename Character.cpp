#include "Character.h"
#include "GameManager.h"

Character::Character()
{
	InitialSet();
	//m_IMG_NowMotion = IMG_CHARACTER_FRONT_1;
	//m_MoveTime = 0;
	//m_JumpTime = 0;
	//m_JumpState = CHARACTER_JUMP_NONE;
	//m_Life = LIFE_MAX; //���

	//m_CharcterRect.left = m_X = IMG_CHARACTER_X;
	//m_CharcterRect.top = m_Y = IMG_CHARACTER_Y;
	//m_CharcterRect.right = m_CharcterRect.left + IMG_CHARACTER_W;
	//m_CharcterRect.bottom = m_CharcterRect.top + IMG_CHARACTER_H;

	//m_TravelDistance = TRAVELDISTANCE_START;
}

Character::~Character()
{
}


void Character::InitialSet()
{
	m_IMG_NowMotion = IMG_CHARACTER_FRONT_1;
	m_MoveTime = 0;
	m_JumpTime = 0;
	m_JumpState = CHARACTER_JUMP_NONE;
	m_Life = LIFE_MAX; //���

	m_CharcterRect.left = m_X = IMG_CHARACTER_X;
	m_CharcterRect.top = m_Y = IMG_CHARACTER_Y;
	m_CharcterRect.right = m_CharcterRect.left + IMG_CHARACTER_W;
	m_CharcterRect.bottom = m_CharcterRect.top + IMG_CHARACTER_H;

	m_TravelDistance = TRAVELDISTANCE_START;
}


float Character::Update(float deltaTime)
{//���� ::Update_XY���� ȣ���� ���� Jump�� ������ϳ�. ������ ���Ǿ��̸� ������ �Լ� ���ٿ� Jump�� �����ϹǷ� ��� ����? 
	float totalDistance;

	Update_Animation(deltaTime); //ĳ���� IMG
	Update_Input();

	totalDistance = Update_Move(deltaTime); //Ű �Է� �ޱ� + �̵�

	Update_Jump(deltaTime);
	return totalDistance;
}

void Character::Update_Animation(float deltaTime)
{
	IMG imgLimit = IMG_CHARACTER_BUMP;

	if (m_MoveTime >= MOVE_SPEED)
	{
		m_MoveTime = 0; //�ʱ�ȭ�� Update_XY���� �̷������.


		switch (m_MoveKey)
		{
		case CHARACTER_MOVE_NONE: //���� ����
			m_IMG_NowMotion = IMG_CHARACTER_FRONT_1;
			break;
		case CHARACTER_MOVE_LEFT: //���� �̵�
			m_IMG_NowMotion = (IMG)(m_IMG_NowMotion + 1);
			imgLimit = IMG_CHARACTER_FRONT_3; //�ڷ� ���� IMG �ȿ����� �۵��ϱ� ���� IMG ���� ���Ѱɱ�
			break;
		case CHARACTER_MOVE_RIGHT: //������ �̵�
			m_IMG_NowMotion = (IMG)(m_IMG_NowMotion + 1);
			imgLimit = IMG_CHARACTER_GOAL_1; //�޸��� IMG �ȿ����� �۵��ϱ� ���� IMG ���� ���Ѱɱ�
			break;
		default:
			break;
		}
		
		if ((m_JumpState != CHARACTER_JUMP_NONE))	//�������̸�
			m_IMG_NowMotion = IMG_CHARACTER_FRONT_3;
		//�ش� ������ ��� ���� IMG �ȿ����� �۵��ϱ� ���� IMG ���� ���Ѱɱ�
		else if (m_IMG_NowMotion >= imgLimit) //���� + ���̵��� ��� imgLmit�� �Ѿ >=�� �ʿ�
 			m_IMG_NowMotion = IMG_CHARACTER_FRONT_1;
	}

	m_MoveTime += deltaTime;
}

void Character::Update_Input()
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

		//������ ����� ������ üũ�� �̷������ �Ѵ�. Ű �ϳ��� �Է� üũ�Ǳ� ������
		if ((GetAsyncKeyState(VK_SPACE) & 0x8000)) //ĳ���Ͱ� �� �����϶��� ���� ����
			m_JumpState = CHARACTER_JUMP_UP;
		break;

	default:
		break;
	}
}

float Character::Update_Move(float deltaTime)
{
	float thisTurn_MoveDistance = 0;
	float residualDistance = 0;
	//TODO::������ ��ǥ�� �����ϱ� �������� ����� �����δ�.(��ǥ�� �־����� �ٽ� ��� ������)
	//GM���� goal ��ġ Ȯ�� bool�� �޾ƿͼ� ���� �ɱ�

	//if (m_MoveTime >= MOVE_SPEED)
	{
		//m_MoveTime = 0;

		//������ �¿� �̵��� ������ ������ �ؾ� �¿��̵� �߿� ������ ���� �� ��� ���� ������ �߻�X

		switch (m_MoveKey)
		{
		case CHARACTER_MOVE_LEFT:
			thisTurn_MoveDistance = -TRAVELDISTANCE_MOVE_PER_SEC;
			break;
		case CHARACTER_MOVE_RIGHT:
			thisTurn_MoveDistance = TRAVELDISTANCE_MOVE_PER_SEC;
			break;
		}

		//ĳ���� �̵� ����
		if (GMMgr->Get_GoalEndPositionCheck())
		{
			m_X += thisTurn_MoveDistance * deltaTime;

			if (m_X <= IMG_CHARACTER_X) //ĳ���� �̵� > ��� �̵����� ��ȯ
			{
				m_TravelDistance += m_X - IMG_CHARACTER_X;
				m_X = IMG_CHARACTER_X;
				GMMgr->Set_GoalEndPositionCheck(false);
			}
			m_CharcterRect.left = m_X;
		}
		else
		{ //��� �̵� ����
			m_TravelDistance += thisTurn_MoveDistance * deltaTime;

			//�Ÿ� �̵��� ������ �α� ����(����� ������ ����, ��� ����)
			if (m_TravelDistance <= TRAVELDISTANCE_START)
				m_TravelDistance = TRAVELDISTANCE_START;
			else if (m_TravelDistance >= TRAVELDISTANCE_END)
			{ //����̵��� ������ ���� �Ÿ� ĳ���Ϳ��� �ֱ�
				m_X += m_TravelDistance - TRAVELDISTANCE_END; //��� �̵��� ������ ĳ���� �̵����� ��ȯ�Ǵ� ��
				m_TravelDistance = TRAVELDISTANCE_END;
			}
		}
	}

	m_CharcterRect.right = m_CharcterRect.left + IMG_CHARACTER_W; //m_CharcterRect.right�� left�� ���Ҷ����� ���Ž����־�� �Ѵ�.
	return m_TravelDistance;
}

void Character::Update_Jump(float deltaTime)
{
	//ĳ���Ͱ� ���� Ű�� ������ ���߿� ���ִ� ����
	//if (m_JumpState != CHARACTER_JUMP_NONE)
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
				m_CharcterRect.top = m_Y;
				break;
			case CHARACTER_JUMP_DOWN:
				m_Y += CHARACTER_JUMP_GAP * deltaTime;
				if ((m_Y >= CHARACTER_JUMP_MIN_Y))
				{
					m_Y = CHARACTER_JUMP_MIN_Y;
					m_JumpState = CHARACTER_JUMP_NONE;
				}
				m_CharcterRect.top = m_Y;
				break;

			}
	}
}

//void Character::Set_XY()
//{
//}

void Character::Draw(HDC hdc)
{
	BitMapMgr->GetImage(m_IMG_NowMotion)->DrawTransparent(hdc, m_CharcterRect.left, m_CharcterRect.top, IMG_CHARACTER_W, IMG_CHARACTER_H);
}

bool Character::ReductionLife_End()
{
	m_Life--;
	
	if (m_Life == 0)
		return false;

	return true;
}

//-----------------------�¸�----------------------------------

void Character::UpdatePerformance(float deltaTime)
{
	if (m_PerformanceTime >= PERFORMANCE_SPEED)
	{
		m_PerformanceTime = 0;

		if (m_IMG_NowMotion == IMG_CHARACTER_GOAL_1)
			m_IMG_NowMotion = IMG_CHARACTER_GOAL_2;
		else if (m_IMG_NowMotion == IMG_CHARACTER_GOAL_2)
			m_IMG_NowMotion = IMG_CHARACTER_GOAL_1;
	}

	m_PerformanceTime += deltaTime;
}

void Character::Set_XY_GoalMid()
{
	//m_X = WIN_PERFORMANCE_X;
	//m_Y = GOAL_IMG_T - IMG_CHARACTER_H;
	
	m_CharcterRect.left = WIN_PERFORMANCE_X;
	m_CharcterRect.top = WIN_PERFORMANCE_Y;
}

//bool Character::ColliderCheck()
//{
//	return false;
//}
