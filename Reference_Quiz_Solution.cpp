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
	//하나의 수를 입력 받아 1 ~ 100 사이의 해당 수의 배수 합을 구하시오.(5입력시 1-100사이의 5의 배수를 모두 합산)
	Sum = 0;
	for (int i = 1; i <= 100; i++)
	{
		if (i % Num1 == 0) //방법 유의
			Sum += i;
	}
}

void Reverse(int Num1, int& ReverseNum)
{//간단
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
	cout << "1번문제 정수 2개를 입력 : ";
	cin >> Num1 >> Num2;
	Big(Num1, Num2, BigNum);
	cout << Num1 << "과 " << Num2 << "중 큰 수는 : " << BigNum << endl;
	cout << "2번문제 정수 하나 입력 : ";
	cin >> Num1;
	Sum(Num1, SumNum);
	cout << "1 ~ 100 사이 " << Num1 << "배수의 합은 : " << SumNum << endl;
	cout << "3번문제 정수 하나 입력 : ";
	cin >> Num1;
	Reverse(Num1, ReverseNum);
	cout << Num1 << "의 거꾸로 수 : " << ReverseNum << endl;
}

