#pragma once
#include <Windows.h>
#include <conio.h>
#include <iostream>

inline void SetTextColor(WORD colors)
{
	// #include <Windows.h>
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, colors);
}

inline void PressAnyKeyToContinue()
{
	// white color
	SetTextColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);

	std::cout << "\n\nPress any key to continue" << std::endl;

	// #include <conio.h>
	// _kbhit : key가 눌러 졌는지 확인.
	while (!_kbhit()) {}

	return;
}