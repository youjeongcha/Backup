#pragma once
#include "Object.h"

class Drawer : public Object
{
private:

public:
	Drawer();
	Drawer(const ObjectData& dataSet, int index);
	~Drawer();
	VOID Initialize() override;
	VOID Move(const FLOAT& deltaTime) override;
	//---선택지 관련----
	void DetailSelect(int selectNum) override;
};