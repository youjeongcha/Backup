//�������� ������ ����� ����� ����.
#include "CarManager.h"

/*
ť - �ڵ����� ���߿� ����ͺ��� ������� �ʴ´�.
���� - ���� ����� ���� ������� �ʴ´�. �ڿ��� �°� ���� ������⵵ �Ѵ�.
���� �����迭- �����Ͱ� ����Ǹ� �ȵȴ�. ��� ���� �ӵ��� ������.
���Ḯ��Ʈ - �������� �߰��� ���� ������ ����Ҷ�.
*/


void CarManager::CarsManager()
{//�� ���� - �� �� ������ ���� �ð� ����
	list<Car> CarList;

	int CurClock, CreateClock;
	CreateClock = clock();

	CarList.push_back(CreateCar());

	while (true)
	{
		char ch;

		//�� ����(time�� ���� �� ������)
		CurClock = clock();
		if (CurClock - CreateClock >= CREATE_CAR)
		{
			CarList.push_back(CreateCar());
			CreateClock = CurClock;
		}

		//kbhit
		if (kbhit()) //Ű���� �Է��� ������ 1, ���� ������ 0
		{
			ch = getch();

			//�ӵ� ���� (�����̽��� �Է� ������ �ӵ� ����)
			if (ch == REVERSE)
				CarSpeed(CarList, ch);
		}

		//�� �̵�
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
	for (list<Car>::iterator iter = CarList.begin(); iter != CarList.end();)//iter++) //iter++������ ��//erase�� �� iter�� ������ ���� �ּҷ� �ڵ����� �ޱ⿡. ++�ϸ� �ѹ� �� �Ѿ������.
	{
		iter->MoveCar();

		if (iter->Get_fX() >= MAPSIZE_LENGTH)
		{//���� �ʰ��� �� ���� �׸� ����
			iter->EraseCar();
			iter = CarList.erase(iter); //++);//������ �ϸ� ���� iter�� �ڵ����� ����Ų��. (++�ϸ� ������ �ٴ��� �ּҷ� �Ѿ��.) //linkedlist�� ���� �ƶ�.
		}
		else
			iter++; //++�� for���� ���� �ʰ� elseó��
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