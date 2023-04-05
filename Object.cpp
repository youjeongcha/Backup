#include "Object.h"

RECT* Object::Get_Rect()
{
	return &m_Rect[RECTTYPE_BUMP];
}
