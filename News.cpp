#include "News.h"
#include "Observer.h" //★ 실제로 객체를 사용하고 있는 곳은 cpp이고 함수 호출이 서로 맞물릴 수 있기 때문에 cpp에 선언하는 걸 추천

News* News::m_pInstance = NULL; //정의(실제 메모리가 할당된다. 전역에서 정의및 초기화 필수.)

News::News()
{
	mDate = "";
	mNewsInfo = "등록된 뉴스가 없음";
}
News::~News()
{
	for (std::vector<Observer*>::iterator iter = mObserverList.begin(); iter != mObserverList.end();)
		delete* iter;
}


Observer* News::Observer_Add(Observer* coustomerName)
{
	mObserverList.push_back(coustomerName);

	return coustomerName;
}

void News::Observer_InfoUpdate()
{
	for (std::vector<Observer*>::iterator iter = mObserverList.begin(); iter != mObserverList.end(); iter++)
	{
		(*iter)->InfoUpdate(mDate, mNewsInfo);
	}
}

void News::NewsUpdate(std::string sNews)
{
	mNewsInfo = sNews;
	mDate = currentDateTime();
}

void News::Observer_InfoPrint()
{
	for (std::vector<Observer*>::iterator iter = mObserverList.begin(); iter != mObserverList.end(); iter++)
	{
		(*iter)->InfoPrint();
	}
} 