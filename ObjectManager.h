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

	bool Get_GoalEndPositionCheck() { return m_Goal.Get_EndPositionCheck(); };
	void Set_ActiveCheck(bool _ActiveCheck) { m_Goal.Set_ActiveCheck(_ActiveCheck); }
	//void Set_Goal_X(float _X) { m_Goal.Set_Goal_X(_X); } //M�� 0�� ��µ� ���ʰ� ���� goal�� x ��ǥ ����
};

