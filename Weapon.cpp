#include "Weapon.h"

//Weapon::Weapon()
//{
//}

void Weapon::PrintInfo(int _Y)
{//xy�� ȿ�������� ��ġ �ʿ�
	string tmp;

	tmp = "���� : " + to_string(mPrice) + " Ÿ�� : " + mType; //to_string ������ ���ڿ��� �ٲ��ִ� �Լ�
	MapDraw::DrawMidText(tmp, MAP_END_X, _Y++);
	tmp = "�̸� : " + mName + " ���ݷ� : " + to_string(mAttack);
	MapDraw::DrawMidText(tmp, MAP_END_X, _Y++);
}

void Weapon::SimpleInfo(int _Y)
{
	string tmp;

	tmp = " Ÿ�� : " + mType + "   �̸� : " + mName + "   ���ݷ� : " + to_string(mAttack);
	MapDraw::DrawMidText(tmp, MAP_END_X, _Y);
}

//Weapon::~Weapon()
//{
//
//}