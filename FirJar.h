#pragma once
#include "FireObstacle.h"

class FirJar : public FireObstacle
{
private:
public:
	FirJar();
	~FirJar();
	//�ʱ� ���� SetObstacle������ Draw�� Rect�� xy(LT) �����ϰ� Inital���� RB�� ColliderCheck�� Rect�� �����Ѵ�.
	virtual void InitialSet(IMG _IMG_X, int _X, int _Y) override;
	virtual void Draw(HDC hdc) override;
	virtual void Update(float total_MoveDistance, float _Prev_MoveDistance) override;
	//virtual bool ColliderCheck() override;
};

