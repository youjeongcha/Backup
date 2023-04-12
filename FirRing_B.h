#pragma once
#include "FireObstacle.h"


class FirRing_B : public FireObstacle
{
protected:
	//bool m_UsingCheck; //게임 한판에 70M에 한번 나오고 끝
	//RECT m_Rect[RECT_COUNT]; //Object의 이게 왼쪽 Draw와 collider 체크를 담당
	//RECT m_Rect_R_Draw; //오른쪽 링 Draw를 위한 Rect
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

	//골대가 특정위치에 도착하면 링 생성 중단을 위해
	//void Set_UsingCheck(bool _UsingCheck) { m_UsingCheck = _UsingCheck; };
	//링이 작동해도 되는지를 체크
	//bool Get_UsingCheck() { return m_UsingCheck; };
};