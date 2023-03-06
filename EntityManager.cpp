#include "EntityManager.h"
#include "BaseGameEntity.h"

EntityManager* EntityManager::Instance()
{
	static EntityManager instance;
	return &instance;
}

void	EntityManager::RegisterEntity(BaseGameEntity* newEntity)
{
	m_EntityMap.insert(std::make_pair(newEntity->ID(), newEntity));
}

BaseGameEntity* EntityManager::GetEntityFromID(int id)const
{
	// 엔티티를 찾는다.
	EntityMap::const_iterator ent = m_EntityMap.find(id);

	assert ((ent !=  m_EntityMap.end()) && "<EntityManager::GetEntityFromID> : invalid ID");
	return ent->second;
}

void EntityManager::RemoveEntity(BaseGameEntity* pEntity)
{
	m_EntityMap.erase(m_EntityMap.find(pEntity->ID()));
}