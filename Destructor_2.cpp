#include<iostream>
#include<string>
using namespace std;
//�Ҹ���

class str
{
private:
	char* name;
public:
	str()
	{
		string str;
		cout << "�̸� �Է� : ";
		cin >> str;
		name = new char[str.length() + 1]; //new
		strcpy(name, str.c_str()); //c_Str
	}
	~str()
	{
		cout << name << "�� ���� �Ҵ��� �����մϴ�.\n";
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