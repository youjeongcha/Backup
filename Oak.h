#pragma once
#include "Character.h"

class Oak : public Character
{
private:
public:
	Oak();
	Oak(Character monster); //<부모인 Charcter의 monster 형태>를 호출하는 방법 cpp참고
	~Oak();
};
