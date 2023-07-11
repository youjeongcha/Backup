#pragma once
#include "Object.h"

class Shelf_Book : public Object
{
private:

public:
	Shelf_Book();
	Shelf_Book(const ObjectData& dataSet, int index);
	~Shelf_Book();
	VOID Initialize() override;
	VOID Move(const FLOAT& deltaTime) override;
	//---선택지 관련----
	void DetailSelect(int selectNum) override;
};