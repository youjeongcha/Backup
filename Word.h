#pragma once
#include "Interface.h"

enum ITEM
{
	ITEM_NONE = -1,
	ITEM_NOMAL,
	ITEM_SPEED_UP,
	ITEM_SPEED_DOWN,
	ITEM_STOP,
	ITEM_SCREEN_CLEAR,
	ITEM_HIDE,
};

//★ 이거 WordManager쪽에서 관리
enum DROP
{
	//DROP_START_X = MAPSIZE_SART_X + 1,
	DROP_START_Y = MAPSIZE_SART_Y + 2,
	
	DROP_END_X = MAPSIZE_END_X - 13, //X축 좌표 (2 ~ MAPSIZE_END_X - 10) 생성되어야 하기 때문. rand % DROP_END_X + 2 할것.
	DROP_END_Y = MAPSIZE_END_Y, //좌표 바꾸고 y 한계 검사하고 출력하는 식이라. y축과 박스 창의 좌표가 같아야 출력이 맨 아래까지 된다.

	DROP_SPEED_STAGE1 = 600,
	DROP_SPEED_STAGE2 = 580,
	DROP_SPEED_STAGE3 = 560,
	DROP_SPEED_STAGE4 = 540,
	DROP_SPEED_STAGE5 = 520,
	DROP_SPEED_STAGE6 = 400,

	//DROP_SPEED_STAGE1 = 1000,
	//DROP_SPEED_STAGE2 = 900,
	//DROP_SPEED_STAGE3 = 850,
	//DROP_SPEED_STAGE4 = 800,
	//DROP_SPEED_STAGE5 = 750,
	//DROP_SPEED_STAGE6 = 700,
};

struct XY
{
	int m_X;
	int m_Y;
};


class Word
{
private:
	std::string word;
	//★ 이거 사용해서 for문 돌려가면서 == 표시하지 않게. 이니셜라이저에서 초기화한다.
	std::string clear_word;
	std::string hide_word;
	XY m_XY;
	ITEM m_ItemType;
public:
	Word();
	//멤버 이니셜라이저, 객체 생성될 때 사용.
	Word(std::string _word, ITEM _itemType);
	~Word();
	//★ 이니셜라이저에서 세팅
	void Set_Word(std::string _word, ITEM _itemType)
	{ word = _word; 
	//clear_word = string(word.size(), ' ');
	m_ItemType = _itemType; }
	std::string Get_Word() { return word; }

	void PrintWord(bool hideWordCheck = false);
	void EraseWord();
	void Drop();

	XY Get_XY() { return m_XY; }
	ITEM Get_ItemType() { return m_ItemType; }
	void Set_XY(XY _XY) { m_XY = _XY; }
};

