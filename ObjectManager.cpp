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

void ObjectManager::Update(float thisTurn_MoveDistance, float _Prev_MoveDistance)
{
	if (m_Goal.Get_ActiveCheck() == true)
		m_Goal.Update(thisTurn_MoveDistance, _Prev_MoveDistance);
	
	m_FirJar[OBSTACLE_ONE].Update(thisTurn_MoveDistance, _Prev_MoveDistance);
	m_FirJar[OBSTACLE_TWO].Update(thisTurn_MoveDistance, _Prev_MoveDistance);
}

bool ObjectManager::ColliderCheck_Goal(RECT* characterRect)
{
	LPRECT lprcDst = NULL;

	if (m_Goal.Get_ActiveCheck() == true)
	{
		//ObjectMgr���� rect üũ �Ŀ� �ش� object�� ������ ĳ������ ������ ��ġ�� true�� �����Ѵ�.
		//IntersectRect(lprcDst, &m_Goal.Get_Rect(), &characterRect);

		if (IntersectRect(lprcDst, m_Goal.Get_Rect(), characterRect) == true)
			return true;

		if ((m_Goal.Get_Rect()->left <= characterRect->right) && // x ��ġ�� ��� : goal�� left�� character�� right ���� �۰ų� ������
			(m_Goal.Get_Rect()->top <= characterRect->bottom)) // y ��ġ�� ��� : goal�� top�� character�� bottom ���� �۰ų� ������
			return true;
	}

	//�̿ܿ��� ��ġ�� �ʴ� ���
	return false;
}

bool ObjectManager::ColliderCheck_Obstacle(RECT* characterRect)
{//TODO::Obstacle 

	if (m_Goal.Get_ActiveCheck() == true)
	{
	}
	return false;
}
