#pragma once
#include "Object.h"

class Stove : public Object
{
private:

public:
	Stove();
	Stove(const ObjectData& dataSet, int index);
	~Stove();
	VOID Initialize() override;
	VOID Move(const FLOAT& deltaTime) override;
	//---������ ����----
	void DetailSelect(int selectNum) override;
};