#pragma once
#include "FireObstacle.h"

class FirRing_B : public FireObstacle
{
protected:
	//RECT m_Rect[RECT_COUNT]; //Object�� �̰� ���� Draw�� collider üũ�� ���
	RECT m_Rect_R_Draw; //������ �� Draw�� ���� Rect
public:
	virtual void InitialSet(IMG _IMG_X, int _X, int _Y) override;
	virtual void Draw(HDC hdc) override;
	virtual void Update(float thisTurn_MoveDistance, float _Prev_MoveDistance) override;
	//virtual bool ColliderCheck() override;
};