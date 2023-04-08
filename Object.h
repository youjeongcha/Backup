#pragma once
#include "framework.h"
#include "BitMapManager.h"

enum RECT_USE
{//충돌, 점수 체크 RECT 구분
	RECT_BUMP,
	RECT_SCORE,
	RECT_COUNT,
};

class Object
{
protected:
	float m_Draw_X;
	float m_Draw_Y;
	float m_Time;
	RECT m_Collider_Rect[RECT_COUNT]; //FirRing의 출력 rect와 collider체크의 rect가 다른 점 고려
	IMG m_IMG_NowMotion; //화면에 현재 띄울 이미지
public:
	//초기 세팅
	virtual void InitialSet(IMG _IMG_X, int _X, int _Y) abstract;
	virtual void Draw(HDC hdc) abstract;
	virtual void Update(float deltaTime, float thisTurn_MoveDistance, float _Prev_MoveDistance) abstract;
	//Rect 세팅
	virtual void SetRect() abstract;

	RECT* Get_Rect(RECT_USE useType);
};