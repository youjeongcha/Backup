#pragma once
#include "Object.h"

class Table_Red : public Object
{
private:

public:
	Table_Red();
	Table_Red(const ObjectData& dataSet, int index);
	~Table_Red();
	VOID Initialize() override;
	VOID Move(const FLOAT& deltaTime) override;
	//---������ ����----
	void DetailSelect(int selectNum) override;
};