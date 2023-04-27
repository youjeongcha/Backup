#include "Box.h"

void Box::Init(float _X, float _Y, float _W, float _H)
{//TODO::���� ��������
	m_ShapeType = SHAPE_BOX;

	m_Position.x = _X;
	m_Position.y = _Y;
	m_Half_W = _W * 0.5f;
	m_Half_H = _H * 0.5f;

	//����
	//m_Volume = m_Half_W * m_Half_H;
	//����
	m_Mass = m_Half_W * m_Half_H * 1;
	m_InvMass = 1 / m_Mass; //1/m_Mass�� �� �Ἥ �̸� ���������. m_Mass�� 0�� �Ǵ� ��찡 ����� �и� 0�� �� �� �����Ƿ� ������ �ɾ�ֵ� �ȴ�.
	//�ӵ�

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
		
		//TODO:: ���� ���Ϸ� �������� �ٽ� ���� �÷��ֱ� ��ȯ
		if (m_Position.y >= MAIN_H)
		{
			m_Position.x = MAIN_W * 0.5f - 30;
			m_Position.y = 20;
			//�߷� ���ӵ�
			Vector2 _Gravity = Gravity * deltaTime;
			m_Velocity = _Gravity;
		}
	}
}
