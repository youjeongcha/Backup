#pragma once
#include "Mecro.h"

class Observer abstract //�߻� Ŭ����
{
private:
public:
	Observer();
	virtual ~Observer();
	virtual void InfoUpdate(std::string mDate, std::string newsInfo) abstract; //���� �����Լ� //���������� ����� �����͸� �������� ���(Ǯ ���)
	virtual void InfoPrint() abstract; //���� �����Լ� 
};

