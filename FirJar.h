#pragma once
#include "FireObstacle.h"

class FirJar : public FireObstacle
{
private:
public:
	FirJar();
	~FirJar();
	//초기 세팅 SetObstacle에서는 Draw할 Rect의 xy(LT) 세팅하고 Inital에서 RB과 ColliderCheck의 Rect를 세팅한다.
	virtual void InitialSet(IMG _IMG_X, int _X, int _Y) override;
	virtual void Draw(HDC hdc) override;
	virtual void Update(float total_MoveDistance, float _Prev_MoveDistance) override;
	//virtual bool ColliderCheck() override;
};

