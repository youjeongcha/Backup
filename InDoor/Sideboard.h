#pragma once
#include "Object.h"

class Sideboard : public Object
{
private:

public:
	Sideboard();
	Sideboard(const ObjectData& dataSet, int index);
	~Sideboard();
	VOID Initialize() override;
	VOID Move(const FLOAT& deltaTime) override;
	//---������ ����----
	void DetailSelect(int selectNum) override;
};