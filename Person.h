#pragma once
#include "Observer.h"

class Person : public Observer //가상 함수 //public으로 선언하지 않을 시 defualt로 private 설정
{
private:
	std::string mName;
	std::string mCheckedNews;
	std::string mDate;
public:
	Person(std::string _Name); //이니셜라이저
	~Person();
	virtual void InfoUpdate(std::string date, std::string newsInfo) override;
	virtual void InfoPrint() override;
};