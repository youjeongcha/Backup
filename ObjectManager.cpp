#include "ObjectManager.h"


void ObjectManager::Draw(HDC hdc)
{
	m_Goal.Draw(hdc);
}

void ObjectManager::Update(float deltaTime, float thisTurn_MoveDistance)
{
	m_Goal.Update(deltaTime, thisTurn_MoveDistance);
}

bool ObjectManager::BumpCheck()
{
	//TODO::ObjectMgr에서 rect 체크 후에 해당 object의 범위와 캐릭터의 범위가 겹치면 true를 리턴한다.

	return false;
}
