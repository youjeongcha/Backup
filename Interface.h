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
	//화면에 출력되는 텍스트. 저장 못하는 Print
	static void Print(string _string);
	//Box와 Sector와 Player 하단 정보
	static void DrawInterface(Player& player);
	//유저 인터페이스
	static void UnderInfo(Player& player); // ★ 이런건 인터페이스 그려주는 함수 쪽에 배치(완)
};

