#pragma once
#include "Shape.h"

class Box : public Shape
{
public:
	float m_Half_W, m_Half_H;

public:
	//지정 좌표, 크기로 생성하기 위해
	void Init(float _X, float _Y, float _W, float _H);
	void Draw(HDC hdc) override;
	void Update(float deltaTime) override;
};