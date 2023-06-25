#pragma once
#include "Object.h"

class Window : public Object
{
private:
public:
	Window();
	~Window();
	VOID Initialize() override;
	VOID Move(const FLOAT& deltaTime) override;
};


