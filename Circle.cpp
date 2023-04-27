#include "Circle.h"

void Circle::Init(float _X, float _Y, float _R)
{//TODO::���� ��������
	m_ShapeType = SHAPE_CIRCLE;

	m_Position.x = _X;
	m_Position.y = _Y;
	m_Radius = _R;

	//����
	//m_Volume = m_Radius * m_Radius * 3.141592f;
	//����
	m_Mass = m_Radius * m_Radius * 3.141592f * 1;
	m_InvMass = 1 / m_Mass; //1/m_Mass�� �� �Ἥ �̸� ���������. m_Mass�� 0�� �Ǵ� ��찡 ����� �и� 0�� �� �� �����Ƿ� ������ �ɾ�ֵ� �ȴ�.
	//�ӵ�

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

		//TODO:: ���� ���Ϸ� �������� �ٽ� ���� �÷��ֱ� ��ȯ
		if (m_Position.y >= MAIN_H)
		{
			m_Position.x = MAIN_W * 0.5f + 20;
			m_Position.y = 20;
			//�߷� ���ӵ�
			Vector2 _Gravity = Gravity * deltaTime;
			m_Velocity = _Gravity;
		}
	}
}
