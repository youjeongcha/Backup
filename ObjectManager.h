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
	FirJar m_FirJar[OBSTACLE_COUNT]; //���׾Ƹ�
	FirRing_B m_FirRing_B[OBSTACLE_COUNT]; //�Ҹ�Big
	FirRing_S m_FirRing_S; //�Ҹ�Small
public:

	//�ʱ� ����
	void InitialSet(SET setType);

	//ObjectMgr���� rect üũ �Ŀ� �ش� object�� ������ ĳ������ ������ ��ġ�� ture�� �����Ѵ�.
	//���� �� + �� �׾Ƹ� + �� ���� ��ֹ�
	void Draw(HDC hdc);
	void Draw_OnCharacter(HDC hdc);
	void Update(float deltaTime, float thisTurn_MoveDistance, float _Prev_MoveDistance);
	//���� ��ģ object�� �Ӽ��� ���� ó���� �ٸ��� �Ѵ�.(ex.��-���� Ŭ����, ��ֹ�-�������+���ӿ���)
	int ColliderCheck(RECT* characterRect);
	

	void DrawCashScoreText(HDC hdc) { m_FirRing_S.DrawCashScoreText(hdc); }

	bool Get_GoalEndPositionCheck() { return m_Goal.Get_EndPositionCheck(); }
	//Goal�� �׷���+�̵�+�浹üũ�� ������ ����
	void Set_Goal_ActiveCheck(bool _ActiveCheck) { m_Goal.Set_ActiveCheck(_ActiveCheck); }
	void Set_GoalEndPositionCheck(bool _EndPositionCheck) { m_Goal.Set_EndPositionCheck(_EndPositionCheck); }
	//���ָӴ� �ش� ring�� ���� xy �������� text ��� ��ǥ ����
	void Set_Text_XY() { m_FirRing_S.Set_Text_XY(); }
	//void Set_Goal_X(float _X) { m_Goal.Set_Goal_X(_X); } //M�� 0�� ��µ� ���ʰ� ���� goal�� x ��ǥ ����
};

