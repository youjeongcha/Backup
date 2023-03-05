#pragma once
#include<iostream>
#include<string>
#include<Windows.h>
#include<time.h> //clock[] 함수
//응용 프로그램이 실행한 뒤 경과된 시간을 돌려주는 함수 <time.h>
using namespace std;

#define SEC 1000
#define MAX_COUNT 5

class Computer
{
private:
	string m_sProductName;
	string m_sCurrentStatus;
	string m_sGraphicCard;
	int m_iCPU;
	string m_sMemory;
public:
	Computer(); //생성자 class명과 같아야 한다.
	void Main();
	int Menu();
	void ComStatus();
	void Function();
	void Off(int oldClock);
};