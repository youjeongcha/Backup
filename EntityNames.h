#pragma once
#include <string>

enum
{
	ent_EvilPlant,
	//ent_Miner_Bob,
	//ent_Elsa
};

inline std::string GetNameOfEntity(int value)
{
	switch (value)
	{
	case ent_EvilPlant:
		return "���νĹ�";
	//case ent_Miner_Bob: return "���� Bob";
	//case ent_Elsa: return "Elsa";
	default: 
		return "Unknown!";
	}
}