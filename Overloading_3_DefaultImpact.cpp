#include<iostream>
using namespace std;

class Test
{
public:
	void test(int a, int b = 100);
	void test(int a);
};

void Test::test(int a, int b)
{
	cout << "����Ʈ ���� �Լ� ȣ��" << endl;
}

void Test::test(int a)
{
	cout << "�����ε� �Լ� ȣ��" << endl;
}

void main()
{
	Test t;
	t.test(10); //�����ε�� �Լ� "Test::test"�� �ν��Ͻ� �� �� �� �̻��� �μ� ��ϰ� ��ġ�մϴ�.
}