#include "ObjectManager.h"
#include "GameManager.h"

void ObjectManager::InitialSet(SET setType)
{
	if (10 == GMMgr->Judgment_First_M_Value() && setType != SET_INIT)
	{
		//Goal ��
		m_Goal.InitialSet(GOAL_IMG_ARRIVE_X, GOAL_IMG_Y); //���� ��� ����

		//FIrJar ���׾Ƹ�
		m_FirJar[OBSTACLE_ONE].InitialSet(FIRJAR_X_10M, FIRJAR_Y);
		m_FirJar[OBSTACLE_TWO].InitialSet(FIRJAR_X_10M - METER_GAP, FIRJAR_Y);

		//FireRing �Ҹ� B
		m_FirRing_B[OBSTACLE_ONE].InitialSet(MAIN_W, FIRRING_Y); //TODO::����
		m_FirRing_B[OBSTACLE_TWO].InitialSet(MAIN_W + METER_GAP, FIRRING_Y);
	}
	else //setType == SET_INIT �� �ʱ�ȭ
	{
		//Goal ��
		m_Goal.InitialSet(GOAL_IMG_X, GOAL_IMG_Y); //���� ��� ����

		//FIrJar ���׾Ƹ�
		m_FirJar[OBSTACLE_ONE].InitialSet(FIRJAR_X, FIRJAR_Y);
		m_FirJar[OBSTACLE_TWO].InitialSet(FIRJAR_X + METER_GAP, FIRJAR_Y);

		//���� ���ϸ� �������� �ٷ� �׾������
		//FireRing �Ҹ� B
		m_FirRing_B[OBSTACLE_ONE].InitialSet(FIRRING_X, FIRRING_Y); //TODO::����
		m_FirRing_B[OBSTACLE_TWO].InitialSet(FIRRING_X + METER_GAP, FIRRING_Y);
	}




	//FireRing �Ҹ� S
	m_FirRing_S.InitialSet(END_SHOW_X + 50, FIRRING_Y);
}

void ObjectManager::Draw(HDC hdc)
{
	if (m_Goal.Get_ActiveCheck() == true)
		m_Goal.Draw(hdc);
	
	//���׾Ƹ� �׸���
	m_FirJar[OBSTACLE_ONE].Draw(hdc);
	m_FirJar[OBSTACLE_TWO].Draw(hdc);

	//FireRing �Ҹ� B
	//if (m_FirRing_B[OBSTACLE_ONE].Get_UsingCheck() == true)
	{
		m_FirRing_B[OBSTACLE_ONE].Draw(hdc);
		//m_FirRing_B[OBSTACLE_ONE].DrawDEbugggggggggggggg(hdc);
	}
	//if (m_FirRing_B[OBSTACLE_TWO].Get_UsingCheck() == true)
	{
		m_FirRing_B[OBSTACLE_TWO].Draw(hdc);
		//m_FirRing_B[OBSTACLE_TWO].DrawDEbugggggggggggggg(hdc);
	}

	//�Ҹ� ȭ��� ��Ÿ�� ������ ���
	//if (m_FirRing_S.Get_UsingCheck() == true)
	{
		//FireRing �Ҹ� S
		m_FirRing_S.Draw(hdc);
		//m_FirRing_S.DrawDEbugggggggggggggg(hdc);
	}
}

void ObjectManager::Draw_OnCharacter(HDC hdc)
{
	//FireRing �Ҹ� B
	//if (m_FirRing_B[OBSTACLE_ONE].Get_UsingCheck() == true)
	{
		m_FirRing_B[OBSTACLE_ONE].Draw_OnCharacter(hdc);
		//m_FirRing_B[OBSTACLE_ONE].DrawDEbugggggggggggggg(hdc);
	}
	//if (m_FirRing_B[OBSTACLE_TWO].Get_UsingCheck() == true)
	{
		m_FirRing_B[OBSTACLE_TWO].Draw_OnCharacter(hdc);
		//m_FirRing_B[OBSTACLE_TWO].DrawDEbugggggggggggggg(hdc);
	}

	//�Ҹ� ȭ��� ��Ÿ�� ������ ���
	//if (m_FirRing_S.Get_UsingCheck() == true)
	{
		//FireRing �Ҹ� S
		m_FirRing_S.Draw_OnCharacter(hdc);
	}
}

void ObjectManager::Update(float deltaTime, float thisTurn_MoveDistance, float _Prev_MoveDistance)
{
	//Goal�� Ư�� ��ǥ�� ���� ���+M �������� �����.(�ڷΰ��� ���� �־����� �ٽ� ��� �̵����� ��ȯ�Ѵ�.)
	//if (GMMgr->Get_GoalEndPositionCheck() == false)
	//{
	//}

	if (m_Goal.Get_ActiveCheck() == true)
		m_Goal.Update(deltaTime, thisTurn_MoveDistance, _Prev_MoveDistance);
	
	//FIrJar ���׾Ƹ�
	m_FirJar[OBSTACLE_ONE].Update(deltaTime, thisTurn_MoveDistance, _Prev_MoveDistance);
	m_FirJar[OBSTACLE_TWO].Update(deltaTime, thisTurn_MoveDistance, _Prev_MoveDistance);

	//FireRing �Ҹ� B
	m_FirRing_B[OBSTACLE_ONE].Update(deltaTime, thisTurn_MoveDistance, _Prev_MoveDistance);
	m_FirRing_B[OBSTACLE_TWO].Update(deltaTime, thisTurn_MoveDistance, _Prev_MoveDistance);

	//FireRing �Ҹ� S
	m_FirRing_S.Update(deltaTime, thisTurn_MoveDistance, _Prev_MoveDistance);
}

int ObjectManager::ColliderCheck(RECT* characterRect)
{
	//RECT lprcDst;
	int score = 0;

	//--------------- �� �ε����� ���� 0 ---------------
	if (m_Goal.Get_ActiveCheck() == true)
	{

		//ObjectMgr���� rect üũ �Ŀ� �ش� object�� ������ ĳ������ ������ ��ġ�� true�� �����Ѵ�.
		if (m_Goal.ColliderCheck(characterRect, RECT_BUMP))
			return BUMP_GOAL;
		//if (IntersectRect(&lprcDst, m_Goal.Get_Rect(RECT_BUMP), characterRect))
		//	return BUMP_GOAL;
	}

	//scroe ���� �����
	for (int i = 0; i < OBSTACLE_COUNT; i++)
	{//��ֹ� �ΰ��� �����Ѵ�.(ȭ��󿡼� ��������)

		//--------------- ��ֹ��� �ε����� ���� -1 ---------------
		 
		//���׾Ƹ� Bump
		//if (IntersectRect(&lprcDst, m_FirJar[i].Get_Rect(RECT_BUMP), characterRect))
		if (m_FirJar[i].ColliderCheck(characterRect, RECT_BUMP))
    		return BUMP_OBSTACLE;

		//--------------- ���ھ� RECT �ε����� 1~�̻� ��� ---------------
		
		//���׾Ƹ� Score
		//if (IntersectRect(&lprcDst, m_FirJar[i].Get_Rect(RECT_SCORE), characterRect))
		if (m_FirJar[i].ColliderCheck(characterRect, RECT_SCORE))
			score += m_FirJar[i].Get_AllotScore(); //TODO::�ش� �������� �Լ��� ���� ���

		//

		//�Ҹ� ȭ��� ��Ÿ�� ������ ���
		//if (m_FirRing_B[i].Get_UsingCheck() == true)
		{
			//�Ҹ�B Bump
			//if (IntersectRect(&lprcDst, m_FirRing_B[i].Get_Rect(RECT_BUMP), characterRect))
			if (m_FirRing_B[i].ColliderCheck(characterRect, RECT_BUMP))
  				return BUMP_OBSTACLE;

			//�Ҹ�B Score
			//if (IntersectRect(&lprcDst, m_FirRing_B[i].Get_Rect(RECT_SCORE), characterRect))
			if (m_FirRing_B[i].ColliderCheck(characterRect, RECT_SCORE))
				score += m_FirRing_B[i].Get_AllotScore(); //TODO::�ش� �������� �Լ��� ���� ���
		}
	}

	//�Ҹ� ȭ��� ��Ÿ�� ������ ���
	//if (m_FirRing_S.Get_UsingCheck() == true)
	{
		//�Ҹ�S�� �ϳ� //70���ö� ����
		//if (IntersectRect(&lprcDst, m_FirRing_S.Get_Rect(RECT_BUMP), characterRect))
		if (m_FirRing_S.ColliderCheck(characterRect, RECT_BUMP))
			return BUMP_OBSTACLE;

		//if (IntersectRect(&lprcDst, m_FirRing_S.Get_Rect(RECT_SCORE), characterRect))
		if (m_FirRing_S.ColliderCheck(characterRect, RECT_SCORE))
		{
			score += m_FirRing_S.Get_AllotScore(); //TODO::�ش� �������� �Լ��� ���� ���
			m_FirRing_S.Set_bCashDraw(false); //���ָӴ� ������ ������� �ϹǷ�
		}
	}


	if (score > 0) //������ 1 �̻��̶�� �� ���� �� ��
		return score;
	else //�̿ܿ��� ��ġ�� �ʴ� ���
		return BUMP_NONE;
}