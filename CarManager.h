//�������� ������ ����� ����� ����
#pragma once
#include "Car.h"
#include <list>
#include <conio.h> 

/*
kbhit - �ʿ� ������� <conio.h>
Ű���带 �Է� ���� ��� ���� ��ȯ�ϴ� �Լ�
*/

#define MAPSIZE_LENGTH 80
#define CREATE_CAR 3750
#define REVERSE 32

//enum CARSPEED
//{
//	REVERSE = 32,
//};

class CarManager
{
private:
public:
	void CarsManager();
	Car CreateCar();
	void CarMove(list<Car>& CarList);
	void CarSpeed(list<Car>& CarList, char ch);

	CarManager();
	~CarManager();
};

