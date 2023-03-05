#include<iostream>
#include<string>
using namespace std;
//c에서 str2 = str1 안되었던 이유가. 배열은 시작 주소값을 가지고 있기 때문
//시작주소가 넘어가서 단일문자가 된다.

void main()
{
	string str1 = "Hello";
	string str2;
	str2 = str1;
	cout << "str1 = " << str1 << endl;
	cout << "str2 = " << str2 << endl;
	str1 = "Bye";
	cout << "str1 = " << str1 << endl;
	cout << "str2 = " << str2 << endl;
}