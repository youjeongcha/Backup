#pragma once
#include "Mecro.h"
#include "Car.h"

class Manager
{
private:
	std::list<Car*> CarList; //동적할당을 하는 이유 : 함수포인터 bind를 사용해서 timer에서 조정을 하는데 데이터가 날아가버리므로 동적할당 이용 필수
	Timer Time_Create_NewCar;
public:
	Manager();
	~Manager();
	void PlayLoop();
	void CarMoveController(); //차 이동 그림
	void CreateCarTimer(); //차 이동 타이머
	void CreateCar(); //차 생성해서 리스트 넣음
	void Input(); //스페이스바 속도 조절
};
