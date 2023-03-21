#include "UI.h"
#include "GameManager.h"

UI::UI()
{
	IMG sequence = IMG_MENU_TITLE_2;

	//빨->노->파
	for (int count = 0; count < STAR_TOTAL_COUNT; count++)
	{
		//★TODO::123순으로 받으면 ++로 한줄 코드 가능하다
		m_StarList.push_back(sequence);

		//switch (sequence)
		//{
		//case STAR_RED:
		//	m_StarList.push_back(IMG_MENU_TITLE_2);
		//	break;
		//case STAR_YELLOW:
		//	m_StarList.push_back(IMG_MENU_TITLE_3);
		//	break;
		//case STAR_BLUE:
		//	m_StarList.push_back(IMG_MENU_TITLE_4);
		//	break;
		//}

		if (sequence == IMG_MENU_TITLE_4)
			sequence = IMG_MENU_TITLE_2;
		else
			sequence = (IMG)(sequence + 1);
	}

	m_Point_Y = SELECT_PLAYER_1A;
	m_NotDrawCheck = false;
	m_StarTime = 0;
	m_FlickeringTime = 0;

}

UI::~UI()
{
}

void UI::DrawMenu(HDC hdc)
{
	DrawTitle(hdc);
	DrawStarFlow(hdc);
	DrawSelect(hdc);
	//flickeringCheck 를 이용해서 깜빡임 관리
	//★TODO::깜빡임은 Draw를 하지 않는 것으로 해결한다.
	//if (m_FlickeringCheck == true)
	//	DrawSelectBlack(hdc);
	DrawPoint(hdc);
}

void UI::DrawTitle(HDC hdc)
{
	BitMapMgr->GetImage(IMG_MENU_TITLE_START)->DrawTransparent(hdc, IMG_TITLE_X, IMG_TITLE_Y, IMG_TITLE_W, IMG_TITLE_H);
}

void UI::UpdateStarFlow(float deltaTime)
{
	if (m_StarTime >= STAR_SPEED)
	{
		m_StarTime = 0;

		//오른쪽으로 순환
		m_StarList.push_front(m_StarList.back());
		m_StarList.pop_back();
	}

	m_StarTime += deltaTime;
}

void UI::DrawStarFlow(HDC hdc)
{
	float x = IMG_STAR_X;
	float y = IMG_STAR_Y;
	int count = 0;

	for (auto img : m_StarList)
	{
		//top,right,bottom,left 배치를 위해서 별 하나하나의 좌표를 조정한다.
		if (count < STAR_TOP)
		{
			x += IMG_STAR_W;
		}
		else if (count < STAR_RIGHT)
		{
			if (count == STAR_TOP)
			{
				x += IMG_STAR_W;
				y += IMG_STAR_H;
			}
			else
				y += IMG_STAR_H;
		}
		else if (count < STAR_BOTTOM)
		{
			if (count == STAR_RIGHT)
			{
				x -= IMG_STAR_W;
				y += IMG_STAR_H;
			}
			else
				x -= IMG_STAR_W;
		}
		else
		{
			if (count == STAR_BOTTOM)
			{
				x -= IMG_STAR_W;
				y -= IMG_STAR_H;
			}
			else
				y -= IMG_STAR_W;
		}

		//빨->노->파
		BitMapMgr->GetImage(img)->DrawTransparent(hdc, x, y, IMG_STAR_W, IMG_STAR_H);

		count++;
	}
}

void UI::UpdateFlickering(float deltaTime)
{
	if (m_FlickeringTime >= FLICKERING_SPEED)
	{
		m_FlickeringTime = 0;

		m_NotDrawCheck = !m_NotDrawCheck; //true false 반대로 세팅
	}

	m_FlickeringTime += deltaTime;
}

void UI::DrawSelect(HDC hdc)
{
	//PLAY SELECT
	BitMapMgr->GetImage(IMG_MENU_SELECT_1)->DrawTransparent(hdc, IMG_SELECT_X, IMG_SELECT_Y, IMG_SELECT_W, IMG_SELECT_H);

	//1 PLAYER A ~ 2 PLAYERS B
	for (int i = 0; i < SELECT_PLAYER_COUNT; i++)
	{
		//★TODO::i로 커서 위치와 i가 같으면 그리는지 bool체크 후 깜빡이기
		if ( ! (i == m_Point_Y && m_NotDrawCheck == false)) //TODO::명칭 변경
			BitMapMgr->GetImage((IMG)(IMG_MENU_SELECT_2 + i))->DrawTransparent(hdc, IMG_SELECT_PLAYER_X, IMG_SELECT_PLAYER_Y + (IMG_SELECT_PLAYER_H * i), IMG_SELECT_PLAYER_W, IMG_SELECT_PLAYER_H);
		//{
		//	if (m_FlickeringCheck == false) //TODO::명칭 변경
		//	{
		//		//★TODO::i로 커서 위치와 i가 같으면 그리는지 bool체크 후 깜빡이기
		//		BitMapMgr->GetImage((IMG)(IMG_MENU_SELECT_2 + i))->DrawTransparent(hdc, IMG_SELECT_PLAYER_X, IMG_SELECT_PLAYER_Y + (IMG_SELECT_PLAYER_H * i), IMG_SELECT_PLAYER_W, IMG_SELECT_PLAYER_H);
		//	}
		//}
		//else
		//	BitMapMgr->GetImage((IMG)(IMG_MENU_SELECT_2 + i))->DrawTransparent(hdc, IMG_SELECT_PLAYER_X, IMG_SELECT_PLAYER_Y + (IMG_SELECT_PLAYER_H * i), IMG_SELECT_PLAYER_W, IMG_SELECT_PLAYER_H);
	}
}

//void UI::DrawSelectBlack(HDC hdc)
//{//★TODO::m_Point_Y를 i단위. 작은 범위로 바꿔서 초기위치y + 출력높이 * i로 해결한다.
//	BitMapMgr->GetImage(IMG_MENU_SELECT_6)->Draw(hdc, IMG_SELECT_PLAYER_X, m_Point_Y, IMG_SELECT_PLAYER_W, IMG_SELECT_PLAYER_H);
//}

void UI::DrawPoint(HDC hdc)
{
	BitMapMgr->GetImage(IMG_MENU_POINT)->DrawTransparent(hdc, IMG_POINT_X, IMG_SELECT_PLAYER_Y + (IMG_SELECT_PLAYER_H * m_Point_Y), IMG_POINT_W, IMG_POINT_H);
}

bool UI::KeyState_PointEnter()
{//★개선
	//space 키 누르면 끝도 없이 GGGG...GGGGetKeyState 무한 이동
	//&0x80 추가 GetAsyncKeyState와 동일한 움직임을 보이게 된다. GetAsyncKeyState와 결과값이 같아지게 된다

	if (GetAsyncKeyState(VK_RETURN) & 0x8000) //엔터 누르면 씬 전환
		return true;
	else if (GetAsyncKeyState(VK_UP) & 0x8000)
		KeyMove(MENU_KEY_UP);
	else if (GetAsyncKeyState(VK_DOWN) & 0x8000)
		KeyMove(MENU_KEY_DOWN);

	return false;
}

void UI::KeyMove(int move_Y)
{//★TODO::m_Point_Y의 단위를 i로 잡는다. 범위 체크도 1~3 같은 식으로
	m_Point_Y += move_Y;

	if (m_Point_Y < SELECT_PLAYER_1A) //위를 벗어나지 않게
		m_Point_Y = SELECT_PLAYER_1A;
	else if (m_Point_Y > SELECT_PLAYER_2B) //아래를 벗어나지 않게
		m_Point_Y = SELECT_PLAYER_2B;
}



//-----------점수 + 목숨 창----------------------------

void UI::DrawScoreSpace(HDC hdc)
{
	BitMapMgr->GetImage(IMG_INTERFACE_SCORE_OUTLINE)->DrawTransparent(hdc, IMG_SCORE_OUTLINE_X, IMG_SCORE_OUTLINE_Y, IMG_SCORE_OUTLINE_W, IMG_SCORE_OUTLINE_H);
}

void UI::DrawScore(HDC hdc)
{
}

void UI::DrawBonus(HDC hdc)
{
}

void UI::DrawLife(HDC hdc)
{
}

void UI::DrawStage(HDC hdc)
{
}
