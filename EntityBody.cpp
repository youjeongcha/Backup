#include "EntityBody.h"

EntityBody::EntityBody()
{
	mCriticalWords = "���� ������ �����߽��ϴ�.";
}
EntityBody::~EntityBody()
{
}

void EntityBody::CreateEntityBody()//TODO::EntityBody.c�� .h ������ �ϴ°�?
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