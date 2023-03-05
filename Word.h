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

//�� �̰� WordManager�ʿ��� ����
enum DROP
{
	//DROP_START_X = MAPSIZE_SART_X + 1,
	DROP_START_Y = MAPSIZE_SART_Y + 2,
	
	DROP_END_X = MAPSIZE_END_X - 13, //X�� ��ǥ (2 ~ MAPSIZE_END_X - 10) �����Ǿ�� �ϱ� ����. rand % DROP_END_X + 2 �Ұ�.
	DROP_END_Y = MAPSIZE_END_Y, //��ǥ �ٲٰ� y �Ѱ� �˻��ϰ� ����ϴ� ���̶�. y��� �ڽ� â�� ��ǥ�� ���ƾ� ����� �� �Ʒ����� �ȴ�.

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
	//�� �̰� ����ؼ� for�� �������鼭 == ǥ������ �ʰ�. �̴ϼȶ��������� �ʱ�ȭ�Ѵ�.
	std::string clear_word;
	std::string hide_word;
	XY m_XY;
	ITEM m_ItemType;
public:
	Word();
	//��� �̴ϼȶ�����, ��ü ������ �� ���.
	Word(std::string _word, ITEM _itemType);
	~Word();
	//�� �̴ϼȶ��������� ����
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

