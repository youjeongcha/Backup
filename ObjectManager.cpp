#include "ObjectManager.h"


void ObjectManager::Draw(HDC hdc)
{
	if (m_Goal.Get_ActiveCheck() == true)
		m_Goal.Draw(hdc);
}

void ObjectManager::Update(float thisTurn_MoveDistance, float _Prev_MoveDistance)
{
	if (m_Goal.Get_ActiveCheck() == true)
		m_Goal.Update(thisTurn_MoveDistance, _Prev_MoveDistance);
}

bool ObjectManager::ColliderCheck()
{
	//TODO::ObjectMgr���� rect üũ �Ŀ� �ش� object�� ������ ĳ������ ������ ��ġ�� true�� �����Ѵ�.

	return false;
}
