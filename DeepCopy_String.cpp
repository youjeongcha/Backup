#include<iostream>
#include<string>
using namespace std;
//c���� str2 = str1 �ȵǾ��� ������. �迭�� ���� �ּҰ��� ������ �ֱ� ����
//�����ּҰ� �Ѿ�� ���Ϲ��ڰ� �ȴ�.

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