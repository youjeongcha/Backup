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
	//오버라이드 되고 있음을 표현해주기 위해 virtual void Draw() override;로 작성하는 걸 추천
	virtual void Draw();
	virtual void SetSize();
	virtual ~Figure(); //부모 소멸자에는 가상함수 virtual을 붙여야한다. 자식에게는 필수 아님
};

