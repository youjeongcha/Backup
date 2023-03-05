#include "WeaponShop.h"

WeaponShop::WeaponShop()
{
	ReadWeaponMap(); //무기 종류별 존재하는 무기 개수
	CreateWeaponCritical(); //무기별 크리티컬 확률과 상승률
}
WeaponShop::~WeaponShop()
{
	weaponMaps.clear();
}

void WeaponShop::FirstWeapon(Player* player)
{
	int y = GAP_6;
	string sWeaponSetting[WEAPON_Count] = { "나무쌍검", "새총", "햄망치", "나무지팡이"};
	int select;
	Weapon* weapon;

	//맵 범위 그리기
	MapDraw::BoxErase(MAP_END_X, MAP_END_Y / GAP_3 * GAP_2);
	//창 띄우기
	MapDraw::DrawMidText("나무쌍검", MAP_END_X, y);
	MapDraw::DrawMidText("새총", MAP_END_X, y += GAP_2);
	MapDraw::DrawMidText("햄망치", MAP_END_X, y += GAP_2);
	MapDraw::DrawMidText("나무지팡이", MAP_END_X, y += GAP_2);
	//화살표
	//MenuLen 이동 가능한 메뉴 크기, AddCol 한 칸 넘어 이동, x,y에서 시작
	select = MapDraw::MenuSelectCursor(WEAPON_Count, GAP_2, MAP_END_X / 2 - GAP_6, y - GAP_3 * GAP_2);
	weapon = Search_WeaponName((WEAPON)select, sWeaponSetting[select - 1]);

	player->SetWeapon(weapon);
}

void WeaponShop::Shop(Player* player)
{
	while (true)
	{
		system("cls");
		//반복 돌때마다 초기화
		int y = GAP_8;
		int select;

		//맵 범위 그리기
		MapDraw::BoxDraw(MAP_START, MAP_START, MAP_END_X, MAP_END_Y);
		//SHOP 창 띄우기
		MapDraw::DrawMidText("♧ ♣ S H O P ♣ ♧", MAP_END_X, y);
		MapDraw::DrawMidText("쌍검", MAP_END_X, y += GAP_2);
		MapDraw::DrawMidText("활", MAP_END_X, y += GAP_2);
		MapDraw::DrawMidText("망치", MAP_END_X, y += GAP_2);
		MapDraw::DrawMidText("지팡이", MAP_END_X, y += GAP_2);
		MapDraw::DrawMidText("나가기", MAP_END_X, y += GAP_2);
		//화살표
		//MenuLen 이동 가능한 메뉴 크기, AddCol 한 칸 넘어 이동, x,y에서 시작

		select = MapDraw::MenuSelectCursor(WEAPON_Count + 1, GAP_2, MAP_END_X * 0.5 - GAP_6, y - GAP_3 * GAP_3 + GAP_1);
		switch (select)
		{
		case WEAPON_Count + 1:
			return;
		default:
			Purchase((WEAPON)select, player);
			break;
		}
	}
}

void WeaponShop::Purchase(WEAPON eWeapon, Player* player)
{
	WEAPON weaponType;
	string weaponName;
	int select;

	auto weaponList =  weaponMaps[eWeapon];
	vector<Weapon*>::iterator iter = weaponList.begin();

	while (true)
	{
		system("cls");
		//맵 범위 그리기
		MapDraw::BoxDraw(MAP_START, MAP_START, MAP_END_X, MAP_END_Y);
		//to_string 정수를 문자열로 바꿔주는 함수
		MapDraw::DrawMidText("보유 Gold : " + to_string(player->Get_Gold()), MAP_END_X, GAP_2);
		MapDraw::DrawMidText((*iter)->GetType() + " Shop", MAP_END_X, GAP_4);
		PrintWeaponInfo(eWeapon);//type의 무기들 전체 출력
		MapDraw::DrawMidText("나가기", MAP_END_X, (weaponMaps.size() + 1) * GAP_3);
		//화살표
		select = MapDraw::MenuSelectCursor(weaponList.size() + 1, GAP_3, MAP_END_X / 2 - GAP_9, GAP_6);
		//층 내려가면 구매할 수 있는 무기를 늘려주고 싶지만... 패스
		//MenuLen 이동 가능한 메뉴 크기, AddCol 한 칸 넘어 이동, x,y에서 시작

		
		switch (select)
		{ //여기서 금액 차감 + 무기 장착
		case 4: //돌아가기
			return;
		default:
			player->Set_Gold(player->Get_Gold() - weaponList[select - 1]->GetPrice()); //구매 가격만큼 Player Gold 차감
			player->SetWeapon(weaponList[select - 1]); //구매 무기 장착
			break;
		}
	}
}

void WeaponShop::PrintWeaponInfo(WEAPON weapon)
{
	Search_WeaponTypeList(weapon);
}

// ★ 명칭 변경, 이름으로 무기 찾기.(해결)
// ★ string으로 받지 말고 int로 받아서 처리 공간(해결)
Weapon* WeaponShop::Search_WeaponName(WEAPON _type, string _name)
{ //SearchTypeWeapon와 유사한 함수지만 방법이 다름
	vector<Weapon*> weapons = weaponMaps[_type];

	for (Weapon* weapon : weapons)
	{
		if (weapon->GetName() == _name)
			return weapon;
	}
}

// ★ 명칭 변경, 무기 타입별 출력 (해결)
// ★ string으로 받지 말고 int로 받아서 처리 공간 (해결)
void WeaponShop::Search_WeaponTypeList(WEAPON _type)
{ //해당 무기 타입의 무기들이 전부 출력된다.
	int y = GAP_6;
	vector<Weapon*> weapons = weaponMaps[_type]; //_type에 해당하는 종류의 무기들이 전부 vector에 깊은 복사된다.
	for (Weapon* weapon : weapons)
	{
		weapon->PrintInfo(y);
		y += GAP_3;
	}
}


void WeaponShop::ReadWeaponMap()
{ //키 값도 value 값도 이름 둘 다 있는 거 괜찮은지?
	ifstream load;
	string str, nameValue;
	int priceValue, attackValue;
	Weapon* weapon;
	WEAPON eWeaponType;

	load.open("SaveWeaponList.txt");
	while (!load.eof())
	{
		load >> str;
		if (str == "쌍검")
		{
			weapon = new DoubleSword;
			eWeaponType = WEAPON_DOUBLESWORD;
		}
		else if (str == "활")
		{
			weapon = new Bow;
			eWeaponType = WEAPON_BOW;
		}
		else if (str == "해머")
		{
			weapon = new Hammer;
			eWeaponType = WEAPON_HAMMER;
		}
		else if (str == "지팡이")
		{
			weapon = new Wand;
			eWeaponType = WEAPON_WAND;
		}

		load >> nameValue;
		load >> priceValue;
		load >> attackValue;

		weapon->Set(nameValue, priceValue, attackValue);
		weaponMaps[eWeaponType].push_back(weapon);
	}
}

void WeaponShop::CreateWeaponCritical()
{
	WeaponCritical tmpWeaponCritical;
	ifstream load;
	string _weaonType, _criticalWords;
	WEAPON eWeaponType;
	int _criticalRate;
	long double _risingPercentage;

	load.open("SaveWeaponCritical.txt");
	if (!load.eof())
	{
		for (int i = 0; i < WEAPON_Count; i++)
		{
			for (int j = 0; j < FOUR; j++)
			{
				load >> _weaonType; //tmpWeaponCritical.weaponType;

				if (_weaonType == "쌍검")
					eWeaponType = WEAPON_DOUBLESWORD;
				else if (_weaonType == "활")
					eWeaponType = WEAPON_BOW;
				else if (_weaonType == "해머")
					eWeaponType = WEAPON_HAMMER;
				else if (_weaonType == "지팡이")
					eWeaponType = WEAPON_WAND;

				vector<Weapon*> weapons = weaponMaps[eWeaponType]; //_type에 해당하는 종류의 무기들이 전부 vector에 깊은 복사된다.
				load >> _criticalRate;
				load >> _criticalWords;
				load >> _risingPercentage;

				for (Weapon* weapon : weapons)
				{
					weapon->SetCritical(_criticalRate, _criticalWords, _risingPercentage);
				}	
			}
		}
		load.close();
	}
}