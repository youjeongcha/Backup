#include <iostream>
using namespace std;

void counter()
{
	static int count = 0; //static�� ������ ȣ���Ҷ����� �� 1�� ���
	//static�� ���α׷��� ����� �� ��������� //���α׷��� ����������� ����
	//������ �ٸ� ���������� �Ͽ����� ����
	cout << ++count << endl;
}

void main()
{
	for (int i = 0; i < 10; i++)
		counter();
	//count = 20; //������ �ٸ� ���������� �Ͽ����� ���� <<<<
}