#include<iostream>
//입력 버퍼는 \n가 나오면 입력된 정보를 입력 버퍼 공간에서 내보낸다
//space와 \n로 단어를 하나로 판단(scanf와 cin 공통)
//차 유정 출력X
//한번 cin후에 다음 cin 없이
//차
//유정으로
void main()
{
	char name[20];
	std::cout << "이름을 입력하세요! ";
	std::cin >> name;
	std::cout << "나의 이름은 " << name << "입니다." << std::endl;
	std::cin >> name;
	std::cout << "나의 이름은 " << name << "입니다." << std::endl;
	return;
}