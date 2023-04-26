#pragma once
#include "framework.h"
#include "Math.h"

enum SHAPE
{
	SHAPE_CIRCLE,
	SHAPE_BOX,

	SHAPE_PLUS_SIZE = 30,
	SHAPE_MIN_SIZE = 30,
};

class Shape
{
protected:
public:
	SHAPE m_ShapeType;

	//XY좌표와 기타 연산자 오버라이딩
	Vector2 m_Position;
	//부피
	//float m_Volume;
	//질량
	float m_Mass; //TODO::각 자식 클래스의 init에서 설정
	float m_InvMass; //TODO::각 자식 클래스의 init에서 설정
	//속도
	Vector2 m_Velocity; //TODO::각 자식 클래스의 init에서 설정
	
	//중력 가속도
	//Vector2 m_GravityVelocity; //TODO::각 자식 클래스의 init에서 설정
	bool m_isStatic = false;

//public:
	virtual void Draw(HDC hdc) abstract;
	virtual void Update(float detaTime) abstract;
	void Set_GravityVelocity(Vector2 g) { if (!m_isStatic) m_Velocity += g; }
	void AddForce(Vector2 accel) { if (!m_isStatic) m_Velocity += accel; }
	void Set_Static() { m_isStatic = true; }
};