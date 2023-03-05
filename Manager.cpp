#include "Manager.h"


Manager::Manager()
{//this�� �ִ� ����
	Time_Create_NewCar.SetTimer(TIMER_TYPE_LOOP, TIME_CREATE_NEWCAR, std::bind(&Manager::CreateCar, this)); //bind�� ���۷���
	//�Լ�������. �� �Լ��� ������ ������ ����Ű�� ���ؼ� �Լ��� ȣ���ϴ� �ʿ��� this�� ǥ���ؼ� �˷��ش�
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

void Manager::Input() //�����̽��� �ӵ� ����
{
	if (kbhit()) // �ӵ� ����
	{
		if (getch() == MOVE_FASTMODE)
		{
			for (std::list<Car*>::iterator iter = CarList.begin(); iter != CarList.end(); iter++)
				(*iter)->Set_ModeChange();
		}
	}
}

void Manager::CreateCarTimer() //�� �̵� Ÿ�̸� old ����
{
	// ����(list �߰�)
	Time_Create_NewCar.CheckTimer();
}

void Manager::CreateCar() //�� �����ؼ� ����Ʈ ����
{
	CarList.push_back(new Car);
}


void Manager::CarMoveController() //�� �̵� �׸�
{
	// �̵�
	for (std::list<Car*>::iterator iter = CarList.begin(); iter != CarList.end(); )
	{
		(*iter)->Move_Car();
		if ((*iter)->EraseCheck_Car()) { //���� ��������(x���� ���� ������) true, �ƴϸ� false
			Car* DeleteCar = *iter; //�����Ҵ� ���� ����
			iter = CarList.erase(iter);
			delete DeleteCar;
		}
		else
			iter++;
	}
}

Manager::~Manager()
{//�����Ҵ� ����

	for (std::list<Car*>::iterator iter = CarList.begin(); iter != CarList.end(); )
		delete* iter;

}