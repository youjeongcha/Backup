#include "Person.h"
#include "Interface.h"

Person::Person(std::string _Name) : mName(_Name) //이니셜라이저
{
	mCheckedNews = "";
	mDate = "";
}
Person::~Person()
{
}

void Person::InfoUpdate(std::string date, std::string newsInfo)
{
	mDate = date;
	mCheckedNews = newsInfo;
}

void Person::InfoPrint()
{
	Interface UI;
	UI.NewsWatch(mDate, mCheckedNews, mName);
}