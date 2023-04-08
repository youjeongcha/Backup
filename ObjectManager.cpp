#include "ObjectManager.h"
#include "GameManager.h"

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
		//ObjectMgr에서 rect 체크 후에 해당 object의 범위와 캐릭터의 범위가 겹치면 true를 리턴한다.
		if (IntersectRect(&lprcDst, m_Goal.Get_Rect(RECT_BUMP), characterRect))
			return BUMP_GOAL;
	}

	for (int i = 0; i < OBSTACLE_COUNT; i++)
	{//장애물 두개씩 존재한다.(화면상에서 돌려쓰기)

		//불항아리 Bump
		if (IntersectRect(&lprcDst, m_FirJar[i].Get_Rect(RECT_BUMP), characterRect))
    		return BUMP_OBSTACLE;

		//불링B Bump
		if (IntersectRect(&lprcDst, m_FirRing_B[i].Get_Rect(RECT_BUMP), characterRect))
			return BUMP_OBSTACLE;


		//불항아리 Score
		if (IntersectRect(&lprcDst, m_FirJar[i].Get_Rect(RECT_SCORE), characterRect))
		{
			//TODO:: 점수 올려주기
			//GMMgr->ScoreUp();
			return BUMP_SCORE;
		}

		//불링B Score
		if (IntersectRect(&lprcDst, m_FirRing_B[i].Get_Rect(RECT_SCORE), characterRect))
		{
			//TODO:: 점수 올려주기

			//GMMgr->ScoreUp();
			return BUMP_SCORE;
		}
	}

	//불링S는 하나?
	//if (IntersectRect(&lprcDst, m_FirRing_S.Get_Rect(), characterRect))
	//	return BUMP_OBSTACLE;

	//이외에는 겹치지 않는 경우
	return BUMP_NONE;
}