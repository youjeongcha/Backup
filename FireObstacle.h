#pragma once
#include "Object.h"
#include "BitMapManager.h"

#define ANI_SPEED_FIRE 0.1f
#define MOVE_SPEED_FRIE 100

//��ӿ�
//FirJar�� FirRing_B�� �θ�. 

class FireObstacle : public Object
{
protected:
	float m_MoveTime; //�̵� �ð�
public:
	//�ʱ� ����
	virtual void InitialSet(int _X, int _Y) abstract;
	virtual void Draw(HDC hdc) abstract;
	virtual void Update(float deltaTime, float thisTurn_MoveDistance, float _Prev_MoveDistance) abstract;
	//Rect ����
	virtual void SetRect() abstract;
	//Animation
	virtual void Animation(float deltaTime) abstract;

	//xy��ǥ �ʱ� ����
	//void SetObstacle(IMG _IMG_X, int _X, int _Y)
	//{
	//	m_IMG_NowMotion = _IMG_X;
	//	m_Rect[RECT_BITMAP].left = _X;
	//	m_Rect[RECT_BITMAP].top = _Y;
	//}
	//virtual bool ColliderCheck() override;
};