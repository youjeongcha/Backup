#include "WeaponCritical.h"

//★ 이거 잘 받아지는 지 체크 해야함

void WeaponCritical::CreateWeaponCritical()
{
	ifstream load;
	string str;
	load.open("SaveWeaponCritical.txt");

	if (!load.eof())
	{
		for (int i = 0; i < WEAPON_Count; i++)
		{
			load >> str;

			for (int j = 0; j < FOUR; j++)
			{
				load >> m_WeaponCritical[str].criticalRate;
				load >> m_WeaponCritical[str].words;
				load >> m_WeaponCritical[str].risingPercentage;
			}
		}
		load.close();
	}
}