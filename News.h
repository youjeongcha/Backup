#pragma once
#include "Subject.h"
#include "Mecro.h"
#include <time.h>
//�߻�Ŭ����. �̱��� ����


class News : public Subject
{
private:
	static News* m_pInstance; // �ڱ� �ڽ��� ���¸� �� ��ü�� �ּҸ� ����Ų��.

	std::string mDate;
	std::string mNewsInfo;
	std::vector<Observer*> mObserverList; //�������̵��ؼ� ���
	//�� �ߺ� ��ü�� ������ �ʰ� �ϱ� ���ؼ�. set�̳� �˰��� ��� ������ �˰��� ���. ����.
	//���� ���������� �ߺ� ��ü�� ���� ���� ���� �ߴ�. �Է� ������ �ٷ� new �����ع����ϱ�.
	//Ex.������ ������ ���� �����ٰ� ���� ������ �ǰ� ���� �˶��� ���� ���� ��.

	News(); //�ڴ�� �������� ���ϰ�

public:
	~News();
	static News* Get_Instance()
	{
		if (NULL == m_pInstance)
			m_pInstance = new News;
		return m_pInstance;
	}
	//gameManager ���� ��� �� ���ٿ� ���ų� �ۼ����� �ʴ´�. �ٸ� ���ٰ� �޸� ���� ���� ������ class���� �ʿ��ϴ�.
	void Destory()
	{
		delete m_pInstance;
		m_pInstance = nullptr;
	}
	
	void NewsUpdate(std::string sNews);
	void Observer_InfoPrint();

	virtual Observer* Observer_Add(Observer* coustomerName) override; //override�� �ؾ� �����Լ��� ��ü�� ������ �� �ְ� �ȴ�.
	virtual void Observer_InfoUpdate() override;
};

