//여러개의 차들을 만들고 지우는 역할
#pragma once
#include "Car.h"
#include <list>
#include <conio.h> 

/*
kbhit - 필요 헤더파일 <conio.h>
키보드를 입력 했을 경우 참을 반환하는 함수
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

