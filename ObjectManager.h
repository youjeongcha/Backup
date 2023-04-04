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
	void Update(float thisTurn_MoveDistance, float _Prev_MoveDistance);
	bool ColliderCheck();
	

	bool Get_GoalEndPositionCheck() { return m_Goal.Get_EndPositionCheck(); };
	//Goal�� �׷���+�̵�+�浹üũ�� ������ ����
	void Set_Goal_ActiveCheck(bool _ActiveCheck) { m_Goal.Set_ActiveCheck(_ActiveCheck); }
	void Set_GoalEndPositionCheck(bool _EndPositionCheck) { m_Goal.Set_EndPositionCheck(_EndPositionCheck); }
	//void Set_Goal_X(float _X) { m_Goal.Set_Goal_X(_X); } //M�� 0�� ��µ� ���ʰ� ���� goal�� x ��ǥ ����
};

