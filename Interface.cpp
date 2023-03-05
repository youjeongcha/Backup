#include "Interface.h"

void Interface::DrawInterface(Player& player)
{
	MapDraw::BoxDraw(MAP_START, MAP_START, MAP_END_X, MAP_END_Y);
	MapDraw::BoxSectorDraw(MAP_END_X, MAP_END_Y, MAP_END_X, MAP_END_Y);
	UnderInfo(player);
}

void Interface::Print(string _string)
{ //저장 못하는 Print
	int Start_y = MAP_END_Y / GAP_3 * GAP_2;

	MapDraw::BoxErase(MAP_END_X, Start_y);
	GRAY
	MapDraw::DrawMidText(_string, MAP_END_X, MENUPRINT_START_Y + GAP_2);
	ORIGINAL

	getch();
}

void Interface::UnderInfo(Player& player)
{
	// ★ enum으로 세팅 사용처에 맞게 가독성. 실행할때마다 계산 x(완)
	int x = USER_INFO_X; //MAP_END_X / GAP_3 * GAP_4 + ;
	int y = USER_INFO_Y;
	string tmp;

	tmp = "======" + player.Get_Name() + "(" + to_string(player.Get_Level()) + "Lv)======";
	MapDraw::DrawPoint(tmp, x, y++);

	tmp = "공격력 = " + to_string(player.Get_Attack());
	if (player.GetWeapon())
		tmp += "(+" + to_string(player.GetWeapon()->GetAttack()) + ")    ";
	else
		tmp += "    ";
	MapDraw::DrawPoint(tmp, x, y);
	tmp = "생명력 = " + to_string(player.Get_NowHP()) + "/" + to_string(player.Get_MaxHP()); // ★ 함수화 // ★ 아래와 같은 형식이므로 함수화 해서 사용 
	MapDraw::DrawPoint(tmp, x + GAP_9, y++);
	tmp = "경험치 = " + to_string(player.Get_NowEXP()) + "/" + to_string(player.Get_MaxEXP());
	MapDraw::DrawPoint(tmp, x, y++);

	// ★ character에서 함수화(하는게 더 더러워지는 듯)
	//player.Print_HP_or_EXP("생명력 = ", to_string(player.Get_NowHP()), to_string(player.Get_MaxHP()), &y, &(x + GAP_9));
	//player.Print_HP_or_EXP("생명력 = ", to_string(player.Get_NowHP()), to_string(player.Get_MaxHP()), y++, x + GAP_9);
}