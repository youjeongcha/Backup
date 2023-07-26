#pragma once
#include "Object.h"

class WallHanging : public Object
{
private:

public:
	WallHanging();
	WallHanging(const ObjectData& dataSet, int index);
	~WallHanging();
	VOID Initialize() override;
	VOID Move(const FLOAT& deltaTime) override;
	//---������ ����----
	void DetailSelect(int selectNum) override;
};