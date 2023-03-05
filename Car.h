//���� ���������, �̵��ϰ�, ������� �ͱ���.
#pragma once
#include <iostream>
#include <Windows.h> //gotoxy COORD �̿뿡 �ʿ�
#include <time.h>
using namespace std;

#define CAR_X 10
#define CAR_Y 10
#define CARMOVE_X 0.08
#define MOVE_CAR_SLOW 300 //1000�� 1��
#define MOVE_CAR_FAST 50 //1000�� 1��


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

