#include<iostream>
using namespace std;

class Add
{
//�ƹ��͵� ���� �� �ϸ� private�� �⺻�� �ȴ�.
public:
	void AddNum1(int Num = 10); //�Լ� �������� ��� �Ѵ�.
	void AddNum2(int Num1 = 10, int Num2 = 5); //����Ʈ �Ű������� ����Ҷ��� ������ ����������
};
void Add::AddNum1(int Num)//���� ���� �⺻ �Լ� ������ ��� ���. //int Num2 = 5 //�Լ� �������� ��� �Ѵ�.
{
	cout << Num << "+" << "1 = " << Num + 1 << endl;
}
void Add::AddNum2(int Num1, int Num2)
{
	cout << Num1 << "+" << Num2 << " = " << Num1 + Num2 << endl;
}
void main()
{
	Add add;
	add.AddNum1(); //ȣ�� ��ü�� ���� �׳� ������ �ִ� �ڵ��� �Ű� xx
	add.AddNum1(20);
	add.AddNum2();
	add.AddNum2(20);
	add.AddNum2(10, 20);
}