#ifndef _BASE_GAME_ENTITY_H_
#define _BASE_GAME_ENTITY_H_

#include <string>

#include "Telegram.h"

class BaseGameEntity
{
private:
	// ��� ��ƼƼ���� ������ �ĺ���ȣ�� ���´�.
	int m_ID;

	// �̰��� ��ȿ�� ���� �ĺ���ȣ�̴�.
	// BaseGameEntity�� �Ź� �ʱ�ȭ�� �� �� ���� ���ŵȴ�.
	static int m_iNextValidID;

	// �̰��� ID�� ��Ȯ�ϰ� �����ǵ��� ������ ���ο��� ȣ��ȴ�.
	// �̰��� ID�� �����ϰ� ��ȿ�� ���� ID�� ������ŰŰ ����,
	// �޼ҵ忡 ���޵� ���� ��ȿ�� ���� ID���� �� ū�� �ƴϸ� �������� Ȯ���Ѵ�.
	void SetID(int id);

public:
	BaseGameEntity(int id)
	{
		SetID(id);
	}

	virtual ~BaseGameEntity(){}

	// ��� ��ƼƼ���� ���� �Լ��� ��ġ�ϰ� �־�߸� �Ѵ�.
	virtual void Update() = 0;

	int ID()const
	{
		return m_ID;
	}

	virtual bool HandleMessage(const Telegram& msg) = 0;
};

#endif