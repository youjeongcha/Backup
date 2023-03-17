#include "MapDraw.h"
#include "GameManager.h"


MapDraw::MapDraw()
{
	m_BacIMG_X = 0;

	//7회 관중 -> 1회 코끼리 *2
	for (int count = 0; count < IMG_BACK_COUNT; count++)
	{
		switch (count)
		{
		case IMG_ELEPHANT_FIRST:
		case IMG_ELEPHANT_SECOND:
			mBackIMG_List.push_back(IMG_BG_ELEPHANT);
			break;
		default:
			mBackIMG_List.push_back(IMG_BG_SPECTATOR_1);
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

void MapDraw::UpdateSpectator(float deltaTime)
{
	m_BacIMG_X -= deltaTime * SPEED_BACK;

	if (-m_BacIMG_X >= IMG_SPECTATOR_W)
	{
		m_BacIMG_X += IMG_SPECTATOR_W;

		mBackIMG_List.push_back(mBackIMG_List.front());
		mBackIMG_List.pop_front();
	}
}

void MapDraw::DrawSpectator(HDC hdc)
{
	float x = m_BacIMG_X;

	//7회 관중 1회 코끼리
	for (auto img : mBackIMG_List)
	{
		switch (img)
		{
		case IMG_BG_ELEPHANT:
			BitMapMgr->GetImage(IMG_BG_ELEPHANT)->Draw(hdc, x, IMG_ELEPHANT_Y, IMG_ELEPHANT_W, IMG_ELEPHANT_H);
			x += IMG_ELEPHANT_W;
			break;
		default:
			BitMapMgr->GetImage(IMG_BG_SPECTATOR_1)->Draw(hdc, x, IMG_SPECTATOR_Y, IMG_SPECTATOR_W, IMG_SPECTATOR_H);
			x += IMG_SPECTATOR_W;
			break;
		}

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
