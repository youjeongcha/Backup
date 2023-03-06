#ifndef CONSOLE_UTILS_H
#define CONSOLE_UTILS_H

#include <windows.h>
#include <conio.h>
#include <iostream>

//문자의 색을 원하는 색으로 바꾼다.
inline void SetTextColor(WORD colors)
{
	HANDLE hConsole=GetStdHandle(STD_OUTPUT_HANDLE);

	SetConsoleTextAttribute(hConsole, colors);
}

inline void PressAnyKeyToContinue()
{
	//문자의 색을 흰색으로 바꾼다.
	SetTextColor(FOREGROUND_BLUE| FOREGROUND_RED | FOREGROUND_GREEN);

	std::cout << "\n\nPress any key to continue" << std::endl; 

	while (!_kbhit()){}

	return;
}

#endif