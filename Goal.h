#pragma once
#include "Object.h"

enum GOAL_IMG
{
	GOAL_IMG_W = 60,
	GOAL_IMG_H = 50,

	//GOAL_IMG_ARRIVE_X = MAIN_W - 150,
};

class Goal : public Object
{
private:
	bool m_EndPositionCheck; //��밡 �� ��ġ�� ������ �������� Ȯ��
	bool m_ActiveCheck; //ȭ��󿡼� �۵� ���� ���� Ȯ�� ����
public:
	Goal();
	~Goal();
	virtual void Draw(HDC hdc) override;
	virtual void Update(float total_MoveDistance, float _Prev_MoveDistance) override;


	//void Set_Goal_X(float _X) { m_Rect[RECTTYPE_BITMAP].left = _X; } //M�� 0�� ��µ� ���ʰ� ���� goal�� x ��ǥ ����
	
	//Goal�� �׷���+�̵�+�浹üũ�� ������ ����
	void Set_ActiveCheck(bool _ActiveCheck) { m_ActiveCheck = _ActiveCheck; }
	bool Get_ActiveCheck() { return m_ActiveCheck; }

	void Set_EndPositionCheck(bool _EndPositionCheck) { m_EndPositionCheck = _EndPositionCheck; }
	bool Get_EndPositionCheck() { return m_EndPositionCheck; }
	virtual bool ColliderCheck() override;
};