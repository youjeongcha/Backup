#pragma once
#include "Object.h"

class Bed : public Object
{
private:

public:
	Bed();
	Bed(const ObjectData& dataSet, int index);
	~Bed();
	VOID Initialize() override;
	VOID Move(const FLOAT& deltaTime) override;
	//---������ ����----
	void DetailSelect(int selectNum) override;
};