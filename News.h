#pragma once
#include "Subject.h"
#include "Mecro.h"
#include <time.h>
//추상클래스. 싱글톤 패턴


class News : public Subject
{
private:
	static News* m_pInstance; // 자기 자신의 형태를 띈 객체의 주소를 가리킨다.

	std::string mDate;
	std::string mNewsInfo;
	std::vector<Observer*> mObserverList; //오버라이드해서 사용
	//★ 중복 객체를 들어오지 않게 하기 위해서. set이나 알고리즘 헤더 파일의 알고리즘 사용. 참고.
	//현재 구조에서는 중복 객체가 들어올 일이 없긴 했다. 입력 받으면 바로 new 생성해버리니까.
	//Ex.유투브 구독을 세번 누른다고 세번 구독이 되고 같은 알람이 세번 오는 것.

	News(); //멋대로 생성하지 못하게

public:
	~News();
	static News* Get_Instance()
	{
		if (NULL == m_pInstance)
			m_pInstance = new News;
		return m_pInstance;
	}
	//gameManager 같은 경우 맨 끝줄에 쓰거나 작성하지 않는다. 다만 쓰다가 메모리 낭비를 위해 삭제할 class에는 필요하다.
	void Destory()
	{
		delete m_pInstance;
		m_pInstance = nullptr;
	}
	
	void NewsUpdate(std::string sNews);
	void Observer_InfoPrint();

	virtual Observer* Observer_Add(Observer* coustomerName) override; //override를 해야 가상함수로 객체를 생성할 수 있게 된다.
	virtual void Observer_InfoUpdate() override;
};

