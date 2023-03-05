//여러개의 차들을 만들고 지우는 역할.
#include "CarManager.h"

/*
큐 - 자동차가 나중에 생긴것부터 사라지지 않는다.
스택 - 먼저 생긴게 먼저 사라지지 않는다. 뒤에서 온게 먼저 사라지기도 한다.
백터 가변배열- 데이터가 변경되면 안된다. 대신 접근 속도가 빠르다.
연결리스트 - 데이터의 추가와 변경 삭제가 빈번할때.
*/


void CarManager::CarsManager()
{//차 생성 - 앞 차 생성된 후의 시간 기준
	list<Car> CarList;

	int CurClock, CreateClock;
	CreateClock = clock();

	CarList.push_back(CreateCar());

	while (true)
	{
		char ch;

		//차 생성(time에 넣을 수 있을지)
		CurClock = clock();
		if (CurClock - CreateClock >= CREATE_CAR)
		{
			CarList.push_back(CreateCar());
			CreateClock = CurClock;
		}

		//kbhit
		if (kbhit()) //키보드 입력을 받으면 1, 받지 않으면 0
		{
			ch = getch();

			//속도 조절 (스페이스바 입력 들어오면 속도 반전)
			if (ch == REVERSE)
				CarSpeed(CarList, ch);
		}

		//차 이동
		CarMove(CarList);
	}
}

Car CarManager::CreateCar()
{
	Car tmpCar;
	return tmpCar;
}

void CarManager::CarMove(list<Car>& CarList)
{
	for (list<Car>::iterator iter = CarList.begin(); iter != CarList.end();)//iter++) //iter++지워야 함//erase될 때 iter가 삭제된 다음 주소로 자동으로 받기에. ++하면 한번 더 넘어가버린다.
	{
		iter->MoveCar();

		if (iter->Get_fX() >= MAPSIZE_LENGTH)
		{//범위 초과시 차 삭제 그림 지움
			iter->EraseCar();
			iter = CarList.erase(iter); //++);//삭제를 하면 다음 iter를 자동으로 가리킨다. (++하면 삭제한 다다음 주소로 넘어간다.) //linkedlist와 같은 맥락.
		}
		else
			iter++; //++은 for문에 쓰지 않고 else처리
	}
}

void CarManager::CarSpeed(list<Car>& CarList, char ch)
{
	for (list<Car>::iterator iter = CarList.begin(); iter != CarList.end(); iter++)
	{
		if (iter->Get_iSpeed() == MOVE_CAR_SLOW)
			iter->Set_iSpeed(MOVE_CAR_FAST);
		else
			iter->Set_iSpeed(MOVE_CAR_SLOW);
	}
}

CarManager::CarManager() {}
CarManager::~CarManager() {}