#pragma once
#include "framework.h"
#include "BitMapManager.h"

enum RECT_USE
{//�浹, ���� üũ RECT ����
	RECT_BUMP,
	RECT_SCORE,
	RECT_COUNT,
};

class Object
{
protected:
	bool m_bActiveCheck; //ȭ��󿡼� �۵� ���� ���� Ȯ�� ����
	float m_Draw_X;
	float m_Draw_Y;
	float m_AnimationTime;
	RECT m_Collider_Rect[RECT_COUNT]; //FirRing�� ��� rect�� colliderüũ�� rect�� �ٸ� �� ���
	IMG m_IMG_NowMotion; //ȭ�鿡 ���� ��� �̹���
public:
	//�ʱ� ����
	virtual void InitialSet(int _X, int _Y) abstract;
	virtual void Draw(HDC hdc) abstract;
	virtual void Update(float deltaTime, float thisTurn_MoveDistance, float _Prev_MoveDistance) abstract;
	//Rect ����
	virtual void SetRect() abstract;
	bool ColliderCheck(RECT* characterRect, RECT_USE useType);

	//Goal�� �׷���+�̵�+�浹üũ�� ������ ����
	void Set_ActiveCheck(bool _ActiveCheck) { m_bActiveCheck = _ActiveCheck; }
	bool Get_ActiveCheck() { return m_bActiveCheck; }

	float Get_XXXXXXXXXXXXXXXXXXXXXX() { return m_Draw_X; }

	void Set_X(float _X) { m_Draw_X = _X; }
	
	//������ RECT �׸���
	//void DrawDEbugggggggggggggg(HDC hdc);

	//RECT* Get_Rect(RECT_USE useType);
};