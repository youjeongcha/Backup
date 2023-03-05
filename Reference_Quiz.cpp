#include <iostream>
using namespace std;
//main에서만 cin, cout 사용, return 사용금지


namespace OneInputLog
{
	string Log = "1번 문제 >> 정수 2개를 입력 : ";
	string result = "큰 수는 : ";
}
namespace TwoInputLog
{
	string Log = "2번 문제 >> 정수 하나 입력 : ";
	string result1 = "1 ~ 100 사이";
	string result2 = "배수의 합은 : ";
}
namespace TreeInputLog
{
	string Log = "3번 문제 >> 정수 하나 입력 : ";
	string result = "의 거꾸로 수 : ";
}


void BiggerFun(int& iBigger, int iSmaller) //iSmaller는 레퍼런스 사용할 필요X
{
	if (iBigger < iSmaller)
		iBigger = iSmaller;
}

void MultipleFun(int& sum)
{
	int num = sum, i = 1;
	sum = 0;

	while (true)
	{
		if ((num >= 1) && (num * i <= 100))
		{
			sum += num * i;
			i++;
		}
		else
			break;
	}
}

void Reverse(int& num)
{

	int result = 0, tmp;

	while (true)
	{
		result *= 10;

		if (num / 10 >= 1)
		{
			tmp = num % 10; //tmp가 존재할 이유가 없다
			num /= 10;
		}
		else
		{
			result += num;
			num = result;
			break;
		}
		result += tmp;
	}

	/*	int result = 0, tmp;

	while (true)
	{
		result *= 10;

		if (num / 10 >= 1)
		{
			tmp = num % 10; //tmp가 존재할 이유가 없다
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
	int iNum1, iNum2;

	//두 개의 정수를 입력 받아 큰 수를 출력하시오.
	cout << OneInputLog::Log;
	cin >> iNum1 >> iNum2;
	cout << iNum1 << "과 " << iNum2 << OneInputLog::result;
	BiggerFun(iNum1, iNum2);
	cout << iNum1 << "\n\n";

	//하나의 수를 입력 받아 1 ~ 100 사이의 해당 수의 배수 합을 구하시오.(5입력시 1-100사이의 5의 배수를 모두 합산)
	cout << TwoInputLog::Log;
	cin >> iNum1;
	cout << TwoInputLog::result1 << iNum1 << TwoInputLog::result2;
	MultipleFun(iNum1);
	cout << iNum1 << "\n\n";

	//하나의 숫자를 입력 받아 거꾸로 출력하시오.
	cout << TreeInputLog::Log;
	cin >> iNum1;
	cout << iNum1 << TreeInputLog::result;
	Reverse(iNum1);
	cout << iNum1 << "\n\n";
}