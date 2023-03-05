#include "Manager.h"


Manager::Manager()
{//this를 넣는 이유
	Time_Create_NewCar.SetTimer(TIMER_TYPE_LOOP, TIME_CREATE_NEWCAR, std::bind(&Manager::CreateCar, this)); //bind와 레퍼런스
	//함수포인터. 위 함수가 누구의 것인지 가리키기 위해서 함수를 호출하는 쪽에서 this를 표시해서 알려준다
}
void Manager::PlayLoop()
{
	CarList.push_back(new Car);
	while (true)
	{
		Input();
		CreateCarTimer();
		CarMoveController();
	}
}

void Manager::Input() //스페이스바 속도 조절
{
	if (kbhit()) // 속도 조절
	{
		if (getch() == MOVE_FASTMODE)
		{
			for (std::list<Car*>::iterator iter = CarList.begin(); iter != CarList.end(); iter++)
				(*iter)->Set_ModeChange();
		}
	}
}

void Manager::CreateCarTimer() //차 이동 타이머 old 갱신
{
	// 생성(list 추가)
	Time_Create_NewCar.CheckTimer();
}

void Manager::CreateCar() //차 생성해서 리스트 넣음
{
	CarList.push_back(new Car);
}


void Manager::CarMoveController() //차 이동 그림
{
	// 이동
	for (std::list<Car*>::iterator iter = CarList.begin(); iter != CarList.end(); )
	{
		(*iter)->Move_Car();
		if ((*iter)->EraseCheck_Car()) { //차가 지워지면(x축의 끝에 닿으면) true, 아니면 false
			Car* DeleteCar = *iter; //동적할당 해제 위해
			iter = CarList.erase(iter);
			delete DeleteCar;
		}
		else
			iter++;
	}
}

Manager::~Manager()
{//동적할당 해제

	for (std::list<Car*>::iterator iter = CarList.begin(); iter != CarList.end(); )
		delete* iter;

}