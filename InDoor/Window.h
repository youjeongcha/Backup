#pragma once
#include "Object.h"




class Window : public Object
{
private:
	//State* m_CurrState;

public:
	Window();
	Window(const ObjectData& dataSet, int index);
	~Window();
	VOID Initialize() override;
	VOID Move(const FLOAT& deltaTime) override;
	//---������ ����----
	void DetailSelect(int selectNum) override;

	//���±����� : ó�� �κ� ���� �ʿ� TODO::!
//private:
//	int m_nID;
//
//public:
//	//void SetID(const int&);
//	int ID() const { return m_nID; }
//
//	bool Update();
//	void ChangeState(State*);
};


