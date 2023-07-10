#pragma once
#include "Object.h"

class Flowerpot : public Object
{
private:

public:
	Flowerpot();
	Flowerpot(const ObjectData& dataSet, int index);
	~Flowerpot();
	VOID Initialize() override;
	VOID Move(const FLOAT& deltaTime) override;
	//---������ ����----
	void DetailSelect(int selectNum) override;
};
