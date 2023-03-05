#include<iostream>
#include<string>
using namespace std;
//소멸자

class str
{
private:
	char* name;
public:
	str()
	{
		string str;
		cout << "이름 입력 : ";
		cin >> str;
		name = new char[str.length() + 1]; //new
		strcpy(name, str.c_str()); //c_Str
	}
	~str()
	{
		cout << name << "의 동적 할당을 해제합니다.\n";
		delete[] name;
	}
	void Disp()
	{
		cout << "name = " << name << endl;
	}
};
void main()
{
	str st1, st2;
	st1.Disp();
	st2.Disp();
}