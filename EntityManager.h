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
	// 기존 포인터들을 저장해 놓기 위한 것
	typedef map<int, BaseGameEntity*> EntityMap;

private:
	// 급히 참조할 수 있도록 엔티티들은 std::map에 저장되는데,
	// 여기서 엔티티들로의 포인터들은 자신의 식별 번호에 의해 교차참조된다.
	EntityMap	m_EntityMap;

	EntityManager(){}
	EntityManager(const EntityManager&);
	EntityManager& operator=(const EntityManager&);

public:
	static EntityManager* Instance();

	// std::vector 내의 엔티티로의 포인터를 저장하고
	// 엔티티의 ID가 지정하는 색인 위치에서의 m_Entities
	// (더 빨리 접근하게 해준다.)
	void	RegisterEntity(BaseGameEntity* newEntity);

	// 매개변수로 주어진 ID를 갖고 있는 엔티티를 가리키는 포인터를 반환한다.
	BaseGameEntity* GetEntityFromID(int id)const;

	// 엔티티를 리스트에서 제거 한다.
	void	RemoveEntity(BaseGameEntity* pEntity);
};

// entityManager의 인스턴스를 쉽게 접근할 수 있는 방법을 제공.
#define EntityMgr EntityManager::Instance()

#endif