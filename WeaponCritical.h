#pragma once
//#include "Mecro.h"
#include "Weapon.h"
#include <map>

//#define WEAPONKIND 4 //���� ����
#define FOUR 4 //�޾ƿ��� ��. �ְ� 15 ũ��Ƽ��!! 1.5 �̷������� 4�� ���

struct WeaponCri
{
	int criticalRate;
	string words;
	int risingPercentage;
};

class WeaponCritical
{
private:
	//string m_WeaponCritical[][FOUR];//�ڱ���ü�� ���� ���
	//���� ����, ���⺰ ����
	map<string, WeaponCri> m_WeaponCritical;
public:
	void CreateWeaponCritical();
	//string(*GetWeaponCritical())[FOUR] { return m_WeaponCritical; }
	map<string, WeaponCri>
		GetWeaponCritical() { return m_WeaponCritical; }
};