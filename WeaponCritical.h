#pragma once
//#include "Mecro.h"
#include "Weapon.h"
#include <map>

//#define WEAPONKIND 4 //무기 종류
#define FOUR 4 //받아오는 게. 쌍검 15 크리티컬!! 1.5 이런식으로 4개 덩어리

struct WeaponCri
{
	int criticalRate;
	string words;
	int risingPercentage;
};

class WeaponCritical
{
private:
	//string m_WeaponCritical[][FOUR];//★구조체로 벡터 사용
	//무기 종류, 무기별 갯수
	map<string, WeaponCri> m_WeaponCritical;
public:
	void CreateWeaponCritical();
	//string(*GetWeaponCritical())[FOUR] { return m_WeaponCritical; }
	map<string, WeaponCri>
		GetWeaponCritical() { return m_WeaponCritical; }
};