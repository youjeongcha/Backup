#include <iostream>
using namespace std;
//class ���� static ����

class A//class�� ����� ���� ������ ���� �� �����. �׷��� int A::count = 0; �ܺ� ���� �ʱ�ȭ �ʿ�
	   //Ŭ������ ���赵
{
public :
	static int count;//���������̴� ���� ��������� Ǯ� �������
	//������ �ϳ��ε� A�� �������  a1,a2,a3���� �������� ���
	A()
	{
		cout << ++count << endl;
	}
};
int A::count = 0; //��ü. Ŭ���� ������ ������ ����ϱ� ���ؼ��� �ܺο��� ����� �ʱ�ȭ �ʿ�
void main()
{
	A a1; //10�� > �׷��� �ٸ� ��ü�ε��� ���� ��� ���� 
	A a2;
	A a3;
	A::count = 10; //public�̶� �̷��� ����
	A a4;
	A a5;
}