#pragma once
#include "Object.h"

class WaterCup : public Object
{
private:
public:
	WaterCup();
	WaterCup(const ObjectData& dataSet, int index);
	~WaterCup();
	//VOID Draw() override;
	VOID Initialize() override;
	VOID Move(const FLOAT& deltaTime) override;
	//---������ ����----
	void DetailSelect(int selectNum) override;
};