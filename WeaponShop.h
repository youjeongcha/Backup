#pragma once
#include "DoubleSword.h"
#include "Bow.h"
#include "Hammer.h"
#include "Wand.h"
#include "Player.h" //함수 인자 받으려면 필요.
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
	//vector를 value로 가지고 있는 map 키값과 벨류
	//업캐스팅 해서 사용 //<>*이게 포인터 역할
	map<WEAPON, vector<Weapon*>> weaponMaps; //키::무기타입. 벨류:vector<Weapon*>
	//무기종류 안에서도 무기별로 확률이 또 달라지게 하려면 weapon무기 객체 각각이 데이터를 가지고 있는 쪽으로 //vector 사용할 필요가 없다.
public:
	WeaponShop();
	~WeaponShop();

	void ReadWeaponMap(); //txt 파일에서 만들어진 무기들을 Weapon에 저장
	void Search_WeaponTypeList(WEAPON _type); //해당 무기 타입의 무기들이 전부 출력된다.
	Weapon* Search_WeaponName(WEAPON _type, string _name);

	void FirstWeapon(Player* player);
	void Shop(Player* player);
	void Purchase(WEAPON eWeapon, Player* player);
	void PrintWeaponInfo(WEAPON weapon);

	void CreateWeaponCritical(); //무기별 크리티컬 확률과 상승률
};