#pragma once
#include "FireObstacle.h"

class FirRing_B : public FireObstacle
{
protected:
	//RECT m_Rect[RECT_COUNT]; //Object의 이게 왼쪽 Draw와 collider 체크를 담당
	RECT m_Rect_R_Draw; //오른쪽 링 Draw를 위한 Rect
public:
	virtual void InitialSet(IMG _IMG_X, int _X, int _Y) override;
	virtual void Draw(HDC hdc) override;
	virtual void Update(float thisTurn_MoveDistance, float _Prev_MoveDistance) override;
	//virtual bool ColliderCheck() override;
};