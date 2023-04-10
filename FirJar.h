#pragma once
#include "FireObstacle.h"




class FirJar : public FireObstacle
{
private:

	//Rect ����
	virtual void SetRect() override;
public:
	FirJar();
	~FirJar();
	//�ʱ� ���� SetObstacle������ Draw�� Rect�� xy(LT) �����ϰ� Inital���� RB�� ColliderCheck�� Rect�� �����Ѵ�.
	//virtual void InitialSet(IMG _IMG, int _X, int _Y) override; //�̱۰Ÿ� ���� IMG�� �޾Ƽ� ���
	virtual void InitialSet(int _X, int _Y) override; //�̱۰Ÿ� ���� IMG�� �޾Ƽ� ���
	virtual void Draw(HDC hdc) override;
	virtual void Update(float deltaTime, float total_MoveDistance, float _Prev_MoveDistance) override;
	//Animation
	virtual void Animation(float deltaTime) override;


	//virtual bool ColliderCheck() override;
};

