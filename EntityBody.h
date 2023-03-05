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
	string m_EntityBody[ENTITYTYPE_COUNT][TEN]; //character에는 enum으로 개체 정보를 가지고 있다.
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

