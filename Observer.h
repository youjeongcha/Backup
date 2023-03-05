#pragma once
#include "Mecro.h"

class Observer abstract //추상 클래스
{
private:
public:
	Observer();
	virtual ~Observer();
	virtual void InfoUpdate(std::string mDate, std::string newsInfo) abstract; //순수 가상함수 //옵저버에서 대상의 데이터를 가져오는 방식(풀 방식)
	virtual void InfoPrint() abstract; //순수 가상함수 
};

