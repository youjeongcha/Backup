#include<iostream>
#include<functional>
using namespace std;
//���ٽ� (�̸��� ���� �Լ�. �͸��� �Լ�)
//��ȸ�� �Լ� . ��Ȱ���� �Ұ�

void Subfunc(int x, int y)
{
	cout << x << "-" << y << "=" << x - y << endl;
}
void func2(function<void(int, int)> p)
{
	p(15, 10);
}
void main()
{
	func2([](int x, int y) {//[]gkrh dlswk gkaus 
		//�̶��� ��� ���� ������ �Լ�
		cout << x << "+" << y << "=" << x + y << endl;
		});
	func2(Subfunc);
	return;
}