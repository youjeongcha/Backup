#include "Interface.h"

void Interface::DrawInterface(Player& player)
{
	MapDraw::BoxDraw(MAP_START, MAP_START, MAP_END_X, MAP_END_Y);
	MapDraw::BoxSectorDraw(MAP_END_X, MAP_END_Y, MAP_END_X, MAP_END_Y);
	UnderInfo(player);
}

void Interface::Print(string _string)
{ //���� ���ϴ� Print
	int Start_y = MAP_END_Y / GAP_3 * GAP_2;

	MapDraw::BoxErase(MAP_END_X, Start_y);
	GRAY
	MapDraw::DrawMidText(_string, MAP_END_X, MENUPRINT_START_Y + GAP_2);
	ORIGINAL

	getch();
}

void Interface::UnderInfo(Player& player)
{
	// �� enum���� ���� ���ó�� �°� ������. �����Ҷ����� ��� x(��)
	int x = USER_INFO_X; //MAP_END_X / GAP_3 * GAP_4 + ;
	int y = USER_INFO_Y;
	string tmp;

	tmp = "======" + player.Get_Name() + "(" + to_string(player.Get_Level()) + "Lv)======";
	MapDraw::DrawPoint(tmp, x, y++);

	tmp = "���ݷ� = " + to_string(player.Get_Attack());
	if (player.GetWeapon())
		tmp += "(+" + to_string(player.GetWeapon()->GetAttack()) + ")    ";
	else
		tmp += "    ";
	MapDraw::DrawPoint(tmp, x, y);
	tmp = "����� = " + to_string(player.Get_NowHP()) + "/" + to_string(player.Get_MaxHP()); // �� �Լ�ȭ // �� �Ʒ��� ���� �����̹Ƿ� �Լ�ȭ �ؼ� ��� 
	MapDraw::DrawPoint(tmp, x + GAP_9, y++);
	tmp = "����ġ = " + to_string(player.Get_NowEXP()) + "/" + to_string(player.Get_MaxEXP());
	MapDraw::DrawPoint(tmp, x, y++);

	// �� character���� �Լ�ȭ(�ϴ°� �� ���������� ��)
	//player.Print_HP_or_EXP("����� = ", to_string(player.Get_NowHP()), to_string(player.Get_MaxHP()), &y, &(x + GAP_9));
	//player.Print_HP_or_EXP("����� = ", to_string(player.Get_NowHP()), to_string(player.Get_MaxHP()), y++, x + GAP_9);
}