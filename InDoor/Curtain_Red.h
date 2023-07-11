#pragma once
#include "Object.h"

class Curtain_Red : public Object
{
private:

public:
	Curtain_Red();
	Curtain_Red(const ObjectData& dataSet, int index);
	~Curtain_Red();
	VOID Initialize() override;
	VOID Move(const FLOAT& deltaTime) override;
	//---선택지 관련----
	void DetailSelect(int selectNum) override;
};