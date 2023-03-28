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
private:
	RECT m_Rect[RECTTYPE_COUNT];
public:
	virtual void Draw() abstract;
	//virtual bool BumpCheck() abstract;

};