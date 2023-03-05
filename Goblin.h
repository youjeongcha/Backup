#pragma once
#include "Character.h"

class Goblin : public Character
{
private:
public:
	Goblin();
	Goblin(Character); //<부모인 Charcter의 monster 형태>를 호출하는 방법 cpp참고
	~Goblin();
};
