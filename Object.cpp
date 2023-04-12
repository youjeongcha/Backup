#include "Object.h"

void Object::DrawDEbugggggggggggggg(HDC hdc)
{
	Rectangle(hdc, m_Collider_Rect[RECT_BUMP].left, m_Collider_Rect[RECT_BUMP].top, m_Collider_Rect[RECT_BUMP].right, m_Collider_Rect[RECT_BUMP].bottom);
}

RECT* Object::Get_Rect(RECT_USE useType)
{
	return &m_Collider_Rect[useType];
}