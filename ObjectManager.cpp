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
	//TODO::ObjectMgr���� rect üũ �Ŀ� �ش� object�� ������ ĳ������ ������ ��ġ�� true�� �����Ѵ�.

	return false;
}
