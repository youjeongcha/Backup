#pragma once
#include "Goal.h"
#include "FireObstacle.h"

class ObjectManager
{
private:
	Goal m_Goal;
public:
	//ObjectMgr���� rect üũ �Ŀ� �ش� object�� ������ ĳ������ ������ ��ġ�� ture�� �����Ѵ�.
	void Draw(HDC hdc);
	void Update(float deltaTime, float thisTurn_MoveDistance);
	bool BumpCheck();

	bool Get_EndCheck() { return m_Goal.Get_EndCheck(); };
};

