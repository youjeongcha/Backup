#pragma once
#include<iostream>
#include<string>
#include<Windows.h>
#include<time.h> //clock[] �Լ�
//���� ���α׷��� ������ �� ����� �ð��� �����ִ� �Լ� <time.h>
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
	Computer(); //������ class��� ���ƾ� �Ѵ�.
	void Main();
	int Menu();
	void ComStatus();
	void Function();
	void Off(int oldClock);
};