#pragma once
//#include "Person.h"
class Observer; //�� �̷��� ������ �ϴ� ��� �����ͷ� ����� ���� �ִ�

class Subject abstract //�߻� Ŭ����
{
private:
public:
	Subject();
	virtual ~Subject();
	virtual Observer* Observer_Add(Observer* userName) abstract; //���� �����Լ� //��
	virtual void Observer_InfoUpdate() abstract;//���� �����Լ� //��󿡼� ���������� �����͸� ������ ���(Ǫ�� ���)
};

