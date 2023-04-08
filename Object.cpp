#include "Object.h"

RECT* Object::Get_Rect(RECT_USE useType)
{
	return &m_Collider_Rect[useType];
}