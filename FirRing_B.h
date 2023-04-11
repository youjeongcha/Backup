#pragma once
#include "FireObstacle.h"


class FirRing_B : public FireObstacle
{
protected:
	//RECT m_Rect[RECT_COUNT]; //Object의 이게 왼쪽 Draw와 collider 체크를 담당
	RECT m_Rect_R_Draw; //오른쪽 링 Draw를 위한 Rect
	IMG m_IMG_NowMotion_R; //오른쪽 이미지를 위해 필요

	//Rect 세팅
	virtual void SetRect();
public:
	FirRing_B();
	~FirRing_B();
	
	virtual void InitialSet(int _X, int _Y) override;
	//캐릭터 뒤에 그려지는 왼쪽 링
	virtual void Draw(HDC hdc);
	//캐릭터 앞에 그려지는 앞쪽 링
	virtual void Draw_OnCharacter(HDC hdc);
	virtual void Update(float deltaTime, float total_MoveDistance, float _Prev_MoveDistance) override;
	//Animation
	virtual void Animation(float deltaTime) override;
};