#include "Box.h"

void Box::Init(float _X, float _Y, float _W, float _H)
{//TODO::생성 랜덤으로
	m_ShapeType = SHAPE_BOX;

	m_Position.x = _X;
	m_Position.y = _Y;
	m_Half_W = _W * 0.5f;
	m_Half_H = _H * 0.5f;

	//부피
	//m_Volume = m_Half_W * m_Half_H;
	//질량
	m_Mass = m_Half_W * m_Half_H * 1;
	m_InvMass = 1 / m_Mass; //1/m_Mass를 잘 써서 미리 멤버변수로. m_Mass가 0이 되는 경우가 생기면 분모가 0이 될 수 없으므로 제한을 걸어둬도 된다.
	//속도

}

void Box::Draw(HDC hdc)
{
	Rectangle(hdc, m_Position.x - m_Half_W, m_Position.y - m_Half_H, m_Position.x + m_Half_W, m_Position.y + m_Half_H);
}

void Box::Update(float deltaTime)
{
	if (!m_isStatic)
	{
		m_Position += m_Velocity * deltaTime;
		
		//TODO:: 일정 이하로 떨어지면 다시 위로 올려주기 순환
		if (m_Position.y >= MAIN_H)
		{
			m_Position.x = MAIN_W * 0.5f - 30;
			m_Position.y = 20;
			//중력 가속도
			Vector2 _Gravity = Gravity * deltaTime;
			m_Velocity = _Gravity;
		}
	}
}
