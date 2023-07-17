#pragma once
#include "Object.h"

class Closet : public Object
{
private:

public:
	Closet();
	Closet(const ObjectData& dataSet, int index);
	~Closet();
	VOID Initialize() override;
	VOID Move(const FLOAT& deltaTime) override;
	//---선택지 관련----
	void DetailSelect(int selectNum) override;
};