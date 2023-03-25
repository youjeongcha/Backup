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
	m_TravelDistance = TRAVELDISTANCE_START;
}

Character::~Character()
{
}

float Character::Update(float deltaTime)
{//���� ::Update_XY���� ȣ���� ���� Jump�� ������ϳ�. ������ ���Ǿ��̸� ������ �Լ� ���ٿ� Jump�� �����ϹǷ� ��� ����? 
	float XY_Tmp;
	UpdateIMG(deltaTime); //ĳ���� IMG
	XY_Tmp = Update_XY(deltaTime);
	Update_Jump(deltaTime);
	return XY_Tmp;

	//UpdateIMG(deltaTime); //ĳ���� IMG
	//Update_Jump(deltaTime);
	//return Update_XY(deltaTime);
}

void Character::UpdateIMG(float deltaTime)
{
	IMG imgLimit = IMG_CHARACTER_BUMP;

	if (m_MoveTime >= MOVE_SPEED)
	{
		//m_MoveTime = 0; //�ʱ�ȭ�� Update_XY���� �̷������.
		if ((m_JumpState != CHARACTER_JUMP_NONE) || (GetAsyncKeyState(VK_SPACE) & 0x8000))	//����
			m_IMG_NowMotion = IMG_CHARACTER_FRONT_3;
		else if (GetAsyncKeyState(VK_RIGHT) & 0x8000) //������ �̵�
		{
			m_IMG_NowMotion = (IMG)(m_IMG_NowMotion + 1);

			imgLimit = IMG_CHARACTER_GOAL_1; //�޸��� IMG �ȿ����� �۵��ϱ� ���� IMG ���� ���Ѱɱ�
		}
		else if (GetAsyncKeyState(VK_LEFT) & 0x8000) //���� �̵�
		{
			m_IMG_NowMotion = (IMG)(m_IMG_NowMotion + 1);
			
			imgLimit = IMG_CHARACTER_FRONT_3; //�ڷ� ���� IMG �ȿ����� �۵��ϱ� ���� IMG ���� ���Ѱɱ�
		}
		else //���� ����
			m_IMG_NowMotion = IMG_CHARACTER_FRONT_1;

		//�ش� ������ ��� ���� IMG �ȿ����� �۵��ϱ� ���� IMG ���� ���Ѱɱ�
		if (m_IMG_NowMotion >= imgLimit) //���� + ���̵��� ��� imgLmit�� �Ѿ >=�� �ʿ�
 			m_IMG_NowMotion = IMG_CHARACTER_FRONT_1;
	}

	m_MoveTime += deltaTime;
}

float Character::Update_XY(float deltaTime)
{
	float thisTurn_MoveDistance = 0;
	//TODO::������ ��ǥ�� �����ϱ� �������� ����� �����δ�.(��ǥ�� �־����� �ٽ� ��� ������)
	//GM���� goal ��ġ Ȯ�� bool�� �޾ƿͼ� ���� �ɱ�

	if (m_MoveTime >= MOVE_SPEED)
	{
		m_MoveTime = 0;

		//������ �¿� �̵��� ������ ������ �ؾ� �¿��̵� �߿� ������ ���� �� ��� ���� ������ �߻�X
		if ((GetAsyncKeyState(VK_SPACE) & 0x8000) && (m_JumpState == CHARACTER_JUMP_NONE)) //ĳ���Ͱ� �� �����϶��� ���� ����
			m_JumpState = CHARACTER_JUMP_UP;
		
		if (GetAsyncKeyState(VK_LEFT) & 0x8000)
			thisTurn_MoveDistance -= TRAVELDISTANCE_MOVE_PER_SEC;
		else if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
			thisTurn_MoveDistance += TRAVELDISTANCE_MOVE_PER_SEC;

		m_TravelDistance += thisTurn_MoveDistance;

		//������ ��� ���� (ĳ���� �̵� ���� ����)
		if (m_TravelDistance < TRAVELDISTANCE_START)
			m_TravelDistance = TRAVELDISTANCE_START;
		else if (m_TravelDistance > TRAVELDISTANCE_END)
			m_TravelDistance = TRAVELDISTANCE_END;
	}

	m_MoveTime += deltaTime;


	//else if (GetAsyncKeyState(VK_LEFT) & 0x8000)
	//	m_CharcterRect.left -= 20;
	//else if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
	//	m_CharcterRect.left += 20;

	
	//�Ÿ� �̵��� ������ �α� ����(����� ������ ����)
	if ((m_TravelDistance <= TRAVELDISTANCE_START) || (m_TravelDistance >= TRAVELDISTANCE_END)) //���� ���ʿ� ������ ���
		return 0;
	else
		return thisTurn_MoveDistance;
}

void Character::Update_Jump(float deltaTime)
{
	//ĳ���Ͱ� ���� Ű�� ������ ���߿� ���ִ� ����
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