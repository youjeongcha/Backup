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
	cout << "���ݷ� : " << w.Damage << " �����Ÿ� : " << endl << endl;
	cout << "���ݼӵ� : �д� " << w.Speed << "ȸ ����" << endl << endl;
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
			ShowWeapon(*iter);//iter�� �ּ�
	}
	cout << endl << "========================" << endl << endl;
}

void main()
{
	list<Weapon> WeaponList;
	//{} 
	//Weapon weapon = { WEAPON_SWORD, "�׷���Ʈ �ҵ�", 500, 5, 10 };���⼭ �׳� �ٷ�
	WeaponList.push_back({ WEAPON_SWORD, "�׷���Ʈ �ҵ�", 500, 5, 10 });//�߰�ȣ�� �� ��Ʈ��� �ǹ�
	WeaponList.push_back({ WEAPON_BOW,"����Ʈ����",50,300,60 });
	WeaponList.push_back({ WEAPON_GUN,"������",50,700,30 });
	WeaponList.push_back({ WEAPON_DAGGER, "â���Ǳ�����", 80,30, 320 });
	WeaponList.push_back({ WEAPON_SWORD,"���� �ҵ�",2000,4,20 });
	WeaponList.push_back({ WEAPON_WAND, "������������", 180,300, 50 });
	WeaponList.push_back({ WEAPON_BOW,"ũ�ν�����",100,400,30 });
	WeaponList.push_back({ WEAPON_HAMMER, "�丣�Ǹ�ġ", 50,50, 110 });

	for (int i = WEAPON_START; i < WEAPON_END; i++)
		ShowWeaponList(WeaponList, (WEAPON)i); // (WEAPON)i�� WEAPON ����
}