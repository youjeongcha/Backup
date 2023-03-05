#pragma once
#include<iostream>
#include<string>
using namespace std;

#define EOUL_LEN 9
#define AREA_LEN 10
#define MPH_LEN 11

//소멸자에 완성된 번호 출력

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
		//this.dPh = tmp; //사용 불가인 이유 ->
		//(*this).dPh가 맞는데 축약해서 ->
	}
	~PhoneNumber()
	{
		cout << "완성된 번호 : " << dPh;
	}
};

