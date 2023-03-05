#include "Weapon.h"

//Weapon::Weapon()
//{
//}

void Weapon::PrintInfo(int _Y)
{//xy축 효율적으로 배치 필요
	string tmp;

	tmp = "가격 : " + to_string(mPrice) + " 타입 : " + mType; //to_string 정수를 문자열로 바꿔주는 함수
	MapDraw::DrawMidText(tmp, MAP_END_X, _Y++);
	tmp = "이름 : " + mName + " 공격력 : " + to_string(mAttack);
	MapDraw::DrawMidText(tmp, MAP_END_X, _Y++);
}

void Weapon::SimpleInfo(int _Y)
{
	string tmp;

	tmp = " 타입 : " + mType + "   이름 : " + mName + "   공격력 : " + to_string(mAttack);
	MapDraw::DrawMidText(tmp, MAP_END_X, _Y);
}

//Weapon::~Weapon()
//{
//
//}