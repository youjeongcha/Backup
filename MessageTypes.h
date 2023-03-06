#ifndef _MESSAGE_TYPES
#define _MESSAGE_TYPES

#include <string>

enum message_type
{
	Msg_HiHoneyImHome,
	Msg_StewReady,
	Msg_MeetPeddle,
	Msg_SaleIsMiner,
	Msg_LeaveMiner
};

inline std::string MsgToStr(int msg)
{
	switch (msg)
	{
	case Msg_HiHoneyImHome:

		return "HiHoneyImHome"; 

	case Msg_StewReady:

		return "StewReady";

	case Msg_MeetPeddle:

		return "MeetMiner";

	case Msg_SaleIsMiner:

		return "SaleIsMiner";

	case Msg_LeaveMiner:

		return "LeaveMiner";

	default:

		return "Not recognized!";
	}
}

#endif