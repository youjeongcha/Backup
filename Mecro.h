#pragma once
#include<iostream>
#include<Windows.h>
#include<conio.h>
//kbhit() - keyboard hit�� �����̸� ���ۿ� ���� ������ 1��, ������ 0�� ����
//getch() - ���� �Է��� ������ ���. ���� ������ ���ۿ� �����ߴٰ� ���ۿ��� ������ ����
#include<string>
#include<iostream>
#include<fstream> //���� ����¿� �̿�
#include<time.h> //���� �ð��� ���
#include<list>
#include<vector>
//#include<stdlib.h>//�����Ҵ�
using namespace std; //����::std ��� �� �ϴ� ������. std���� ���� ����ϰ��� �ϴ� ������� ��ġ�� �͵��� ����.

//////////////////////////////////////////////////////
#define col GetStdHandle(STD_OUTPUT_HANDLE) 
#define BLACK SetConsoleTextAttribute( col,0x0000 );
#define DARK_BLUE SetConsoleTextAttribute( col,0x0001 );
#define GREEN SetConsoleTextAttribute( col,0x0002 );
#define BLUE_GREEN SetConsoleTextAttribute( col,0x0003 );
#define BLOOD SetConsoleTextAttribute( col,0x0004 );
#define PUPPLE SetConsoleTextAttribute( col,0x0005 );
#define GOLD SetConsoleTextAttribute( col,0x0006 );			//���� ����
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