#pragma once
#include"Figure.h"
#include<iomanip> //setpercision(n) ����Ҷ� �̿�

class circle : public Figure //���
{
private:
	float pi;
public:
	virtual void Draw();
	virtual void SetSize();
	circle();
	~circle(); //�ڽ� �Ҹ��ڿ��Դ� virtual ���̴� ���� �ʼ� �ƴ�.
};