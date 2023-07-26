#pragma once
#include "Object.h"

class FirePot : public Object
{
private:

public:
	FirePot();
	FirePot(const ObjectData& dataSet, int index);
	~FirePot();
	VOID Initialize() override;
	VOID Move(const FLOAT& deltaTime) override;
	//---선택지 관련----
	void DetailSelect(int selectNum) override;
};