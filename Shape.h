#pragma once
#include "framework.h"
#include "Math.h"

class Shape
{
public:
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

//public:
	virtual void Draw(HDC hdc) abstract;
	virtual void Update(float detaTime) abstract;
	void Set_GravityVelocity(Vector2 g) { m_Velocity += g; }
};