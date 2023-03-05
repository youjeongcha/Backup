#pragma once
#include"Figure.h"
class Quadrangle : public Figure //상속
{
public:
	void Draw(); //현재 코드에 virtual이 없는 것은 이 코드 상에서 virtual이 없어도 오버라이드가 되기 때문. 그냥 오버라이드 되고 있음을 표현해주기 위해 virtual void Draw() override;로 작성하는 걸 추천
	Quadrangle();
	~Quadrangle();
};

