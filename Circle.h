#pragma once
#include "Shape.h"

class Circle : public Shape
{
private:
	float m_Radius;
	
public:
	void Init(float _X, float _Y, float _R);
	void Draw(HDC hdc) override;
	void Update(float detaTime) override;
};

