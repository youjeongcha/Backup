#pragma once
#include "Object.h"

class OneCandle : public Object
{
private:

public:
	OneCandle();
	OneCandle(const ObjectData& dataSet, int index);
	~OneCandle();
	VOID Initialize() override;
	VOID Move(const FLOAT& deltaTime) override;
	//void Animation(const FLOAT& deltaTime) override;
	//---선택지 관련----
	void DetailSelect(int selectNum) override;
};