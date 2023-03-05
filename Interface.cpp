#include "Interface.h"

int Interface::MainMenu()
{
	//질문::이런것도 함수를 만드는 편이 좋은가?
	std::cout << "===Atents News===" << std::endl;
	std::cout << " 1. 고객등록" << std::endl;
	std::cout << " 2. News 전송" << std::endl;
	std::cout << " 3. News 업데이트" << std::endl;
	std::cout << " 4. News 시청" << std::endl;

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
	std::cout << std::endl << "        " + name + "고객님." << std::endl;
}