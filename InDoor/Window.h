#pragma once
#include "Object.h"

class Window : public Object
{
private:
public:
	Window();
	Window(const ObjectData& dataSet, int index);
	~Window();
	VOID Initialize() override;
	VOID Move(const FLOAT& deltaTime) override;
	//---선택지 관련----
	void DetailSelect(int selectNum) override;
};


