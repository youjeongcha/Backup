#pragma once
#include"Figure.h"
class Quadrangle : public Figure //���
{
public:
	void Draw(); //���� �ڵ忡 virtual�� ���� ���� �� �ڵ� �󿡼� virtual�� ��� �������̵尡 �Ǳ� ����. �׳� �������̵� �ǰ� ������ ǥ�����ֱ� ���� virtual void Draw() override;�� �ۼ��ϴ� �� ��õ
	Quadrangle();
	~Quadrangle();
};

