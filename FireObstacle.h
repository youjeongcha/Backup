#pragma once
#include "Object.h"
#include "BitMapManager.h"

#define ANI_SPEED_FIRE 0.1f
#define MOVE_SPEED_FRIERING_B 100
#define MOVE_SPEED_FRIERING_S 150

//상속용
//FirJar과 FirRing_B의 부모. 

class FireObstacle : public Object
{
protected:
	float m_MoveTime; //이동 시간
	int m_AllotScore; //통과시 해당되는 점수
public:
	//초기 세팅
	virtual void InitialSet(int _X, int _Y) abstract;
	virtual void Draw(HDC hdc) abstract;
	virtual void Update(float deltaTime, float thisTurn_MoveDistance, float _Prev_MoveDistance) abstract;
	//Rect 세팅
	virtual void SetRect() abstract;
	//Animation
	virtual void Animation(float deltaTime) abstract;

	int Get_AllotScore() { return m_AllotScore; }

	//xy좌표 초기 세팅
	//void SetObstacle(IMG _IMG_X, int _X, int _Y)
	//{
	//	m_IMG_NowMotion = _IMG_X;
	//	m_Rect[RECT_BITMAP].left = _X;
	//	m_Rect[RECT_BITMAP].top = _Y;
	//}
	//virtual bool ColliderCheck() override;
};