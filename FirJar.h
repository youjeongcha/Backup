#pragma once
#include "FireObstacle.h"




class FirJar : public FireObstacle
{
private:

	//Rect 세팅
	virtual void SetRect() override;
public:
	FirJar();
	~FirJar();
	//초기 세팅 SetObstacle에서는 Draw할 Rect의 xy(LT) 세팅하고 Inital에서 RB과 ColliderCheck의 Rect를 세팅한다.
	//virtual void InitialSet(IMG _IMG, int _X, int _Y) override; //이글거림 위해 IMG를 받아서 사용
	virtual void InitialSet(int _X, int _Y) override; //이글거림 위해 IMG를 받아서 사용
	virtual void Draw(HDC hdc) override;
	virtual void Update(float deltaTime, float total_MoveDistance, float _Prev_MoveDistance) override;
	//Animation
	virtual void Animation(float deltaTime) override;


	//virtual bool ColliderCheck() override;
};

