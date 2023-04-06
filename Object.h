#pragma once
#include "framework.h"
#include "BitMapManager.h"

enum RECT_USE
{//FirRing의 출력 rect와 collider체크의 rect가 다른 점 고려
	RECT_BITMAP,
	RECT_COLLIDER,
	RECT_COUNT,
};

class Object
{
protected:
	float m_Draw_X;
	float m_Draw_Y;
	RECT m_Collider_Rect;// [RECT_COUNT] ; //FirRing의 출력 rect와 collider체크의 rect가 다른 점 고려
	IMG m_IMG_NowMotion; //화면에 현재 띄울 이미지
public:
	//초기 세팅
	virtual void InitialSet(IMG _IMG_X, int _X, int _Y)abstract;
	virtual void Draw(HDC hdc) abstract;
	virtual void Update(float thisTurn_MoveDistance, float _Prev_MoveDistance) abstract;
	//virtual bool ColliderCheck() abstract;

	RECT* Get_Rect();

};