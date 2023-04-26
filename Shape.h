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

	//XY��ǥ�� ��Ÿ ������ �������̵�
	Vector2 m_Position;
	//����
	//float m_Volume;
	//����
	float m_Mass; //TODO::�� �ڽ� Ŭ������ init���� ����
	float m_InvMass; //TODO::�� �ڽ� Ŭ������ init���� ����
	//�ӵ�
	Vector2 m_Velocity; //TODO::�� �ڽ� Ŭ������ init���� ����
	
	//�߷� ���ӵ�
	//Vector2 m_GravityVelocity; //TODO::�� �ڽ� Ŭ������ init���� ����
	bool m_isStatic = false;

//public:
	virtual void Draw(HDC hdc) abstract;
	virtual void Update(float detaTime) abstract;
	void Set_GravityVelocity(Vector2 g) { if (!m_isStatic) m_Velocity += g; }
	void AddForce(Vector2 accel) { if (!m_isStatic) m_Velocity += accel; }
	void Set_Static() { m_isStatic = true; }
};