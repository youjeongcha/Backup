#include "Word.h"
#include "Interface.h"

//�� ���忡�� ������ string�� item�� �ʿ��ؼ�. ����Ʈ �����ڴ� �������ִ� ���� �������� ��������.
Word::Word()
{
	word = "";
	//m_XY.m_X = rand() % DROP_END_X + 3;
	//m_XY.m_Y = DROP_START_Y;
}
Word::Word(std::string _word, ITEM _itemType) : word(_word), m_ItemType(_itemType)
{ //��� �̴ϼȶ�����
	clear_word = std::string(word.size(), ' ');
	hide_word = std::string(word.size(), '=');

	m_XY.m_X = rand() % DROP_END_X + 3;
	m_XY.m_Y = DROP_START_Y;
}
Word::~Word()
{

}

void Word::PrintWord(bool hideWordCheck)
{
	std::string printWord = word;//"";

	//������ Ÿ�Կ� ���� ���� �ٸ��� ���
	switch (m_ItemType)
	{
	case ITEM_NOMAL:
		break;
	case ITEM_SPEED_UP:
		GREEN
		break;
	case ITEM_SPEED_DOWN:
		BLOOD
		break;
	case ITEM_STOP:
		GOLD
		break;
	case ITEM_SCREEN_CLEAR:
		BLUE
		break;
	case ITEM_HIDE:
		//�̷� ������ �����ؼ� ���
		YELLOW
		break;
	default:
		return;
	}

	if (hideWordCheck)
		printWord = hide_word;

	MapDraw::DrawPoint(printWord, m_XY.m_X, m_XY.m_Y);

	ORIGINAL

	////������ ���� ������
	//if (hideWordCheck)
	//{
	//	for (int i = 0; i < word.size(); i++)
	//		hideWord += "=";
	//	MapDraw::DrawPoint(hideWord, m_XY.m_X, m_XY.m_Y);
	//}
	//else
	//	MapDraw::DrawPoint(word, m_XY.m_X, m_XY.m_Y);
	//MapDraw::DrawPoint(printWord, m_XY.m_X, m_XY.m_Y);
	//ORIGINAL
}

void Word::EraseWord()
{
	MapDraw::DrawPoint(clear_word, m_XY.m_X, m_XY.m_Y);
	//MapDraw::EraseWord(strSize, m_XY.m_X, m_XY.m_Y - 1); //EraseWord �ȿ��� for�� �ݺ� ������ �ִ�.
}

void Word::Drop()
{
	m_XY.m_Y++;
}