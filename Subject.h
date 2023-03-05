#pragma once
//#include "Person.h"
class Observer; //★ 이렇게 참조만 하는 경우 포인터로 사용할 수만 있다

class Subject abstract //추상 클래스
{
private:
public:
	Subject();
	virtual ~Subject();
	virtual Observer* Observer_Add(Observer* userName) abstract; //순수 가상함수 //★
	virtual void Observer_InfoUpdate() abstract;//순수 가상함수 //대상에서 옵저버에게 데이터를 보내는 방식(푸시 방식)
};

