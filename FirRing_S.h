#pragma once
#include "FirRing_B.h"

class FirRing_S : public FirRing_B
{
private:
	bool m_bCashDraw; //복주머니 먹으면 사라져야 하므로
	IMG m_IMG_Cash; //복주머니
	float m_Text_X;
	float m_Text_Y;
	//Rect 세팅
	virtual void SetRect() override;
public:
	FirRing_S();
	~FirRing_S();
	//캐릭터 뒤에 그려지는 왼쪽 링
	void Draw(HDC hdc) override;
	//캐릭터 앞에 그려지는 앞쪽 링
	void Draw_OnCharacter(HDC hdc) override;
	void Update(float deltaTime, float total_MoveDistance, float _Prev_MoveDistance) override;
	void InitialSet(int _X, int _Y);

	void DrawCashScoreText(HDC hdc);

	//복주머니 해당 ring읜 현재 xy 기준으로 text 출력 좌표 설정
	void Set_Text_XY() { m_Text_X = m_Draw_X; m_Text_Y = m_Draw_Y; }
	//복주머니 먹으면 사라져야 하므로
	void Set_bCashDraw(bool _bCashDraw) { m_bCashDraw = _bCashDraw; }
};