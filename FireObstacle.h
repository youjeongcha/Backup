#pragma once
#include "Object.h"
#include "BitMapManager.h"

//��ӿ�
//FirJar�� FirRing_B�� �θ�. 

class FireObstacle : public Object
{
protected:

public:
	//�ʱ� ����
	virtual void InitialSet(IMG _IMG_X, int _X, int _Y) abstract;
	virtual void Draw(HDC hdc) abstract;
	virtual void Update(float thisTurn_MoveDistance, float _Prev_MoveDistance) abstract;

	//xy��ǥ �ʱ� ����
	//void SetObstacle(IMG _IMG_X, int _X, int _Y)
	//{
	//	m_IMG_NowMotion = _IMG_X;
	//	m_Rect[RECT_BITMAP].left = _X;
	//	m_Rect[RECT_BITMAP].top = _Y;
	//}
	//virtual bool ColliderCheck() override;
};