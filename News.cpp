#include "News.h"
#include "Observer.h" //�� ������ ��ü�� ����ϰ� �ִ� ���� cpp�̰� �Լ� ȣ���� ���� �¹��� �� �ֱ� ������ cpp�� �����ϴ� �� ��õ

News* News::m_pInstance = NULL; //����(���� �޸𸮰� �Ҵ�ȴ�. �������� ���ǹ� �ʱ�ȭ �ʼ�.)

News::News()
{
	mDate = "";
	mNewsInfo = "��ϵ� ������ ����";
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