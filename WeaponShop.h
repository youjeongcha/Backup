#pragma once
#include "DoubleSword.h"
#include "Bow.h"
#include "Hammer.h"
#include "Wand.h"
#include "Player.h" //�Լ� ���� �������� �ʿ�.
#include <map>
#include <vector>

#define FOUR 4

struct WeaponCritical
{
	int criticalRate;
	string words;
	int risingPercentage;
};

class WeaponShop
{
private:
	//vector�� value�� ������ �ִ� map Ű���� ����
	//��ĳ���� �ؼ� ��� //<>*�̰� ������ ����
	map<WEAPON, vector<Weapon*>> weaponMaps; //Ű::����Ÿ��. ����:vector<Weapon*>
	//�������� �ȿ����� ���⺰�� Ȯ���� �� �޶����� �Ϸ��� weapon���� ��ü ������ �����͸� ������ �ִ� ������ //vector ����� �ʿ䰡 ����.
public:
	WeaponShop();
	~WeaponShop();

	void ReadWeaponMap(); //txt ���Ͽ��� ������� ������� Weapon�� ����
	void Search_WeaponTypeList(WEAPON _type); //�ش� ���� Ÿ���� ������� ���� ��µȴ�.
	Weapon* Search_WeaponName(WEAPON _type, string _name);

	void FirstWeapon(Player* player);
	void Shop(Player* player);
	void Purchase(WEAPON eWeapon, Player* player);
	void PrintWeaponInfo(WEAPON weapon);

	void CreateWeaponCritical(); //���⺰ ũ��Ƽ�� Ȯ���� ��·�
};