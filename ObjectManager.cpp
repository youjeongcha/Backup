#include "ObjectManager.h"


void ObjectManager::InitialSet()
{
	//Goal 골
	m_Goal.InitialSet(IMG_OBJECT_GOAL, GOAL_IMG_X, GOAL_IMG_Y); //인자 사용 안함
	//FIrJar 불항아리
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
		//ObjectMgr에서 rect 체크 후에 해당 object의 범위와 캐릭터의 범위가 겹치면 true를 리턴한다.
		//IntersectRect(lprcDst, &m_Goal.Get_Rect(), &characterRect);

		if (IntersectRect(lprcDst, m_Goal.Get_Rect(), characterRect) == true)
			return true;

		if ((m_Goal.Get_Rect()->left <= characterRect->right) && // x 겹치는 경우 : goal의 left가 character의 right 보다 작거나 같으면
			(m_Goal.Get_Rect()->top <= characterRect->bottom)) // y 겹치는 경우 : goal의 top이 character의 bottom 보다 작거나 같으면
			return true;
	}

	//이외에는 겹치지 않는 경우
	return false;
}

bool ObjectManager::ColliderCheck_Obstacle(RECT* characterRect)
{//TODO::Obstacle 

	if (m_Goal.Get_ActiveCheck() == true)
	{
	}
	return false;
}
