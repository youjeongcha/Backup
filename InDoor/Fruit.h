#pragma once
#include "Item.h"

class Fruit : public Item
{
protected:
public:
	Fruit(ITEM_ID _itemID);
	~Fruit();
};