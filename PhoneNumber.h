#pragma once
#include<iostream>
#include<string>
using namespace std;

#define EOUL_LEN 9
#define AREA_LEN 10
#define MPH_LEN 11

//�Ҹ��ڿ� �ϼ��� ��ȣ ���

class PhoneNumber
{
private:
	string ph;
	string dPh;
public:
	PhoneNumber()
	{

	}
	void Main();
	void AddDash(int first, int second);
	void setDPh(string tmp)
	{
		dPh = tmp;
		//this.dPh = tmp; //��� �Ұ��� ���� ->
		//(*this).dPh�� �´µ� ����ؼ� ->
	}
	~PhoneNumber()
	{
		cout << "�ϼ��� ��ȣ : " << dPh;
	}
};

