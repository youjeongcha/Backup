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
		return "식인식물";
	//case ent_Miner_Bob: return "광부 Bob";
	//case ent_Elsa: return "Elsa";
	default: 
		return "Unknown!";
	}
}