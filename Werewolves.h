#pragma once
#include "Character.h"
class Werewolves : public Character
{
private:
public:
	Werewolves();
	Werewolves(Character monster); //<부모인 Charcter의 monster 형태>를 호출하는 방법 cpp참고
	~Werewolves();
};