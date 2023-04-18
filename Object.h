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
	bool m_bActiveCheck; //화면상에서 작동 가능 여부 확인 위해
	float m_Draw_X;
	float m_Draw_Y;
	float m_AnimationTime;
	RECT m_Collider_Rect[RECT_COUNT]; //FirRing의 출력 rect와 collider체크의 rect가 다른 점 고려
	IMG m_IMG_NowMotion; //화면에 현재 띄울 이미지
public:
	//초기 세팅
	virtual void InitialSet(int _X, int _Y) abstract;
	virtual void Draw(HDC hdc) abstract;
	virtual void Update(float deltaTime, float thisTurn_MoveDistance, float _Prev_MoveDistance) abstract;
	//Rect 세팅
	virtual void SetRect() abstract;
	bool ColliderCheck(RECT* characterRect, RECT_USE useType);

	//Goal이 그려짐+이동+충돌체크가 가능한 상태
	void Set_ActiveCheck(bool _ActiveCheck) { m_bActiveCheck = _ActiveCheck; }
	bool Get_ActiveCheck() { return m_bActiveCheck; }

	float Get_XXXXXXXXXXXXXXXXXXXXXX() { return m_Draw_X; }

	void Set_X(float _X) { m_Draw_X = _X; }
	
	//디버깅용 RECT 그리기
	//void DrawDEbugggggggggggggg(HDC hdc);

	//RECT* Get_Rect(RECT_USE useType);
};