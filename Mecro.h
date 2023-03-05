#pragma once
#include<iostream>
#include<Windows.h>
#include<conio.h>
//kbhit() - keyboard hit의 약자이며 버퍼에 값이 있으면 1을, 없으면 0을 리턴
//getch() - 값을 입력할 때까지 대기. 값이 들어오면 버퍼에 저장했다가 버퍼에서 꺼내서 리턴
#include<string>
#include<iostream>
#include<fstream> //파일 입출력에 이용
#include<time.h> //랜덤 시간에 사용
#include<list>
#include<vector>
//#include<stdlib.h>//동적할당
using namespace std; //조언::std 사용 안 하는 쪽으로. std에는 내가 사용하고자 하는 변수명과 겹치는 것들이 많다.

//////////////////////////////////////////////////////
#define col GetStdHandle(STD_OUTPUT_HANDLE) 
#define BLACK SetConsoleTextAttribute( col,0x0000 );
#define DARK_BLUE SetConsoleTextAttribute( col,0x0001 );
#define GREEN SetConsoleTextAttribute( col,0x0002 );
#define BLUE_GREEN SetConsoleTextAttribute( col,0x0003 );
#define BLOOD SetConsoleTextAttribute( col,0x0004 );
#define PUPPLE SetConsoleTextAttribute( col,0x0005 );
#define GOLD SetConsoleTextAttribute( col,0x0006 );			//색상 지정
#define ORIGINAL SetConsoleTextAttribute( col,0x0007 );
#define GRAY SetConsoleTextAttribute( col,0x0008 );
#define BLUE SetConsoleTextAttribute( col,0x0009 );
#define HIGH_GREEN SetConsoleTextAttribute( col,0x000a );
#define SKY_BLUE SetConsoleTextAttribute( col,0x000b );
#define RED SetConsoleTextAttribute( col,0x000c );
#define PLUM SetConsoleTextAttribute( col,0x000d );
#define YELLOW SetConsoleTextAttribute( col,0x000e );
//////////////////////////////////////////////////////
//#define WIDTH 30
//#define HEIGHT 30
#define WIDTH 100
#define HEIGHT 34