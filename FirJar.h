#pragma once
#include "FireObstacle.h"

#define ANI_FIREJAR 0.2

enum FIREJAR_RECT
{
	FIREJAR_RECT_GAP = 5,
};


class FirJar : public FireObstacle
{
private:

	//Rect ����
	virtual void SetRect() override;
public:
	FirJar();
	~FirJar();
	//�ʱ� ���� SetObstacle������ Draw�� Rect�� xy(LT) �����ϰ� Inital���� RB�� ColliderCheck�� Rect�� �����Ѵ�.
	virtual void InitialSet(IMG _IMG_X, int _X, int _Y) override;
	virtual void Draw(HDC hdc) override;
	virtual void Update(float deltaTime, float total_MoveDistance, float _Prev_MoveDistance) override;
	//Animation
	virtual void Animation(float deltaTime) override;


	//virtual bool ColliderCheck() override;
};

