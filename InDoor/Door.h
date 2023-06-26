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
};

