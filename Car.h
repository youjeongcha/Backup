//차가 만들어져서, 이동하고, 사라지는 것까지.
#pragma once
#include <iostream>
#include <Windows.h> //gotoxy COORD 이용에 필요
#include <time.h>
using namespace std;

#define CAR_X 10
#define CAR_Y 10
#define CARMOVE_X 0.08
#define MOVE_CAR_SLOW 300 //1000에 1초
#define MOVE_CAR_FAST 50 //1000에 1초


class Car
{
private:
	float m_fX;
	float m_fY;
	int m_iSpeed;
	int m_OldClock;

public:
	inline void DrawCar();
	inline void EraseCar();
	void MoveCar();

	inline float Get_fX() { return m_fX; }
	inline int Get_iSpeed() { return m_iSpeed; }
	inline void Set_iSpeed(int _iSpeed) { m_iSpeed = _iSpeed; }

	inline void gotoxy(int x, int y)
	{
		COORD Pos = { x, y };
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
	}

	Car();
	~Car();
};

