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

void Character::Update_XY(float deltaTime)
{
	//TODO::������ ��ǥ�� �����ϱ� �������� ����� �����δ�.(��ǥ�� �־����� �ٽ� ��� ������)
	//GM���� goal ��ġ Ȯ�� bool�� �޾ƿͼ� ���� �ɱ�

	if (GetAsyncKeyState(VK_SPACE) & 0x8000 && (m_JumpState == CHARACTER_JUMP_NONE)) //ĳ���Ͱ� �� �����϶��� ���� ����
		m_JumpState = CHARACTER_JUMP_UP;
	/*else if (GetAsyncKeyState(VK_LEFT) & 0x8000)
		m_CharcterRect.left -= 20;
	else if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
		m_CharcterRect.left += 20;*/


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