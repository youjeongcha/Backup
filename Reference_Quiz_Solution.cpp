#include <iostream>
using namespace std;

void Big(int Num1, int Num2, int& BigNum)
{
	if (Num1 > Num2)
		BigNum = Num1;
	else
		BigNum = Num2;
}

void Sum(int Num1, int& Sum)
{
	//�ϳ��� ���� �Է� �޾� 1 ~ 100 ������ �ش� ���� ��� ���� ���Ͻÿ�.(5�Է½� 1-100������ 5�� ����� ��� �ջ�)
	Sum = 0;
	for (int i = 1; i <= 100; i++)
	{
		if (i % Num1 == 0) //��� ����
			Sum += i;
	}
}

void Reverse(int Num1, int& ReverseNum)
{//����
	ReverseNum = 0;
	while (1)
	{
		ReverseNum += Num1 % 10;
		Num1 /= 10;
		if (Num1 == 0)
			break;
		ReverseNum *= 10;
	}
	/*int result = 0, tmp;

	while (true)
	{
		result *= 10;

		if (num / 10 >= 1)
		{
			tmp = num % 10;
			num /= 10;
		}
		else
		{
			result += num;
			num = result;
			break;
		}
		result += tmp;
	}*/
}

void main()
{
	int Num1, Num2, BigNum, SumNum = 0, ReverseNum;
	cout << "1������ ���� 2���� �Է� : ";
	cin >> Num1 >> Num2;
	Big(Num1, Num2, BigNum);
	cout << Num1 << "�� " << Num2 << "�� ū ���� : " << BigNum << endl;
	cout << "2������ ���� �ϳ� �Է� : ";
	cin >> Num1;
	Sum(Num1, SumNum);
	cout << "1 ~ 100 ���� " << Num1 << "����� ���� : " << SumNum << endl;
	cout << "3������ ���� �ϳ� �Է� : ";
	cin >> Num1;
	Reverse(Num1, ReverseNum);
	cout << Num1 << "�� �Ųٷ� �� : " << ReverseNum << endl;
}

