#pragma once
#include"Figure.h"
class Triangle : public Figure //���
{
public:
	void Draw(); //override�� Ȯ�ο�. Ư���� ����� �������� ����
	virtual void SetSize() override;//������ϰ� �������̵� �� �ٿ��ִ� ���� ����
	Triangle();
	~Triangle();
};

