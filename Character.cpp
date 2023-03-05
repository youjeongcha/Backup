#include "Character.h"
//std::bind ����


void Character::HitBy(int Damage)
{
	cout << "�������� �Ծ����ϴ�." << endl;
	cout << "HP : " << m_iHP << " -> ";
	m_iHP -= Damage;
	if (m_iHP < 0)
		m_iHP = 0;

	cout << m_iHP << endl;
	if (m_iHP == 0)
		cout << "ĳ���Ͱ� ����Ͽ����ϴ�.";
}
void Character::Buff()
{
	cout << "�ɷ�ġ�� ���� �����Ͽ����ϴ�." << endl;
	m_iDamage += 100;
}
void Character::Attack()
{
	cout << "ĳ���Ͱ� ������ ���鿡�� �������� " << m_iDamage << " ��ŭ �������ϴ�." << endl;
}

//Ŭ�������� ����Լ��� ������ ���ε带 ��κ� ����
void Character::AttackAnimation()
{//std::bind > class�� ����� �ʿ�X
	/*m_animationManager.Play(&Character::Attack, this);//�Լ�������. ���������� ����Ű�� ���ؼ� this ���*/
	m_animationManager.NonParameterPlay(std::bind(&Character::Attack,this));
	//�Լ�������. ���������� ����Ű�� ���ؼ� this ���
}
void Character::BuffAnimation()
{
	m_animationManager.NonParameterPlay(std::bind(&Character::Buff, this));
}
void Character::HitbyAnimation()
{//���ӽ����̽� + ���۷���
	m_animationManager.IntParameterPlay(std::bind(&Character::HitBy, this,placeholders::_1));
}

Character::Character()
{//������
	m_iDamage = 300;
	m_iHP = 1000;
	cout << "Animation �ʱ�ȭ��";
}
Character::~Character()
{

}