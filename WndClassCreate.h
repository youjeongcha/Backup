#pragma once
#include<Windows.h>

class WndClassCreate
{
private:

public:
	WNDCLASS WndClass;

	WndClassCreate(HINSTANCE hInstance, LPCTSTR lpszClass, int backgroundColor);
	~WndClassCreate();
};

