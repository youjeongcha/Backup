#include "Circle.h"

void Circle::Init(float _X, float _Y, float _R)
{//TODO::생성 랜덤으로
	m_ShapeType = SHAPE_CIRCLE;

	m_Position.x = _X;
	m_Position.y = _Y;
	m_Radius = _R;

	//부피
	//m_Volume = m_Radius * m_Radius * 3.141592f;
	//질량
	m_Mass = m_Radius * m_Radius * 3.141592f * 1;
	m_InvMass = 1 / m_Mass; //1/m_Mass를 잘 써서 미리 멤버변수로. m_Mass가 0이 되는 경우가 생기면 분모가 0이 될 수 없으므로 제한을 걸어둬도 된다.
	//속도

}

void Circle::Draw(HDC hdc)
{
	Ellipse(hdc, m_Position.x - m_Radius, m_Position.y - m_Radius, m_Position.x + m_Radius, m_Position.y + m_Radius);
}

void Circle::Update(float deltaTime)
{
	if (!m_isStatic)
	{
		m_Position += m_Velocity * deltaTime;

		//TODO:: 일정 이하로 떨어지면 다시 위로 올려주기 순환
		if (m_Position.y >= MAIN_H)
		{
			m_Position.x = MAIN_W * 0.5f + 20;
			m_Position.y = 20;
			//중력 가속도
			Vector2 _Gravity = Gravity * deltaTime;
			m_Velocity = _Gravity;
		}
	}
}
