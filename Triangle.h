#pragma once
#include"Figure.h"
class Triangle : public Figure //상속
{
public:
	void Draw(); //override는 확인용. 특별한 기능을 수행하지 않음
	virtual void SetSize() override;//버츄얼하고 오버라이드 다 붙여주는 편이 좋음
	Triangle();
	~Triangle();
};

