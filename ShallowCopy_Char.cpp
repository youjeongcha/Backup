#include<iostream>
using namespace std;
//���� ���� - �ּ� - �ּҰ� ����Ű�� ���� ���ϸ� �� ����
//���� ���� - ���� �� - �ּҰ� ����Ű�� ���� ���ص� �����ִ�

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