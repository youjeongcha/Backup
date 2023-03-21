#include "UI.h"
#include "GameManager.h"

UI::UI()
{
	STAR sequence = STAR_START;

	//빨->노->파
	for (int count = 0; count < STAR_TOTAL_COUNT; count++)
	{
		switch (sequence)
		{
		case STAR_RED:
			m_StarList.push_back(IMG_MENU_TITLE_3);
			break;
		case STAR_YELLOW:
			m_StarList.push_back(IMG_MENU_TITLE_4);
			break;
		case STAR_BLUE:
			m_StarList.push_back(IMG_MENU_TITLE_2);
			break;
		}

		if (sequence == STAR_END)
			sequence = STAR_START;
		else
			sequence = (STAR)(sequence + 1);
	}

	m_Point_Y = IMG_POINT_Y;
}

UI::~UI()
{
}

void UI::DrawMenu(HDC hdc)
{
	DrawTitle(hdc);
	DrawStarFlow(hdc);
	DrawSelect(hdc);
	DrawPoint(hdc);
}

void UI::DrawTitle(HDC hdc)
{
	BitMapMgr->GetImage(IMG_MENU_TITLE_START)->DrawTransparent(hdc, IMG_TITLE_X, IMG_TITLE_Y, IMG_TITLE_W, IMG_TITLE_H);
}

void UI::UpdateStarFlow(float deltaTime)
{
	if (m_Time >= STAR_SPEED)
	{
		m_Time = 0;

		//오른쪽으로 순환
		m_StarList.push_front(m_StarList.back());
		m_StarList.pop_back();
	}

	m_Time += deltaTime;
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

void UI::UpdateSelect(float deltaTime)
{
	
}

void UI::DrawSelect(HDC hdc)
{
	//PLAY SELECT
	BitMapMgr->GetImage(IMG_MENU_SELECT_1)->DrawTransparent(hdc, IMG_SELECT_X, IMG_SELECT_Y, IMG_SELECT_W, IMG_SELECT_H);

	//1 PLAYER A ~ 2 PLAYERS B
	for (int i = 0; i < SELECT_PLAYER_COUNT; i++)
	{
		BitMapMgr->GetImage((IMG)(IMG_MENU_SELECT_2 + i))->DrawTransparent(hdc, IMG_SELECT_PLAYER_X, IMG_SELECT_PLAYER_Y + (IMG_SELECT_PLAYER_H * i), IMG_SELECT_PLAYER_W, IMG_SELECT_PLAYER_H);
	}
}

void UI::DrawPoint(HDC hdc)
{
	BitMapMgr->GetImage((IMG)(IMG_MENU_POINT))->DrawTransparent(hdc, IMG_POINT_X, m_Point_Y, IMG_POINT_W, IMG_POINT_H);
}
