#include "MapDraw.h"
#include "GameManager.h"
//#include "Character.h"
//#include "UI.h"

MapDraw::MapDraw()
{
	m_BackIMG_X = 0;

	m_Meter[METER_SHOW_FISRT].setMeter(METER_X, METER_VALUE_START);
	m_Meter[METER_SHOW_SECOND].setMeter(METER_SECOND_X, METER_VALUE_START - METER_VALUE_GAP);
	//m_Meter[]
	//m_MeterIMG_List[METER_SHOW_FISRT] = METER_X;
	//m_MeterIMG_List[METER_SHOW_SECOND] = m_MeterIMG_List[METER_SHOW_FISRT] + METER_GAP;

	//m_Meter_Value[METER_SHOW_FISRT] = METER_VALUE_START;
	//m_Meter_Value[METER_SHOW_SECOND] = METER_VALUE_START - METER_VALUE_GAP;

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

void MapDraw::DrawMap(HDC hdc)
{
	//잔디
	DrawGrass(hdc);
	//관중 + 코끼리
	DrawBack(hdc);
	//meter
	for (int i = 0; i < METER_SHOW_COUNT; i++)
		m_Meter[i].DrawMeter(hdc);
}

void MapDraw::UpdateMap(float deltaTime, float thisTurn_MoveDistance)
{
	//Goal이 특정 위치에 도달하면 Map움직임 멈추기
	UpdateBack(deltaTime, thisTurn_MoveDistance);
	//meter
	for (int i = 0; i < METER_SHOW_COUNT; i++)
		m_Meter[i].UpdateMeter(deltaTime, thisTurn_MoveDistance);

}

void MapDraw::DrawGrass(HDC hdc)
{
	BitMapMgr->GetImage(IMG_BG_GRASS)->Draw(hdc, IMG_GRASS_X, IMG_GRASS_Y, IMG_GRASS_W, IMG_GRASS_H);
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



//void MapDraw::DrawMeterValue()
//{
//	for (int i = 0; i < METER_SHOW_COUNT; i++)
//		BitMapMgr->GetImage(IMG_INTERFACE_METER_OUTLINE)->DrawTransparent(hdc, m_Meter_List[i], METER_Y, METER_W, METER_H);
//}

void MapDraw::UpdateBack(float deltaTime, float thisTurn_MoveDistance)
{

	if (thisTurn_MoveDistance == 0)
		return;

	//먼저 이동을 하고 범위에 어긋나는지 확인하는게 맞다.
	//thisTurn_MoveDistance로 캐릭터가 이동한 만큼 이동하는게 맞다.
	m_BackIMG_X -= deltaTime * thisTurn_MoveDistance * SPEED_BACK;



	if (thisTurn_MoveDistance > 0)
	{ //앞으로 간다. (IMG 왼쪽으로 순환)
		
		if (-m_BackIMG_X > IMG_SPECTATOR_W) //가장 처음 이미지가 -x라서 젋댓값을 체크한다.
		{
			m_BackIMG_X += IMG_SPECTATOR_W;

			//if (m_BackIMG_X >= TRAVELDISTANCE_END)
			//{
			//	m_BackIMG_X = TRAVELDISTANCE_END;
			//	//return;
			//}

			m_BackIMG_List.push_back(m_BackIMG_List.front());
			m_BackIMG_List.pop_front();
		}
	}
	else if (thisTurn_MoveDistance < 0)
	{ //뒤로 간다. (IMG 오른쪽으로 순환)

		if (m_BackIMG_X >= -IMG_SPECTATOR_W)
		{
			m_BackIMG_X -= IMG_SPECTATOR_W;

			//if (m_BackIMG_X <= TRAVELDISTANCE_START)
			//{
			//	m_BackIMG_X = TRAVELDISTANCE_START;
			//	//return;
			//}

			m_BackIMG_List.push_front(m_BackIMG_List.back());
			m_BackIMG_List.pop_back();
		}
	}
}