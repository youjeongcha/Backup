#pragma once
#include "framework.h"

enum RECTTYPE
{//FirRing의 출력 rect와 collider체크의 rect가 다른 점 고려
	RECTTYPE_BITMAP,
	RECTTYPE_BUMP,
	RECTTYPE_COUNT,
};

class Object
{
protected:
	RECT m_Rect[RECTTYPE_COUNT]; //FirRing의 출력 rect와 collider체크의 rect가 다른 점 고려
public:
	virtual void Draw(HDC hdc) abstract;
	virtual void Update(float thisTurn_MoveDistance, float _Prev_MoveDistance) abstract;
	//virtual bool ColliderCheck() abstract;
	RECT* Get_Rect();

};