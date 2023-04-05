#include "MapDraw.h"
#include "GameManager.h"
//#include "Character.h"
//#include "UI.h"

MapDraw::MapDraw()
{

	InitialSet();

	//m_BackIMG_X = 0;

	//m_Meter[METER_SHOW_FISRT].setMeter(METER_X, METER_VALUE_START);
	//m_Meter[METER_SHOW_SECOND].setMeter(METER_SECOND_X, METER_VALUE_START - METER_VALUE_GAP);


	
}

MapDraw::~MapDraw()
{
}

void MapDraw::InitialSet()
{
	m_BackIMG_X = 0;

	m_Meter[METER_SHOW_FISRT].InitialSet();
	m_Meter[METER_SHOW_SECOND].InitialSet();

	m_Meter[METER_SHOW_FISRT].setMeter(METER_X, METER_VALUE_START);
	m_Meter[METER_SHOW_SECOND].setMeter(METER_SECOND_X, METER_VALUE_START - METER_VALUE_GAP);

	m_BackIMG_List.clear();

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

void MapDraw::UpdateMap(float total_MoveDistance, float _Prev_MoveDistance)
{
	//Goal이 특정 좌표에 오면 배경+M 움직임을 멈춘다.(뒤로가서 골이 멀어지면 다시 배경 이동으로 전환한다.)
	if (GMMgr->Get_GoalEndPositionCheck() == false)
	{
		//Goal이 특정 위치에 도달하면 Map움직임 멈추기
		UpdateBack(total_MoveDistance, _Prev_MoveDistance);
		//meter
		for (int i = 0; i < METER_SHOW_COUNT; i++)
			m_Meter[i].UpdateMeter(total_MoveDistance, _Prev_MoveDistance);
	}
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

void MapDraw::UpdateBack(float total_MoveDistance, float _Prev_MoveDistance)
{// 토탈 이동 거리와 이전 턴의 이동 거리의 차이에 따라서 배경을 출력한다.
	//x축 이동거리만큼 쭉 옮겨버리고 출력 시작점까지 push pop을 반복한다.
	m_BackIMG_X += (_Prev_MoveDistance - total_MoveDistance);

	//앞으로 m_BackIMG_X가 더 작다
	if (m_BackIMG_X <= -IMG_SPECTATOR_W) //가장 처음 이미지가 -x라서 젋댓값을 체크한다.
	{
		m_BackIMG_X += IMG_SPECTATOR_W;
		m_BackIMG_List.push_back(m_BackIMG_List.front());
		m_BackIMG_List.pop_front();
	}
	else if (m_BackIMG_X > 0)
	{//뒤로 m_BackIMG_X가 더 크다
		m_BackIMG_X -= IMG_SPECTATOR_W;
		m_BackIMG_List.push_front(m_BackIMG_List.back());
		m_BackIMG_List.pop_back();
	}

	//m_Prev_MoveDistance = total_MoveDistance;
}

void MapDraw::UpdateClapBack(float deltaTime)
{
	if (m_ClapTime >= CLAP_BACK)
	{
		m_ClapTime = 0;

		for (auto &img : m_BackIMG_List)
		{
			if (img == IMG_BG_SPECTATOR_1)
				img = IMG_BG_SPECTATOR_2;
			else if (img == IMG_BG_SPECTATOR_2)
				img = IMG_BG_SPECTATOR_1;
		}
	}

	m_ClapTime += deltaTime;
}


bool MapDraw::MeterEnd_GoalActiveCheck()
{
	//for (int i = 0; i < METER_SHOW_COUNT; i++)
	//{
	//	if (m_Meter[i].Get_Meter_Value() == METER_VALUE_END)
	//		return true;
	//}

	if (m_Meter[METER_SHOW_FISRT].Get_Meter_Value() == METER_VALUE_END)
		return true;

	return false;
}