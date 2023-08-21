#pragma once
#include "Item.h"

class Water : public Item
{
private:
public:
	//Water();
	Water(ITEM_DETAIL itemDetail, ITEM_ID _itemID);
	~Water();
	//virtual void Use() override;
};