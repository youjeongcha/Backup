#include<iostream>
using namespace std;

class A
{
private:
	int Num; 
public :
	static int count;//����� .h�� �ۼ�
	A()
	{
		Num = 10;
		cout << ++count << endl;
	}
	static void Print()
		//�Ϲ������δ� class �ȿ� ���ϴ� ��� �Լ���� �Ѵ�.
	
	{
		cout << "count : " << count << endl;//���� ȣ���� ��ü�� �Ҽ�
		//count�� static���� ���� ������ �������� ����ؼ� a1,a2,a3 ��� �������� ��ü���� ���� ��� �Ұ�.
		//static�Լ������� static ������ ��밡��
	}
};
int A::count = 0;//.cpp�� �ۼ�
void main()
{
	A a1;
	A a2;
	A::count = 10;
	A a3;
	A a4;
	A a5;
	a5.Print();
	A::Print();//�����̱⿡ �̷��Ե� ��밡��
}