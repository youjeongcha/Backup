#include <iostream>
using namespace std;

class Bumo
{
public:
	virtual void func()
	{
		cout << "Bumo함수 입니다." << endl;
	}
};

class Jasic : public Bumo
{
public:
	void func()
	{
		cout << "Jassic함수 입니다." << endl;
	}
};

void main()
{
	Jasic ob;
	Bumo* mom = &ob; //업캐스팅
	mom->func();//오버라이딩
}