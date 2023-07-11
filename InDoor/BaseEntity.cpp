#include "BaseEntity.h"
#include <cassert>

int BaseEntity::m_nNextVaildID = 0;

void BaseEntity::SetID(const int& id)
{
	// (id < m_nNextVaildID) ��Ȳ�� ��� ���� �޽��� �߻�!!
	// ���� �޽��� �߻� �� "<BaseGameEntity::SetID>:invaild ID" ���� ���� ���.
	assert((id >= m_nNextVaildID) && "<BaseGameEntity::SetID>:invaild ID");

	m_nID = id;
	m_nNextVaildID = m_nID + 1;
}