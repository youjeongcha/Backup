#pragma once
#include <iostream>
#include <string>
#include <vector>
#include<Windows.h>
#include <conio.h> //getch()

static std::string currentDateTime() //���� �ð� �޴� �Լ�.
{
	time_t now = time(0); //���� �ð��� time_t Ÿ������ ����.
	struct tm tstruct;
	tstruct = *localtime(&now);
	char buf[80];
	strftime(buf, sizeof(buf), "%Y-%m-%d.%X", &tstruct); // YYYY-MM-DD.HH:mm:ss

	return buf;
}