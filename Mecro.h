#pragma once

#include<iostream>
#include<string>
#include<conio.h>
#include<Windows.h>
using namespace std;

//rkfh 
enum class FIVE_IN_A_ROW_BOARD_SIZE
{
	WIDTH = 20,
	HEIGHT = 20,
}; 

enum class OTHELLO_BOARD_SIZE
{
	WIDTH = 8,
	HEIGHT = 8,
};

enum class KEY
{
	LEFT = 'a',
	RIGHT = 'd',
	UP = 'w',
	DOWN = 's',
	ESC = 27,
	DROP = 13,
	UNDO = 'n',
	OPTION = 'p',
	WIN = 1,
	PASS
};


enum class GAMETYPE
{
	FIVE_IN_A_ROW,
	OTHELLO
};