#include <iostream>
using namespace std;
//main������ cin, cout ���, return ������


namespace OneInputLog
{
	string Log = "1�� ���� >> ���� 2���� �Է� : ";
	string result = "ū ���� : ";
}
namespace TwoInputLog
{
	string Log = "2�� ���� >> ���� �ϳ� �Է� : ";
	string result1 = "1 ~ 100 ����";
	string result2 = "����� ���� : ";
}
namespace TreeInputLog
{
	string Log = "3�� ���� >> ���� �ϳ� �Է� : ";
	string result = "�� �Ųٷ� �� : ";
}


void BiggerFun(int& iBigger, int iSmaller) //iSmaller�� ���۷��� ����� �ʿ�X
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
			tmp = num % 10; //tmp�� ������ ������ ����
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
			tmp = num % 10; //tmp�� ������ ������ ����
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

	//�� ���� ������ �Է� �޾� ū ���� ����Ͻÿ�.
	cout << OneInputLog::Log;
	cin >> iNum1 >> iNum2;
	cout << iNum1 << "�� " << iNum2 << OneInputLog::result;
	BiggerFun(iNum1, iNum2);
	cout << iNum1 << "\n\n";

	//�ϳ��� ���� �Է� �޾� 1 ~ 100 ������ �ش� ���� ��� ���� ���Ͻÿ�.(5�Է½� 1-100������ 5�� ����� ��� �ջ�)
	cout << TwoInputLog::Log;
	cin >> iNum1;
	cout << TwoInputLog::result1 << iNum1 << TwoInputLog::result2;
	MultipleFun(iNum1);
	cout << iNum1 << "\n\n";

	//�ϳ��� ���ڸ� �Է� �޾� �Ųٷ� ����Ͻÿ�.
	cout << TreeInputLog::Log;
	cin >> iNum1;
	cout << iNum1 << TreeInputLog::result;
	Reverse(iNum1);
	cout << iNum1 << "\n\n";
}