#include<iostream>
//console output input
void main()
{
	char name[20];
	std::cout << "�̸��� �Է��ϼ���! ";
	std::cin.get(name,20); //�� ���� ���O
	std::cout << "���� �̸��� " << name << "�Դϴ�." << std::endl;
	return;
}