#pragma once
#include "Input.h"
//#include "Observer.h"

class Interface
{
private:
	Input mInput;
public:
	int MainMenu();
	//Observer* CustomerRegister(); //�����ε� //����
	std::string CustomerRegister();
	//void NewsSend();
	std::string NewsUpdate();
	void NewsWatch(std::string date, std::string newsInfo, std::string name);
};

