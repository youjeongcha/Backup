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
	//---선택지 관련----
	void DetailSelect(int selectNum) override;
};