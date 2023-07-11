#include "BaseEntity.h"
#include <cassert>

int BaseEntity::m_nNextVaildID = 0;

void BaseEntity::SetID(const int& id)
{
	// (id < m_nNextVaildID) 상황인 경우 에러 메시지 발생!!
	// 에러 메시지 발생 시 "<BaseGameEntity::SetID>:invaild ID" 문구 같이 출력.
	assert((id >= m_nNextVaildID) && "<BaseGameEntity::SetID>:invaild ID");

	m_nID = id;
	m_nNextVaildID = m_nID + 1;
}