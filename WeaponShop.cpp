#include "WeaponShop.h"

WeaponShop::WeaponShop()
{
	ReadWeaponMap(); //���� ������ �����ϴ� ���� ����
	CreateWeaponCritical(); //���⺰ ũ��Ƽ�� Ȯ���� ��·�
}
WeaponShop::~WeaponShop()
{
	weaponMaps.clear();
}

void WeaponShop::FirstWeapon(Player* player)
{
	int y = GAP_6;
	string sWeaponSetting[WEAPON_Count] = { "�����ְ�", "����", "�ܸ�ġ", "����������"};
	int select;
	Weapon* weapon;

	//�� ���� �׸���
	MapDraw::BoxErase(MAP_END_X, MAP_END_Y / GAP_3 * GAP_2);
	//â ����
	MapDraw::DrawMidText("�����ְ�", MAP_END_X, y);
	MapDraw::DrawMidText("����", MAP_END_X, y += GAP_2);
	MapDraw::DrawMidText("�ܸ�ġ", MAP_END_X, y += GAP_2);
	MapDraw::DrawMidText("����������", MAP_END_X, y += GAP_2);
	//ȭ��ǥ
	//MenuLen �̵� ������ �޴� ũ��, AddCol �� ĭ �Ѿ� �̵�, x,y���� ����
	select = MapDraw::MenuSelectCursor(WEAPON_Count, GAP_2, MAP_END_X / 2 - GAP_6, y - GAP_3 * GAP_2);
	weapon = Search_WeaponName((WEAPON)select, sWeaponSetting[select - 1]);

	player->SetWeapon(weapon);
}

void WeaponShop::Shop(Player* player)
{
	while (true)
	{
		system("cls");
		//�ݺ� �������� �ʱ�ȭ
		int y = GAP_8;
		int select;

		//�� ���� �׸���
		MapDraw::BoxDraw(MAP_START, MAP_START, MAP_END_X, MAP_END_Y);
		//SHOP â ����
		MapDraw::DrawMidText("�� �� S H O P �� ��", MAP_END_X, y);
		MapDraw::DrawMidText("�ְ�", MAP_END_X, y += GAP_2);
		MapDraw::DrawMidText("Ȱ", MAP_END_X, y += GAP_2);
		MapDraw::DrawMidText("��ġ", MAP_END_X, y += GAP_2);
		MapDraw::DrawMidText("������", MAP_END_X, y += GAP_2);
		MapDraw::DrawMidText("������", MAP_END_X, y += GAP_2);
		//ȭ��ǥ
		//MenuLen �̵� ������ �޴� ũ��, AddCol �� ĭ �Ѿ� �̵�, x,y���� ����

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
		//�� ���� �׸���
		MapDraw::BoxDraw(MAP_START, MAP_START, MAP_END_X, MAP_END_Y);
		//to_string ������ ���ڿ��� �ٲ��ִ� �Լ�
		MapDraw::DrawMidText("���� Gold : " + to_string(player->Get_Gold()), MAP_END_X, GAP_2);
		MapDraw::DrawMidText((*iter)->GetType() + " Shop", MAP_END_X, GAP_4);
		PrintWeaponInfo(eWeapon);//type�� ����� ��ü ���
		MapDraw::DrawMidText("������", MAP_END_X, (weaponMaps.size() + 1) * GAP_3);
		//ȭ��ǥ
		select = MapDraw::MenuSelectCursor(weaponList.size() + 1, GAP_3, MAP_END_X / 2 - GAP_9, GAP_6);
		//�� �������� ������ �� �ִ� ���⸦ �÷��ְ� ������... �н�
		//MenuLen �̵� ������ �޴� ũ��, AddCol �� ĭ �Ѿ� �̵�, x,y���� ����

		
		switch (select)
		{ //���⼭ �ݾ� ���� + ���� ����
		case 4: //���ư���
			return;
		default:
			player->Set_Gold(player->Get_Gold() - weaponList[select - 1]->GetPrice()); //���� ���ݸ�ŭ Player Gold ����
			player->SetWeapon(weaponList[select - 1]); //���� ���� ����
			break;
		}
	}
}

void WeaponShop::PrintWeaponInfo(WEAPON weapon)
{
	Search_WeaponTypeList(weapon);
}

// �� ��Ī ����, �̸����� ���� ã��.(�ذ�)
// �� string���� ���� ���� int�� �޾Ƽ� ó�� ����(�ذ�)
Weapon* WeaponShop::Search_WeaponName(WEAPON _type, string _name)
{ //SearchTypeWeapon�� ������ �Լ����� ����� �ٸ�
	vector<Weapon*> weapons = weaponMaps[_type];

	for (Weapon* weapon : weapons)
	{
		if (weapon->GetName() == _name)
			return weapon;
	}
}

// �� ��Ī ����, ���� Ÿ�Ժ� ��� (�ذ�)
// �� string���� ���� ���� int�� �޾Ƽ� ó�� ���� (�ذ�)
void WeaponShop::Search_WeaponTypeList(WEAPON _type)
{ //�ش� ���� Ÿ���� ������� ���� ��µȴ�.
	int y = GAP_6;
	vector<Weapon*> weapons = weaponMaps[_type]; //_type�� �ش��ϴ� ������ ������� ���� vector�� ���� ����ȴ�.
	for (Weapon* weapon : weapons)
	{
		weapon->PrintInfo(y);
		y += GAP_3;
	}
}


void WeaponShop::ReadWeaponMap()
{ //Ű ���� value ���� �̸� �� �� �ִ� �� ��������?
	ifstream load;
	string str, nameValue;
	int priceValue, attackValue;
	Weapon* weapon;
	WEAPON eWeaponType;

	load.open("SaveWeaponList.txt");
	while (!load.eof())
	{
		load >> str;
		if (str == "�ְ�")
		{
			weapon = new DoubleSword;
			eWeaponType = WEAPON_DOUBLESWORD;
		}
		else if (str == "Ȱ")
		{
			weapon = new Bow;
			eWeaponType = WEAPON_BOW;
		}
		else if (str == "�ظ�")
		{
			weapon = new Hammer;
			eWeaponType = WEAPON_HAMMER;
		}
		else if (str == "������")
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

				if (_weaonType == "�ְ�")
					eWeaponType = WEAPON_DOUBLESWORD;
				else if (_weaonType == "Ȱ")
					eWeaponType = WEAPON_BOW;
				else if (_weaonType == "�ظ�")
					eWeaponType = WEAPON_HAMMER;
				else if (_weaonType == "������")
					eWeaponType = WEAPON_WAND;

				vector<Weapon*> weapons = weaponMaps[eWeaponType]; //_type�� �ش��ϴ� ������ ������� ���� vector�� ���� ����ȴ�.
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