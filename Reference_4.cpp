#include <iostream>
using namespace std;

void func(int& ref)
{//ref�� a�� �����ϰ� �ִ� ��.
	//�ѹ� �ʱ� ������ �����ϸ� ���������� ������ ����Ų��.
	//�����ʹ� �����ϴ� ���� ������ �����ϴ�. (�ڷᱸ�� ���� �������ϰ� ����)
	cout << "ref = " << ref << endl << endl;
	int b = 20;
	ref = b; //b�� ���빰�� a�޸𸮿� �����ϴ� ��
	b = 25;
	cout << "b = " << b << endl;
	cout << "ref = " << ref << endl;
}

void main()
{
	int a = 10;
	cout << "a = " << a << endl;
	func(a);
	cout << "a = " << a << endl;
}