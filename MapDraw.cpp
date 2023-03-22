#include "MapDraw.h"
#include "GameManager.h"


MapDraw::MapDraw()
{
	m_BackIMG_X = 0;

	//7ȸ ���� -> 1ȸ �ڳ��� *2
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
	{ //������ ����. (IMG �������� ��ȯ)
		
		if (abs(m_BackIMG_X) >= IMG_SPECTATOR_W) //���� ó�� �̹����� -x�� ������ üũ�Ѵ�.
		{
			m_BackIMG_X += IMG_SPECTATOR_W;

			m_BackIMG_List.push_back(m_BackIMG_List.front());
			m_BackIMG_List.pop_front();
		}

		m_BackIMG_X -= deltaTime * SPEED_BACK;
	}
	else if (GetAsyncKeyState(VK_LEFT) & 0x8000)
	{ //�ڷ� ����. (IMG ���������� ��ȯ)

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

	//7ȸ ���� 1ȸ �ڳ���
	for (auto img : m_BackIMG_List)
	{
		BitMapMgr->GetImage(img)->Draw(hdc, x, IMG_ELEPHANT_Y, IMG_ELEPHANT_W, IMG_ELEPHANT_H);

		x += IMG_SPECTATOR_W;
	}
}
