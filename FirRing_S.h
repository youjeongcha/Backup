#pragma once
#include "FirRing_B.h"

class FirRing_S : public FirRing_B
{
private:
	bool m_bCashDraw; //���ָӴ� ������ ������� �ϹǷ�
	IMG m_IMG_Cash; //���ָӴ�
	float m_Text_X;
	float m_Text_Y;
	//Rect ����
	virtual void SetRect() override;
public:
	FirRing_S();
	~FirRing_S();
	//ĳ���� �ڿ� �׷����� ���� ��
	void Draw(HDC hdc) override;
	//ĳ���� �տ� �׷����� ���� ��
	void Draw_OnCharacter(HDC hdc) override;
	void Update(float deltaTime, float total_MoveDistance, float _Prev_MoveDistance) override;
	void InitialSet(int _X, int _Y);

	void DrawCashScoreText(HDC hdc);

	//���ָӴ� �ش� ring�� ���� xy �������� text ��� ��ǥ ����
	void Set_Text_XY() { m_Text_X = m_Draw_X; m_Text_Y = m_Draw_Y; }
	//���ָӴ� ������ ������� �ϹǷ�
	void Set_bCashDraw(bool _bCashDraw) { m_bCashDraw = _bCashDraw; }
};