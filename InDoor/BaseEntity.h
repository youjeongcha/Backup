#pragma once

class BaseEntity
{
private:
	int m_nID;

	static int m_nNextVaildID;

	void SetID(const int&);

public:
	BaseEntity(const int& id) { SetID(id); }
	virtual ~BaseEntity() {}

	virtual bool Update() abstract;
	int ID() const { return m_nID; }
};