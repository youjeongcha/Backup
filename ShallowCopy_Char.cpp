#include<iostream>
using namespace std;
//얕은 복사 - 주소 - 주소가 가리키는 곳이 변하면 다 변함
//깊은 복사 - 실제 값 - 주소가 가리키는 곳이 변해도 남아있다

void main()
{
	char str[6] = "Hello";
	char* tmp = str;
	cout << "str = " << str << endl;
	cout << "tmp = " << tmp << endl;
	strcpy(str, "Bye");
	cout << "str = " << str << endl;
	cout << "tmp = " << tmp << endl;
}