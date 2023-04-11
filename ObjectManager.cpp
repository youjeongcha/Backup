#include "ObjectManager.h"
#include "GameManager.h"

void ObjectManager::InitialSet()
{
	//Goal ��
	m_Goal.InitialSet(GOAL_IMG_X, GOAL_IMG_Y); //���� ��� ����

	//FIrJar ���׾Ƹ�
	m_FirJar[OBSTACLE_ONE].InitialSet(FIRJAR_X, FIRJAR_Y);
	m_FirJar[OBSTACLE_TWO].InitialSet(FIRJAR_X + METER_GAP, FIRJAR_Y);

	//FireRing �Ҹ� B
	m_FirRing_B[OBSTACLE_ONE].InitialSet(FIRRING_X, FIRRING_Y); //TODO::����
	m_FirRing_B[OBSTACLE_TWO].InitialSet(FIRRING_X + METER_GAP, FIRRING_Y);

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
	m_FirRing_B[OBSTACLE_ONE].Draw(hdc);
	m_FirRing_B[OBSTACLE_TWO].Draw(hdc);

	//�Ҹ� ȭ��� ��Ÿ�� ������ ���
	if (m_FirRing_S.Get_UsingCheck() == true)
	{
		//FireRing �Ҹ� S
		m_FirRing_S.Draw(hdc);
	}
}

void ObjectManager::Draw_OnCharacter(HDC hdc)
{
	//FireRing �Ҹ� B
	m_FirRing_B[OBSTACLE_ONE].Draw_OnCharacter(hdc);
	m_FirRing_B[OBSTACLE_TWO].Draw_OnCharacter(hdc);

	//�Ҹ� ȭ��� ��Ÿ�� ������ ���
	if (m_FirRing_S.Get_UsingCheck() == true)
	{
		//FireRing �Ҹ� S
		m_FirRing_S.Draw_OnCharacter(hdc);
	}
}

void ObjectManager::Update(float deltaTime, float thisTurn_MoveDistance, float _Prev_MoveDistance)
{
	if (m_Goal.Get_ActiveCheck() == true)
		m_Goal.Update(deltaTime, thisTurn_MoveDistance, _Prev_MoveDistance);
	
	//FIrJar ���׾Ƹ�
	m_FirJar[OBSTACLE_ONE].Update(deltaTime, thisTurn_MoveDistance, _Prev_MoveDistance);
	m_FirJar[OBSTACLE_TWO].Update(deltaTime, thisTurn_MoveDistance, _Prev_MoveDistance);


	//FireRing �Ҹ� B
	m_FirRing_B[OBSTACLE_ONE].Update(deltaTime, thisTurn_MoveDistance, _Prev_MoveDistance);
	m_FirRing_B[OBSTACLE_TWO].Update(deltaTime, thisTurn_MoveDistance, _Prev_MoveDistance);


	//�Ҹ� ȭ��� ��Ÿ�� ������ ���
	if (m_FirRing_S.Get_UsingCheck() == true)
	{
		//FireRing �Ҹ� S
		m_FirRing_S.Update(deltaTime, thisTurn_MoveDistance, _Prev_MoveDistance);
	}
}

BUMP_CHECK ObjectManager::ColliderCheck(RECT* characterRect)
{
	RECT lprcDst;
	int score;

	if (m_Goal.Get_ActiveCheck() == true)
	{
		//ObjectMgr���� rect üũ �Ŀ� �ش� object�� ������ ĳ������ ������ ��ġ�� true�� �����Ѵ�.
		if (IntersectRect(&lprcDst, m_Goal.Get_Rect(RECT_BUMP), characterRect))
			return BUMP_GOAL;
	}

	//scroe ���� �����
	for (int i = 0; i < OBSTACLE_COUNT; i++)
	{//��ֹ� �ΰ��� �����Ѵ�.(ȭ��󿡼� ��������)

		//���׾Ƹ� Bump
		if (IntersectRect(&lprcDst, m_FirJar[i].Get_Rect(RECT_BUMP), characterRect))
    		return BUMP_OBSTACLE;

		//�Ҹ�B Bump
		if (IntersectRect(&lprcDst, m_FirRing_B[i].Get_Rect(RECT_BUMP), characterRect))
			return BUMP_OBSTACLE;


		//���׾Ƹ� Score
		if (IntersectRect(&lprcDst, m_FirJar[i].Get_Rect(RECT_SCORE), characterRect))
			return BUMP_SCORE;

		//�Ҹ�B Score
		if (IntersectRect(&lprcDst, m_FirRing_B[i].Get_Rect(RECT_SCORE), characterRect))
			return BUMP_SCORE;
	}

	//�Ҹ� ȭ��� ��Ÿ�� ������ ���
	if (m_FirRing_S.Get_UsingCheck() == true)
	{
		//�Ҹ�S�� �ϳ� //70���ö� ����
		if (IntersectRect(&lprcDst, m_FirRing_S.Get_Rect(RECT_BUMP), characterRect))
			return BUMP_OBSTACLE;

		if (IntersectRect(&lprcDst, m_FirRing_S.Get_Rect(RECT_SCORE), characterRect))
			return BUMP_CASH;
	}

	//�̿ܿ��� ��ġ�� �ʴ� ���
	return BUMP_NONE;
}