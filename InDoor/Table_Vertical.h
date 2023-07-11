#pragma once
#include "Object.h"

class Table_Vertical : public Object
{
private:

public:
	Table_Vertical();
	Table_Vertical(const ObjectData& dataSet, int index);
	~Table_Vertical();
	VOID Initialize() override;
	VOID Move(const FLOAT& deltaTime) override;
	//---������ ����----
	void DetailSelect(int selectNum) override;
};