#pragma once
#include "Object.h"

class KitchenCounter : public Object
{
private:

public:
	KitchenCounter();
	KitchenCounter(const ObjectData& dataSet, int index);
	~KitchenCounter();
	VOID Initialize() override;
	VOID Move(const FLOAT& deltaTime) override;
	//---������ ����----
	void DetailSelect(int selectNum) override;
};