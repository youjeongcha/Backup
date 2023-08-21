#pragma once
#include "Object.h"

class Bookcase : public Object
{
private:

public:
	Bookcase();
	Bookcase(const ObjectData& dataSet, int index);
	~Bookcase();
	VOID Initialize() override;
	VOID Move(const FLOAT& deltaTime) override;
	//---선택지 관련----
	void DetailSelect(int selectNum) override;
};