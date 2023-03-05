#include "EntityBody.h"

EntityBody::EntityBody()
{
	mCriticalWords = "약점 부위를 공격했습니다.";
}
EntityBody::~EntityBody()
{
}

void EntityBody::CreateEntityBody()//TODO::EntityBody.c와 .h 만들어야 하는가?
{
	ifstream load;

	string str;
	load.open("SaveEntityBody.txt");
	if (!load.eof())
	{
		for (int i = 0; i < ENTITYTYPE_COUNT; i++)
		{
			for (int j = 0; j < TEN; j++)
			{
				load >> m_EntityBody[i][j];
			}
		}
		load.close();
	}
}

long double EntityBody::GetRisingPercentage(int parts)
{ 
	if (parts == HIGHTEST_PERCENTAGE)
		return 2;
	else if (parts == LOW_PERCENTAGE)
		return 1.2;
}