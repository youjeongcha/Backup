#pragma once
#include "Shape.h"

class Box : public Shape
{
public:
	float m_Half_W, m_Half_H;

public:
	void Init(float _X, float _Y, float _W, float _H);
	void Draw(HDC hdc) override;
	void Update(float detaTime) override;
};