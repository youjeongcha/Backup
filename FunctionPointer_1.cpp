#include <iostream>
#include <functional> //���̺귯��. c++ stl �Լ� ���� ��ɵ��� ����ִ�.
using namespace std;
//�Լ� �������� ���� : ��Ȳ�� ���� �󸶵��� �޸��� �� �ִ�.

void func1()
{
	cout << "�Լ� ������1 ȣ��" << endl;
}

void func2()
{
	cout << "�Լ� ������2 ȣ��" << endl;
}

void main()
{
	//list<int>
	function<void()> p; // <��ȯ�ڷ���(�Ű�����)> 

	p = func1;// <��ȯ�ڷ���(�Ű�����)>  ����
	p();

	//������ ����. ����� �����͸� �󸶵��� �ٲ� �� �ִ�.
	p = func2;
	p();

	return;
}