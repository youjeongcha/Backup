#pragma once
#include "Object.h"



class Goal : public Object
{
private:
	bool m_EndPositionCheck; //��밡 �� ��ġ�� ������ �������� Ȯ��
	bool m_ActiveCheck; //ȭ��󿡼� �۵� ���� ���� Ȯ�� ����
public:
	Goal();
	~Goal();

	//�ʱ� ���� Goal������ ���ڸ� ������� �ʴ´�.
	virtual void InitialSet(IMG _IMG_X, int _X, int _Y) override;
	virtual void Draw(HDC hdc) override;
	virtual void Update(float total_MoveDistance, float _Prev_MoveDistance) override;

	
	//Goal�� �׷���+�̵�+�浹üũ�� ������ ����
	void Set_ActiveCheck(bool _ActiveCheck) { m_ActiveCheck = _ActiveCheck; }
	bool Get_ActiveCheck() { return m_ActiveCheck; }

	void Set_EndPositionCheck(bool _EndPositionCheck) { m_EndPositionCheck = _EndPositionCheck; }
	bool Get_EndPositionCheck() { return m_EndPositionCheck; }
};