#include "ObjectManager.h"
#include "GameManager.h"

void ObjectManager::InitialSet()
{
	//Goal 골
	m_Goal.InitialSet(GOAL_IMG_X, GOAL_IMG_Y); //인자 사용 안함

	//FIrJar 불항아리
	m_FirJar[OBSTACLE_ONE].InitialSet(FIRJAR_X, FIRJAR_Y);
	m_FirJar[OBSTACLE_TWO].InitialSet(FIRJAR_X + METER_GAP, FIRJAR_Y);

	//FireRing 불링 B
	m_FirRing_B[OBSTACLE_ONE].InitialSet(FIRRING_X, FIRRING_Y); //TODO::수정
	m_FirRing_B[OBSTACLE_TWO].InitialSet(FIRRING_X + METER_GAP, FIRRING_Y);

	//FireRing 불링 S
	m_FirRing_S.InitialSet(END_SHOW_X + 50, FIRRING_Y);
}

void ObjectManager::Draw(HDC hdc)
{
	if (m_Goal.Get_ActiveCheck() == true)
		m_Goal.Draw(hdc);
	
	//불항아리 그리기
	m_FirJar[OBSTACLE_ONE].Draw(hdc);
	m_FirJar[OBSTACLE_TWO].Draw(hdc);

	//FireRing 불링 B
	m_FirRing_B[OBSTACLE_ONE].Draw(hdc);
	m_FirRing_B[OBSTACLE_TWO].Draw(hdc);

	//불링 화면상에 나타날 시점에 사용
	if (m_FirRing_S.Get_UsingCheck() == true)
	{
		//FireRing 불링 S
		m_FirRing_S.Draw(hdc);
	}
}

void ObjectManager::Draw_OnCharacter(HDC hdc)
{
	//FireRing 불링 B
	m_FirRing_B[OBSTACLE_ONE].Draw_OnCharacter(hdc);
	m_FirRing_B[OBSTACLE_TWO].Draw_OnCharacter(hdc);

	//불링 화면상에 나타날 시점에 사용
	if (m_FirRing_S.Get_UsingCheck() == true)
	{
		//FireRing 불링 S
		m_FirRing_S.Draw_OnCharacter(hdc);
	}
}

void ObjectManager::Update(float deltaTime, float thisTurn_MoveDistance, float _Prev_MoveDistance)
{
	if (m_Goal.Get_ActiveCheck() == true)
		m_Goal.Update(deltaTime, thisTurn_MoveDistance, _Prev_MoveDistance);
	
	//FIrJar 불항아리
	m_FirJar[OBSTACLE_ONE].Update(deltaTime, thisTurn_MoveDistance, _Prev_MoveDistance);
	m_FirJar[OBSTACLE_TWO].Update(deltaTime, thisTurn_MoveDistance, _Prev_MoveDistance);


	//FireRing 불링 B
	m_FirRing_B[OBSTACLE_ONE].Update(deltaTime, thisTurn_MoveDistance, _Prev_MoveDistance);
	m_FirRing_B[OBSTACLE_TWO].Update(deltaTime, thisTurn_MoveDistance, _Prev_MoveDistance);


	//불링 화면상에 나타날 시점에 사용
	if (m_FirRing_S.Get_UsingCheck() == true)
	{
		//FireRing 불링 S
		m_FirRing_S.Update(deltaTime, thisTurn_MoveDistance, _Prev_MoveDistance);
	}
}

BUMP_CHECK ObjectManager::ColliderCheck(RECT* characterRect)
{
	RECT lprcDst;
	int score;

	if (m_Goal.Get_ActiveCheck() == true)
	{
		//ObjectMgr에서 rect 체크 후에 해당 object의 범위와 캐릭터의 범위가 겹치면 true를 리턴한다.
		if (IntersectRect(&lprcDst, m_Goal.Get_Rect(RECT_BUMP), characterRect))
			return BUMP_GOAL;
	}

	//scroe 변수 만들긴
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
			return BUMP_SCORE;

		//불링B Score
		if (IntersectRect(&lprcDst, m_FirRing_B[i].Get_Rect(RECT_SCORE), characterRect))
			return BUMP_SCORE;
	}

	//불링 화면상에 나타날 시점에 사용
	if (m_FirRing_S.Get_UsingCheck() == true)
	{
		//불링S는 하나 //70나올때 생성
		if (IntersectRect(&lprcDst, m_FirRing_S.Get_Rect(RECT_BUMP), characterRect))
			return BUMP_OBSTACLE;

		if (IntersectRect(&lprcDst, m_FirRing_S.Get_Rect(RECT_SCORE), characterRect))
			return BUMP_CASH;
	}

	//이외에는 겹치지 않는 경우
	return BUMP_NONE;
}