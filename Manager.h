#pragma once
#include "Mecro.h"
#include "Car.h"

class Manager
{
private:
	std::list<Car*> CarList; //�����Ҵ��� �ϴ� ���� : �Լ������� bind�� ����ؼ� timer���� ������ �ϴµ� �����Ͱ� ���ư������Ƿ� �����Ҵ� �̿� �ʼ�
	Timer Time_Create_NewCar;
public:
	Manager();
	~Manager();
	void PlayLoop();
	void CarMoveController(); //�� �̵� �׸�
	void CreateCarTimer(); //�� �̵� Ÿ�̸�
	void CreateCar(); //�� �����ؼ� ����Ʈ ����
	void Input(); //�����̽��� �ӵ� ����
};
