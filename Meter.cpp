#include "Meter.h"
#include "GameManager.h"


Meter::Meter()
{
	m_MeterIMG_X = 0;
	m_Meter_Value = 0;
}
Meter::~Meter()
{
}

void Meter::DrawMeter(HDC hdc)
{
	std::wstring str;

	BitMapMgr->GetImage(IMG_INTERFACE_METER_OUTLINE)->DrawTransparent(hdc, m_MeterIMG_X, METER_Y, METER_W, METER_H);

	SetBkMode(hdc, TRANSPARENT); //���� �޹�� ����ȭ
	//SetBkColor(hdc, RGB(0, 0, 0));
	SetTextColor(hdc, RGB(255, 255, 255)); //���� �� ����(���)

	SelectObject(hdc, GMMgr->Get_Font(FONT_STAGE));
	str = std::to_wstring(m_Meter_Value);
	TextOut(hdc, m_MeterIMG_X + METER_VALUE_X_GAP - str.length() * 10, METER_VALUE_Y, str.c_str(), str.length());
}


void Meter::UpdateMeter(float deltaTime, float thisTurn_MoveDistance)
{
	//m_MeterIMG_X -= deltaTime * SPEED_METER * thisTurn_MoveDistance;
	m_MeterIMG_X -= deltaTime * thisTurn_MoveDistance;

	if (thisTurn_MoveDistance > 0)
	{ //������ ����. (IMG �������� ��ȯ)

		if (m_MeterIMG_X <= METER_START_SHOW_X) //���� ó�� �̹����� -x�� ������ üũ�Ѵ�.
		{
			m_MeterIMG_X += METER_ACROSS_ONE; //�̹��� �ϳ� �ǳʼ� ���
			m_Meter_Value -= METER_VALUE_ACROSS_ONE; //�̹��� �ϳ� �ǳʼ� -20
		}
	}
	else if (thisTurn_MoveDistance < 0)
	{ //�ڷ� ����. (IMG ���������� ��ȯ)

		if (m_MeterIMG_X >= METER_END_SHOW_X)
		{
			m_MeterIMG_X -= METER_ACROSS_ONE;
			m_Meter_Value += METER_VALUE_ACROSS_ONE;
		}
	}
}