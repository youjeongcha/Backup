#pragma once
#include "Player.h"
#include "MapDraw.h"

enum USER_INFO
{
	USER_INFO_X = GAP_3,
	USER_INFO_Y = GAP_2 + (MAP_END_Y / GAP_3 * GAP_2),
};

class Interface
{
public:
	//ȭ�鿡 ��µǴ� �ؽ�Ʈ. ���� ���ϴ� Print
	static void Print(string _string);
	//Box�� Sector�� Player �ϴ� ����
	static void DrawInterface(Player& player);
	//���� �������̽�
	static void UnderInfo(Player& player); // �� �̷��� �������̽� �׷��ִ� �Լ� �ʿ� ��ġ(��)
};

