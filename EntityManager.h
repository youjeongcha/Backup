#ifndef _ENTITYMANAGER_H
#define _ENTITYMANAGER_H

#pragma warning (disable:4786)

#include <map>
#include <cassert>
#include <string>

using namespace std;
class BaseGameEntity;

class EntityManager
{
private:
	// ���� �����͵��� ������ ���� ���� ��
	typedef map<int, BaseGameEntity*> EntityMap;

private:
	// ���� ������ �� �ֵ��� ��ƼƼ���� std::map�� ����Ǵµ�,
	// ���⼭ ��ƼƼ����� �����͵��� �ڽ��� �ĺ� ��ȣ�� ���� ���������ȴ�.
	EntityMap	m_EntityMap;

	EntityManager(){}
	EntityManager(const EntityManager&);
	EntityManager& operator=(const EntityManager&);

public:
	static EntityManager* Instance();

	// std::vector ���� ��ƼƼ���� �����͸� �����ϰ�
	// ��ƼƼ�� ID�� �����ϴ� ���� ��ġ������ m_Entities
	// (�� ���� �����ϰ� ���ش�.)
	void	RegisterEntity(BaseGameEntity* newEntity);

	// �Ű������� �־��� ID�� ���� �ִ� ��ƼƼ�� ����Ű�� �����͸� ��ȯ�Ѵ�.
	BaseGameEntity* GetEntityFromID(int id)const;

	// ��ƼƼ�� ����Ʈ���� ���� �Ѵ�.
	void	RemoveEntity(BaseGameEntity* pEntity);
};

// entityManager�� �ν��Ͻ��� ���� ������ �� �ִ� ����� ����.
#define EntityMgr EntityManager::Instance()

#endif