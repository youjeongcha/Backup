#pragma once
#include<iostream>
using namespace std;

class Figure
{
protected:
	int x;
	int y;
public:
	Figure();
	//�������̵� �ǰ� ������ ǥ�����ֱ� ���� virtual void Draw() override;�� �ۼ��ϴ� �� ��õ
	virtual void Draw();
	virtual void SetSize();
	virtual ~Figure(); //�θ� �Ҹ��ڿ��� �����Լ� virtual�� �ٿ����Ѵ�. �ڽĿ��Դ� �ʼ� �ƴ�
};

