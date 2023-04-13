#include "Object.h"

//void Object::DrawDEbugggggggggggggg(HDC hdc)
//{
//	Rectangle(hdc, m_Collider_Rect[RECT_BUMP].left, m_Collider_Rect[RECT_BUMP].top, m_Collider_Rect[RECT_BUMP].right, m_Collider_Rect[RECT_BUMP].bottom);
//}

bool Object::ColliderCheck(RECT* characterRect, RECT_USE useType)
{
	RECT lprcDst;


	if ((m_bActiveCheck == true) && (useType == RECT_SCORE))
	{
		if (IntersectRect(&lprcDst, &m_Collider_Rect[RECT_SCORE], characterRect))
		{
			m_bActiveCheck = false;
			return true;
		}
	}
	if (useType == RECT_BUMP)
	{
		if (IntersectRect(&lprcDst, &m_Collider_Rect[RECT_BUMP], characterRect))
			return true;
	}

	return false;
}

//RECT* Object::Get_Rect(RECT_USE useType)
//{
//	return &m_Collider_Rect[useType];
//}