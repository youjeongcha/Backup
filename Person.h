#pragma once
#include "Observer.h"

class Person : public Observer //���� �Լ� //public���� �������� ���� �� defualt�� private ����
{
private:
	std::string mName;
	std::string mCheckedNews;
	std::string mDate;
public:
	Person(std::string _Name); //�̴ϼȶ�����
	~Person();
	virtual void InfoUpdate(std::string date, std::string newsInfo) override;
	virtual void InfoPrint() override;
};