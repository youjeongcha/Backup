#include "MapDraw.h"
#include "GameManager.h"


MapDraw::MapDraw()
{
	m_BackIMG_X = 0;

	//7회 관중 -> 1회 코끼리 *2
	for (int count = 0; count < IMG_BACK_COUNT; count++)
	{
		switch (count)
		{
		case IMG_ELEPHANT_FIRST:
		case IMG_ELEPHANT_SECOND:
			m_BackIMG_List.push_back(IMG_BG_ELEPHANT);
			break;
		default:
			m_BackIMG_List.push_back(IMG_BG_SPECTATOR_1);
			break;
		}
	}
	
}

MapDraw::~MapDraw()
{
}

void MapDraw::DrawGrass(HDC hdc)
{
	BitMapMgr->GetImage(IMG_BG_GRASS)->Draw(hdc, IMG_GRASS_X, IMG_GRASS_Y, IMG_GRASS_W, IMG_GRASS_H);
}

void MapDraw::UpdateBack(float deltaTime)
{
	if (-m_BackIMG_X >= IMG_SPECTATOR_W)
	{
		m_BackIMG_X += IMG_SPECTATOR_W;

		//왼쪽으로 순환
		m_BackIMG_List.push_back(m_BackIMG_List.front());
		m_BackIMG_List.pop_front();
	}

	m_BackIMG_X -= deltaTime * SPEED_BACK;
}

void MapDraw::DrawBack(HDC hdc)
{
	float x = m_BackIMG_X;

	//7회 관중 1회 코끼리
	for (auto img : m_BackIMG_List)
	{
		switch (img)
		{
		case IMG_BG_ELEPHANT:
			BitMapMgr->GetImage(IMG_BG_ELEPHANT)->Draw(hdc, x, IMG_ELEPHANT_Y, IMG_ELEPHANT_W, IMG_ELEPHANT_H);
			break;
		default:
			BitMapMgr->GetImage(IMG_BG_SPECTATOR_1)->Draw(hdc, x, IMG_SPECTATOR_Y, IMG_SPECTATOR_W, IMG_SPECTATOR_H);
			break;
		}

		x += IMG_SPECTATOR_W;
	}
}

void MapDraw::DrawRing(HDC hdc)
{

}

void MapDraw::DrawPot(HDC hdc)
{

}

void MapDraw::DrawGoal(HDC hdc)
{

}
