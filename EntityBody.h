#pragma once
#include "Mecro.h"
#include "Character.h"

#define HIGHTEST_PERCENTAGE 1
#define LOW_PERCENTAGE 2
#define TEN 10
#define FOUR 4

class EntityBody
{
private:
	string m_EntityBody[ENTITYTYPE_COUNT][TEN]; //character���� enum���� ��ü ������ ������ �ִ�.
	string mCriticalWords;
	//long double mRisingPercentage;
public:
	EntityBody();
	~EntityBody();

	void CreateEntityBody();

	string GetCriticalWords() { return mCriticalWords; }
	long double GetRisingPercentage(int parts);
	string (*GetEntityBody())[TEN] { return m_EntityBody; }
};

