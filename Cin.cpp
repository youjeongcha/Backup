#include<iostream>

void main()
{
	int num1, num2, sum;
	std::cout << "정수 2개를 입력하시오!" << std::endl;
	std::cin >> num1 >> num2;
	sum = num1 + num2;
	std::cout << num1 << "+" << num2;
	std::cout << "=" << sum << std::endl;
	return;
}