#include "Meter.h"
#include "GameManager.h"


Meter::Meter()
{
	InitialSet();
	/*m_MeterIMG_X = 0;
	m_Meter_Value = 0;*/
}
Meter::~Meter()
{
}

void Meter::InitialSet()
{
	m_MeterIMG_X = 0;
	m_Meter_Value = 0;
}

void Meter::DrawMeter(HDC hdc)
{
	std::wstring str;

	BitMapMgr->GetImage(IMG_INTERFACE_METER_OUTLINE)->DrawTransparent(hdc, m_MeterIMG_X, METER_Y, METER_W, METER_H);

	SetBkMode(hdc, TRANSPARENT); //글자 뒷배경 투명화
	//SetBkColor(hdc, RGB(0, 0, 0));
	SetTextColor(hdc, RGB(255, 255, 255)); //글자 색 변경(흰색)

	SelectObject(hdc, GMMgr->Get_Font(FONT_STAGE));
	str = std::to_wstring(m_Meter_Value);
	TextOut(hdc, m_MeterIMG_X + METER_VALUE_X_GAP - str.length() * 10, METER_VALUE_Y, str.c_str(), str.length());
}


void Meter::UpdateMeter(float total_MoveDistance, float _Prev_MoveDistance)
{
	m_MeterIMG_X += (_Prev_MoveDistance - total_MoveDistance) *10;
	
	if (m_MeterIMG_X <= METER_START_SHOW_X) //가장 처음 이미지가 -x라서 절댓값을 체크한다.
	{ //앞으로 간다. (IMG 왼쪽으로 순환)
		m_MeterIMG_X += METER_ACROSS_ONE; //이미지 하나 건너서 출력
		m_Meter_Value -= METER_VALUE_ACROSS_ONE; //이미지 하나 건너서 -20
	}
	else if (m_MeterIMG_X >= METER_END_SHOW_X)
	{ //뒤로 간다. (IMG 오른쪽으로 순환)
		m_MeterIMG_X -= METER_ACROSS_ONE;
		m_Meter_Value += METER_VALUE_ACROSS_ONE;
	}

	//m_Prev_MoveDistance = total_MoveDistance;
}