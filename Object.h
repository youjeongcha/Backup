#pragma once
#include "framework.h"
#include "BitMapManager.h"

enum RECT_USE
{//FirRing�� ��� rect�� colliderüũ�� rect�� �ٸ� �� ���
	RECT_BITMAP,
	RECT_COLLIDER,
	RECT_COUNT,
};

class Object
{
protected:
	float m_Draw_X;
	float m_Draw_Y;
	RECT m_Collider_Rect;// [RECT_COUNT] ; //FirRing�� ��� rect�� colliderüũ�� rect�� �ٸ� �� ���
	IMG m_IMG_NowMotion; //ȭ�鿡 ���� ��� �̹���
public:
	//�ʱ� ����
	virtual void InitialSet(IMG _IMG_X, int _X, int _Y)abstract;
	virtual void Draw(HDC hdc) abstract;
	virtual void Update(float thisTurn_MoveDistance, float _Prev_MoveDistance) abstract;
	//virtual bool ColliderCheck() abstract;

	RECT* Get_Rect();

};