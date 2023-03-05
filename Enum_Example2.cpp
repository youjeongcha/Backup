#include<iostream>
#include<string>
#include<Windows.h>
#include<list>
using namespace std;

enum WEAPON
{
	WEAPON_START,
	WEAPON_DAGGER = 0,
	WEAPON_GUN,
	WEAPON_SWORD,
	WEAPON_WAND,
	WEAPON_BOW,
	WEAPON_HAMMER,
	WEAPON_END,
};

struct Weapon
{
	WEAPON WeaponType;
	string Name;
	int Damage;
	int Reach;
	int Speed;
};

void ShowWeapon(Weapon w)
{
	cout << "===" << w.Name << "===" << endl;
	cout << "공격력 : " << w.Damage << " 사정거리 : " << endl << endl;
	cout << "공격속도 : 분당 " << w.Speed << "회 공격" << endl << endl;
}

void ShowWeaponList(list<Weapon> WeaponList, WEAPON type)
{
	cout << "=========";
	switch (type)
	{
	case WEAPON_DAGGER:
		cout << "Dagger";
		break;
	case WEAPON_GUN:
		cout << "Gun";
		break;
	case WEAPON_SWORD:
		cout << "Sword";
		break;
	case WEAPON_WAND:
		cout << "Wand";
		break;
	case WEAPON_BOW:
		cout << "Bow";
		break;
	case WEAPON_HAMMER:
		cout << "Hammer";
		break;
	}
	cout << "=========" << endl << endl;
	for (list<Weapon>::iterator iter = WeaponList.begin(); iter != WeaponList.end(); iter++)
	{
		if (iter->WeaponType == type)
			ShowWeapon(*iter);//iter는 주소
	}
	cout << endl << "========================" << endl << endl;
}

void main()
{
	list<Weapon> WeaponList;
	//{} 
	//Weapon weapon = { WEAPON_SWORD, "그레이트 소드", 500, 5, 10 };여기서 그냥 바로
	WeaponList.push_back({ WEAPON_SWORD, "그레이트 소드", 500, 5, 10 });//중괄호가 한 세트라는 의미
	WeaponList.push_back({ WEAPON_BOW,"라이트보우",50,300,60 });
	WeaponList.push_back({ WEAPON_GUN,"리볼버",50,700,30 });
	WeaponList.push_back({ WEAPON_DAGGER, "창성의구원자", 80,30, 320 });
	WeaponList.push_back({ WEAPON_SWORD,"에고 소드",2000,4,20 });
	WeaponList.push_back({ WEAPON_WAND, "현자의지팡이", 180,300, 50 });
	WeaponList.push_back({ WEAPON_BOW,"크로스보우",100,400,30 });
	WeaponList.push_back({ WEAPON_HAMMER, "토르의망치", 50,50, 110 });

	for (int i = WEAPON_START; i < WEAPON_END; i++)
		ShowWeaponList(WeaponList, (WEAPON)i); // (WEAPON)i로 WEAPON 접근
}