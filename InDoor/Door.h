#pragma once
#include "Object.h"

class Door : public Object
{
private:

public:
	Door();
	Door(const ObjectData& dataSet, int index);
	~Door();
	VOID Initialize() override;
	VOID Move(const FLOAT& deltaTime) override;
	//---선택지 관련----
	//void DetailSelectForm();
	void DetailSelect(int selectNum) override;
};

