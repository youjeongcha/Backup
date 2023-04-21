#include "Box.h"

void Box::Init(float _X, float _Y, float _W, float _H)
{//TODO::생성 랜덤으로
	m_Position.x = _X;
	m_Position.y = _Y;
	m_Half_W = _W * 0.5f;
	m_Half_H = _H * 0.5f;

	//부피
	//m_Volume = m_Half_W * m_Half_H;
	//질량
	m_Mass = m_Half_W * m_Half_H * 1;
	//속도

}

void Box::Draw(HDC hdc)
{
	Rectangle(hdc, m_Position.x - m_Half_W, m_Position.y - m_Half_H, m_Position.x + m_Half_W, m_Position.y + m_Half_H);
}

void Box::Update(float detaTime)
{
}
