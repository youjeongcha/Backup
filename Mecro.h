#pragma once

#include<iostream>
#include<string>
#include<conio.h>
#include<Windows.h>
using namespace std;

#define WIDTH 20
#define HEIGHT 20

enum class KEY
{
	LEFT = 'a',
	RIGHT = 'd',
	UP = 'w',
	DOWN = 's',
	ESC = 27,
	DROP = 13, //
	UNDO = 'n',
	OPTION = 'p', //
	WIN = 1 //
};


enum class GAMETYPE
{
	FIVE_IN_A_ROW,
	OTHELLO
};