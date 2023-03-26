#include "MapDraw.h"
#include "GameManager.h"
//#include "Character.h"
//#include "UI.h"

MapDraw::MapDraw()
{
	m_BackIMG_X = 0;
	m_MeterIMG_List[METER_SHOW_FISRT] = METER_X;
	m_MeterIMG_List[METER_SHOW_SECOND] = m_MeterIMG_List[METER_SHOW_FISRT] + METER_GAP;

	m_Meter_Value[METER_SHOW_FISRT] = METER_VALUE_START;
	m_Meter_Value[METER_SHOW_SECOND] = METER_VALUE_START - METER_VALUE_GAP;

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
	DrawMeter(hdc);
}

void MapDraw::UpdateMap(float deltaTime, float thisTurn_MoveDistance)
{
	//map
	UpdateBack(deltaTime, thisTurn_MoveDistance);
	//meter
	UpdateMeter(deltaTime, thisTurn_MoveDistance);

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

void MapDraw::DrawMeter(HDC hdc)
{
	std::wstring str;

	for (int i = 0; i < METER_SHOW_COUNT; i++)
	{
		BitMapMgr->GetImage(IMG_INTERFACE_METER_OUTLINE)->DrawTransparent(hdc, m_MeterIMG_List[i], METER_Y, METER_W, METER_H);

		SetBkMode(hdc, TRANSPARENT); //글자 뒷배경 투명화
		//SetBkColor(hdc, RGB(0, 0, 0));
		SetTextColor(hdc, RGB(255, 255, 255)); //글자 색 변경(흰색)

		SelectObject(hdc, GMMgr->Get_Font(FONT_STAGE));
		str = std::to_wstring(m_Meter_Value[i]);
		TextOut(hdc, m_MeterIMG_List[i] + METER_VALUE_X_GAP, METER_VALUE_Y, str.c_str(), str.length());
	}
}

//void MapDraw::DrawMeterValue()
//{
//	for (int i = 0; i < METER_SHOW_COUNT; i++)
//		BitMapMgr->GetImage(IMG_INTERFACE_METER_OUTLINE)->DrawTransparent(hdc, m_Meter_List[i], METER_Y, METER_W, METER_H);
//}

void MapDraw::UpdateBack(float deltaTime, float thisTurn_MoveDistance)
{
	if (thisTurn_MoveDistance > 0)
	{ //앞으로 간다. (IMG 왼쪽으로 순환)
		
		if (abs(m_BackIMG_X) >= IMG_SPECTATOR_W) //가장 처음 이미지가 -x라서 젋댓값을 체크한다.
		{
			m_BackIMG_X += IMG_SPECTATOR_W;

			m_BackIMG_List.push_back(m_BackIMG_List.front());
			m_BackIMG_List.pop_front();
		}

		m_BackIMG_X -= deltaTime * SPEED_BACK;
	}
	else if (thisTurn_MoveDistance < 0)
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



void MapDraw::UpdateMeter(float deltaTime, float thisTurn_MoveDistance)
{
	if (thisTurn_MoveDistance > 0)
	{ //앞으로 간다. (IMG 왼쪽으로 순환)

		if (m_MeterIMG_List[METER_SHOW_FISRT] <= METER_START_SHOW_X) //가장 처음 이미지가 -x라서 젋댓값을 체크한다.
		{
			m_MeterIMG_List[METER_SHOW_FISRT] += METER_GAP;
			m_MeterIMG_List[METER_SHOW_SECOND] += METER_GAP;

			m_Meter_Value[METER_SHOW_FISRT] -= METER_VALUE_GAP;
			m_Meter_Value[METER_SHOW_SECOND] -= METER_VALUE_GAP;

			//m_Meter_List.push_back(m_BackIMG_List.front());
			//m_BackIMG_List.pop_front();
		}

		m_MeterIMG_List[METER_SHOW_FISRT] -= deltaTime * SPEED_BACK;
		m_MeterIMG_List[METER_SHOW_SECOND] -= deltaTime * SPEED_BACK;
	}
	else if (thisTurn_MoveDistance < 0)
	{ //뒤로 간다. (IMG 오른쪽으로 순환)

		if (m_MeterIMG_List[METER_SHOW_SECOND] >= METER_END_SHOW_X)
		{
			m_MeterIMG_List[METER_SHOW_FISRT] -= METER_GAP;
			m_MeterIMG_List[METER_SHOW_SECOND] -= METER_GAP;

			m_Meter_Value[METER_SHOW_FISRT] += METER_VALUE_GAP;
			m_Meter_Value[METER_SHOW_SECOND] += METER_VALUE_GAP;

			//m_BackIMG_List.push_front(m_BackIMG_List.back());
			//m_BackIMG_List.pop_back();
		}

		m_MeterIMG_List[METER_SHOW_FISRT] += deltaTime * SPEED_BACK;
		m_MeterIMG_List[METER_SHOW_SECOND] += deltaTime * SPEED_BACK;
	}
}