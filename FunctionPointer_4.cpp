#include<iostream>
#include<functional>
using namespace std;
//Bind(Ư�� ���ڸ� ����)
//default�Ű� ������ ����

void Addfunc1(int x1, int x2, int x3, int x4)
{
	cout << x1 << "+" << x2 << "=" << x3 + x4 << endl;
}
void Addfunc(int x, int y)
{
	cout << x << "+" << y << "=" << x + y << endl;
}
void Subfunc(int x, int y)
{
	cout << x << "-" << y << "=" << x - y << endl;
}
void func2(function<void(int)> p)//�����ϳ�¥��
{
	p(20);
}
void main()
{
	//�ϳ� ���� placeholders::_1
	func2(bind(Addfunc, 10, placeholders::_1));//�Լ���, ���� ���ڰ�(ù��° ���� x�� ����), ���� �Ƚ�Ų ��. intp�� _1�� �ǹ�
	func2(bind(Subfunc, 10, placeholders::_1));

	func2(bind(Addfunc1, 1, 2, placeholders::_1, 3)); //x3�� 20���� ����
	//���� ��ų �� placeholders::_3���� 1 ~ placeholders::_3���ε� ��� ����
	return;
}