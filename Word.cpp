#include "Word.h"
#include "Interface.h"

//★ 워드에는 무조건 string과 item이 필요해서. 디폴트 생성자는 삭제해주는 쪽이 안전성이 높아진다.
Word::Word()
{
	word = "";
	//m_XY.m_X = rand() % DROP_END_X + 3;
	//m_XY.m_Y = DROP_START_Y;
}
Word::Word(std::string _word, ITEM _itemType) : word(_word), m_ItemType(_itemType)
{ //멤버 이니셜라이저
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

	//아이템 타입에 따라 색상 다르게 출력
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
		//이런 식으로 적용해서 사용
		YELLOW
		break;
	default:
		return;
	}

	if (hideWordCheck)
		printWord = hide_word;

	MapDraw::DrawPoint(printWord, m_XY.m_X, m_XY.m_Y);

	ORIGINAL

	////아이템 워드 가리기
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
	//MapDraw::EraseWord(strSize, m_XY.m_X, m_XY.m_Y - 1); //EraseWord 안에서 for문 반복 돌리고 있다.
}

void Word::Drop()
{
	m_XY.m_Y++;
}