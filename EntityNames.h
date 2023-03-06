#ifndef _NAMES_H
#define _NAMES_H

#include <string>

enum 
{
	ent_Miner_Bob,
	ent_Elsa,
	ent_Peddle
};

inline std::string GetNameOfEntity(int n)
{
	switch(n)
	{
	case ent_Miner_Bob:
		return "±¤ºÎ Bob";

	case ent_Elsa:
		return "Elsa";

	case ent_Peddle:
		return "º¸ºÎ»ó";

	default:
		return "UNKNOWN!";
	}
}

#endif