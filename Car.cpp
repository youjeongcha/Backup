#include "Car.h"
//���� ���������, �̵��ϰ�, ������� �ͱ���.

void Car::DrawCar()
{
	gotoxy(m_fX, m_fY++);
	cout << "  ���������� ";
	gotoxy(m_fX, m_fY++);
	cout << "���� �Ƣ� ����";
	gotoxy(m_fX, m_fY);
	cout << "���ۦ������ۦ�";

	m_fX += CARMOVE_X;
	m_fY = CAR_Y;
}

void Car::EraseCar()
{
	gotoxy(m_fX, m_fY++);
	cout << "             ";
	gotoxy(m_fX, m_fY++);
	cout << "              ";
	gotoxy(m_fX++, m_fY);
	cout << "              ";

	m_fX += CARMOVE_X;
	m_fY = CAR_Y;
}

void Car::MoveCar()
{//�� ��ĭ�� ������ �̵�(���������)
	int CurClock = clock();

	if (CurClock - m_OldClock >= m_iSpeed)//1000�� 1��
	{
		DrawCar();
		EraseCar();
		DrawCar();

		m_OldClock = CurClock;
	}
}


Car::Car()
{
	m_fX = CAR_X;
	m_fY = CAR_Y;
	m_iSpeed = MOVE_CAR_SLOW;
	m_OldClock = clock();
}
Car::~Car() {}