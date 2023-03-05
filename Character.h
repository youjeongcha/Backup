#pragma once
#include"AnimationManager.h"
//����Լ��� ��� ��ü�� ����Լ����� �����ؾ� �Ѵ�.
//Ŭ������ ����Լ��� �ش� ����Լ��� ������ ���������� �˷���� > ����� ����

class Character
{//Ŭ���� ������
private:
	int m_iHP;
	int m_iDamage;
	AnimationManager m_animationManager;
public:
	Character();
	~Character();
	void HitBy(int Damage);
	void Buff();
	void Attack();

	void AttackAnimation();
	void BuffAnimation();
	void HitbyAnimation();
};

