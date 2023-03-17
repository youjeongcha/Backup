#include "UI.h"
#include "GameManager.h"

UI::UI()
{
}

UI::~UI()
{
}

void UI::DrawMenu(HDC hdc)
{
	DrawTitle(hdc);
	DrawSelect(hdc);
}

void UI::DrawTitle(HDC hdc)
{
	BitMapMgr->GetImage(IMG_MENU_TITLE_START)->DrawTransparent(hdc, IMG_TITLE_X, IMG_TITLE_Y, IMG_TITLE_W, IMG_TITLE_H);
}

void UI::UpdateStarFlow(float deltaTime)
{
}

void UI::DrawStarFlow(HDC hdc)
{
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
}
