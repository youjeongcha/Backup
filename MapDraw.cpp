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
	if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
	{ //앞으로 간다. (IMG 왼쪽으로 순환)
		
		if (abs(m_BackIMG_X) >= IMG_SPECTATOR_W) //가장 처음 이미지가 -x라서 젋댓값을 체크한다.
		{
			m_BackIMG_X += IMG_SPECTATOR_W;

			m_BackIMG_List.push_back(m_BackIMG_List.front());
			m_BackIMG_List.pop_front();
		}

		m_BackIMG_X -= deltaTime * SPEED_BACK;
	}
	else if (GetAsyncKeyState(VK_LEFT) & 0x8000)
	{ //뒤로 간다. (IMG 오른쪽으로 순환)

		if (m_BackIMG_X >= -IMG_SPECTATOR_W)
		{
			m_BackIMG_X -= IMG_SPECTATOR_W;

			m_BackIMG_List.push_front(m_BackIMG_List.back());
			m_BackIMG_List.pop_back();
		}

		m_BackIMG_X += deltaTime * SPEED_BACK;
	}
}

void MapDraw::DrawBack(HDC hdc)
{
	float x = m_BackIMG_X;

	//7회 관중 1회 코끼리
	for (auto img : m_BackIMG_List)
	{
		BitMapMgr->GetImage(img)->Draw(hdc, x, IMG_ELEPHANT_Y, IMG_ELEPHANT_W, IMG_ELEPHANT_H);

		x += IMG_SPECTATOR_W;
	}
}
