#pragma once
#include"Figure.h"
#include<iomanip> //setpercision(n) 사용할때 이용

class circle : public Figure //상속
{
private:
	float pi;
public:
	virtual void Draw();
	virtual void SetSize();
	circle();
	~circle(); //자식 소멸자에게는 virtual 붙이는 것이 필수 아님.
};