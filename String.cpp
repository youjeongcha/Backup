#include<iostream>
#include<string>
using namespace std; //std::를 생략시켜준다

//endl endline
void main()
{
	string str = "Hello";
	cout << "str = " << str << endl << endl;
	cout << "새로운 문자열 입력 : ";
	cin >> str;
	cout << "새로운 str 입력 : " << str << endl;
	return;
	
}