#pragma once
#include "framework.h"

enum RECTTYPE
{//FirRing�� ��� rect�� colliderüũ�� rect�� �ٸ� �� ���
	RECTTYPE_BITMAP,
	RECTTYPE_BUMP,
	RECTTYPE_COUNT,
};

class Object
{
protected:
	RECT m_Rect[RECTTYPE_COUNT]; //FirRing�� ��� rect�� colliderüũ�� rect�� �ٸ� �� ���
public:
	virtual void Draw(HDC hdc) abstract;
	virtual void Update(float thisTurn_MoveDistance, float _Prev_MoveDistance) abstract;
	//virtual bool ColliderCheck() abstract;
	RECT* Get_Rect();

};