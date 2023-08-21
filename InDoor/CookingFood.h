#pragma once
#include "Item.h"

class CookingFood : public Item
{
private:
public:
	CookingFood(ITEM_DETAIL itemDetail, ITEM_ID _itemID);
	~CookingFood();
	//virtual void Use() override;
};