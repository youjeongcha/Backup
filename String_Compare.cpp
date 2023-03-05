#include<iostream>
#include<string>
using namespace std;

void main()
{
	string str;
	while (1)
	{
		system("cls");
		cout << "Very를 입력하시오 : ";
		cin >> str;
		if (str == "Very")
		{
			str += "Good";
			cout << str << endl;
			break;
		}
		cout << "잘못 입력 다시" << endl;
		system("pause");
	}
	return;
}