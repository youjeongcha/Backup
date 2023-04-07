#include "ObjectManager.h"


void ObjectManager::InitialSet()
{
	//Goal ��
	m_Goal.InitialSet(IMG_OBJECT_GOAL, GOAL_IMG_X, GOAL_IMG_Y); //���� ��� ����
	//FIrJar ���׾Ƹ�
	//m_FirJar[OBSTACLE_ONE].SetObstacle(IMG_OBJECT_POT_1, FIRJAR_X, FIRJAR_Y);
	m_FirJar[OBSTACLE_ONE].InitialSet(IMG_OBJECT_POT_1, FIRJAR_X, FIRJAR_Y);
	m_FirJar[OBSTACLE_TWO].InitialSet(IMG_OBJECT_POT_1, FIRJAR_X + METER_GAP, FIRJAR_Y);
}

void ObjectManager::Draw(HDC hdc)
{
	if (m_Goal.Get_ActiveCheck() == true)
		m_Goal.Draw(hdc);
	
	//m_FirJar->Draw(hdc);
	m_FirJar[OBSTACLE_ONE].Draw(hdc);
	m_FirJar[OBSTACLE_TWO].Draw(hdc);
}

void ObjectManager::Update(float deltaTime, float thisTurn_MoveDistance, float _Prev_MoveDistance)
{
	if (m_Goal.Get_ActiveCheck() == true)
		m_Goal.Update(deltaTime, thisTurn_MoveDistance, _Prev_MoveDistance);
	
	m_FirJar[OBSTACLE_ONE].Update(deltaTime, thisTurn_MoveDistance, _Prev_MoveDistance);
	m_FirJar[OBSTACLE_TWO].Update(deltaTime, thisTurn_MoveDistance, _Prev_MoveDistance);
}

BUMP_CHECK ObjectManager::ColliderCheck(RECT* characterRect)
{
	RECT lprcDst;

	if (m_Goal.Get_ActiveCheck() == true)
	{
		//ObjectMgr���� rect üũ �Ŀ� �ش� object�� ������ ĳ������ ������ ��ġ�� true�� �����Ѵ�.
		if (IntersectRect(&lprcDst, m_Goal.Get_Rect(), characterRect))
			return BUMP_GOAL;
	}

	for (int i = 0; i < OBSTACLE_COUNT; i++)
	{//��ֹ� �ΰ��� �����Ѵ�.(ȭ��󿡼� ��������)

		//���׾Ƹ�
		if (IntersectRect(&lprcDst, m_FirJar[i].Get_Rect(), characterRect))
			return BUMP_OBSTACLE;

		//�Ҹ�B
		if (IntersectRect(&lprcDst, m_FirRing_B[i].Get_Rect(), characterRect))
			return BUMP_OBSTACLE;
	}

	//�Ҹ�S�� �ϳ�?
	//if (IntersectRect(&lprcDst, m_FirRing_S.Get_Rect(), characterRect))
	//	return BUMP_OBSTACLE;

	//�̿ܿ��� ��ġ�� �ʴ� ���
	return BUMP_NONE;
}