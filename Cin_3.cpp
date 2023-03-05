#include<iostream>
//console output input
void main()
{
	char name[20];
	std::cout << "이름을 입력하세요! ";
	std::cin.get(name,20); //차 유정 출력O
	std::cout << "나의 이름은 " << name << "입니다." << std::endl;
	return;
}