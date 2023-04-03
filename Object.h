#pragma once
#include "framework.h"

enum RECTTYPE
{
	RECTTYPE_BITMAP,
	RECTTYPE_BUMP,
	RECTTYPE_COUNT,
};

class Object
{
protected:
	RECT m_Rect[RECTTYPE_COUNT];
public:
	virtual void Draw(HDC hdc) abstract;
	virtual void Update(float thisTurn_MoveDistance) abstract;
	//virtual bool BumpCheck() abstract;

};