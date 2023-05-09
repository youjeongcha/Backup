#pragma once
#include "Shape.h"

class Circle : public Shape
{
public:
	float m_Radius;
	
	//지정 좌표, 크기로 생성하기 위해
	void Init(float _X, float _Y, float _R);
	void Draw(HDC hdc) override;
	void Update(float deltaTime) override;
};