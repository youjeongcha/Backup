#pragma once
#include "Goal.h"
#include "FirJar.h"
#include "FirRing_B.h"
#include "FirRing_S.h"

enum OBSTACLE_COUNT
{
	OBSTACLE_ONE,
	OBSTACLE_TWO,
	OBSTACLE_COUNT,
};

class ObjectManager
{
private:
	Goal m_Goal;
	FirJar m_FirJar[OBSTACLE_COUNT];
public:

	//�ʱ� ����
	void InitialSet();

	//ObjectMgr���� rect üũ �Ŀ� �ش� object�� ������ ĳ������ ������ ��ġ�� ture�� �����Ѵ�.
	void Draw(HDC hdc);
	void Update(float thisTurn_MoveDistance, float _Prev_MoveDistance);
	//ObjectMgr���� rect üũ �Ŀ� �ش� object�� ������ ĳ������ ������ ��ġ�� true�� �����Ѵ�.
	bool ColliderCheck_Goal(RECT* characterRect);
	bool ColliderCheck_Obstacle(RECT* characterRect);
	

	bool Get_GoalEndPositionCheck() { return m_Goal.Get_EndPositionCheck(); };
	//Goal�� �׷���+�̵�+�浹üũ�� ������ ����
	void Set_Goal_ActiveCheck(bool _ActiveCheck) { m_Goal.Set_ActiveCheck(_ActiveCheck); }
	void Set_GoalEndPositionCheck(bool _EndPositionCheck) { m_Goal.Set_EndPositionCheck(_EndPositionCheck); }
	//void Set_Goal_X(float _X) { m_Goal.Set_Goal_X(_X); } //M�� 0�� ��µ� ���ʰ� ���� goal�� x ��ǥ ����
};

