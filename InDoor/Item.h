#pragma once
#include "Object.h"

class Item : Object
{
protected:

public:
	Item();
	~Item();

    VOID Initialize() override;
};