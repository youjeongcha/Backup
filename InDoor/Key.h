#pragma once
#include "Item.h"

class Key : public Item
{
protected:
public:
	Key();
	Key(ITEM_DETAIL itemDetail, ITEM_ID _itemID);
	~Key();
};

