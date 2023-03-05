#pragma once
#include"AnimationManager.h"
//멤버함수가 어느 객체의 멤버함수인지 구분해야 한다.
//클래스의 멤버함수는 해당 멤버함수가 누구의 것인지까지 알려줘야 > 사용이 가능

class Character
{//클래는 설개도
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

