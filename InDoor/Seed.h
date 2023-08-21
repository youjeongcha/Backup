#pragma once
#include "Item.h"

class Seed : public Item
{
protected:
public:
	Seed();
	Seed(ITEM_DETAIL itemDetail, ITEM_ID _itemID);
	~Seed();
};