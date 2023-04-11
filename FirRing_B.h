#pragma once
#include "FireObstacle.h"


class FirRing_B : public FireObstacle
{
protected:
	//RECT m_Rect[RECT_COUNT]; //Object�� �̰� ���� Draw�� collider üũ�� ���
	RECT m_Rect_R_Draw; //������ �� Draw�� ���� Rect
	IMG m_IMG_NowMotion_R; //������ �̹����� ���� �ʿ�

	//Rect ����
	virtual void SetRect();
public:
	FirRing_B();
	~FirRing_B();
	
	virtual void InitialSet(int _X, int _Y) override;
	//ĳ���� �ڿ� �׷����� ���� ��
	virtual void Draw(HDC hdc);
	//ĳ���� �տ� �׷����� ���� ��
	virtual void Draw_OnCharacter(HDC hdc);
	virtual void Update(float deltaTime, float total_MoveDistance, float _Prev_MoveDistance) override;
	//Animation
	virtual void Animation(float deltaTime) override;
};