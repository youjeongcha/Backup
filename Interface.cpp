#include "Interface.h"

int Interface::MainMenu()
{
	//����::�̷��͵� �Լ��� ����� ���� ������?
	std::cout << "===Atents News===" << std::endl;
	std::cout << " 1. �����" << std::endl;
	std::cout << " 2. News ����" << std::endl;
	std::cout << " 3. News ������Ʈ" << std::endl;
	std::cout << " 4. News ��û" << std::endl;

	return mInput.MainSelect();
}

std::string Interface::CustomerRegister()
{
	return mInput.InputCustomerName();
}

//void Interface::NewsSend()
//{
//}

std::string Interface::NewsUpdate()
{
	return mInput.InputNewNews();
}

void Interface::NewsWatch(std::string date, std::string newsInfo, std::string name)
{
	std::cout << std::endl << date << std::endl;
	std::cout << newsInfo << std::endl;
	std::cout << std::endl << "        " + name + "����." << std::endl;
}