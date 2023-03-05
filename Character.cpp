#include "Character.h"



void Character::HitBy(int Damage)
{
	cout << "데미지를 입었습니다." << endl;
	cout << "HP : " << m_iHP << " -> ";
	m_iHP -= Damage;
	if (m_iHP < 0)
		m_iHP = 0;

	cout << m_iHP << endl;
	if (m_iHP == 0)
		cout << "캐릭터가 사망하였습니다.";
}
void Character::Buff()
{
	cout << "능력치가 소폭 증가하였습니다." << endl;
	m_iDamage += 100;
}
void Character::Attack()
{
	cout << "캐릭터가 전방의 적들에게 데미지를 " << m_iDamage << " 만큼 입혔습니다." << endl;
}


void Character::AttackAnimation()
{
	m_animationManager.Play(&Character::Attack, this);//함수포인터. 누구거인지 가리키기 위해서 this 사용
}
void Character::BuffAnimation()
{
	m_animationManager.Play(&Character::Buff, this);
}
void Character::HitbyAnimation()
{//네임스페이스 + 레퍼런스
	m_animationManager.Play(&Character::HitBy, this);
}

Character::Character()
{//생성자
	m_iDamage = 300;
	m_iHP = 1000;
	cout << "Animation 초기화중";
}
Character::~Character()
{

}