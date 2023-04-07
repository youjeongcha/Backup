#pragma once
#include "FireObstacle.h"

class FirRing_B : public FireObstacle
{
protected:
	//RECT m_Rect[RECT_COUNT]; //Object�� �̰� ���� Draw�� collider üũ�� ���
	RECT m_Rect_R_Draw; //������ �� Draw�� ���� Rect

	//Rect ����
	virtual void SetRect() override;
public:
	virtual void InitialSet(IMG _IMG_X, int _X, int _Y) override;
	virtual void Draw(HDC hdc) override;
	virtual void Update(float deltaTime, float thisTurn_MoveDistance, float _Prev_MoveDistance) override;
	//Animation
	virtual void Animation(float deltaTime) override;


	//virtual bool ColliderCheck() override;
};