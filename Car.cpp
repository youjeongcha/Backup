#include "Car.h"
//차가 만들어져서, 이동하고, 사라지는 것까지.

void Car::DrawCar()
{
	gotoxy(m_fX, m_fY++);
	cout << "  ┌───┐ ";
	gotoxy(m_fX, m_fY++);
	cout << "┌┘ ▒▒ └┐";
	gotoxy(m_fX, m_fY);
	cout << "└○───○┘";

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
{//차 한칸씩 앞으로 이동(유사깜빡임)
	int CurClock = clock();

	if (CurClock - m_OldClock >= m_iSpeed)//1000에 1초
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