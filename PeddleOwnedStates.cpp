#include "PeddleOwnedStates.h"
#include "Peddle.h"
#include "Locations.h"
#include "CrudeTimer.h"
#include "MessageDispatcher.h"
#include "MessageTypes.h"
#include "EntityNames.h"

#include <iostream>
using std::cout;

#ifdef TEXTOUTPUT
#include <fstream>
extern std::ofstream os;
#define cout os
#endif
//-----------------------------------------------------------------------------------
//-----------------------------------------------------------------------Global state
PeddleGlobalState* PeddleGlobalState::Instance()
{
	static PeddleGlobalState instance;

	return &instance;
}

bool PeddleGlobalState::OnMessage(Peddle* pPeddle, const Telegram& msg)
{
	switch(msg.Msg)
	{
	case Msg_MeetPeddle:
		{
			SetTextColor(BACKGROUND_RED | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
			cout<<"\n"<<GetNameOfEntity(pPeddle->ID())<<"이(가) 시간:"<<Clock->GetTickCount()<<"에 수신한 메시지.";

			SetTextColor(BACKGROUND_INTENSITY | FOREGROUND_BLUE | FOREGROUND_INTENSITY);

			cout<<"\n"<<GetNameOfEntity(pPeddle->ID())<<" : 손님, 이 물건 좀 보시고 가세요~!!";

			pPeddle->GetFSM()->ChangeState(MeetMiner::Instance(), TRUE);
		}

		return true;

	}//end switch

	return false;
}
//-----------------------------------------------------------------------------------


//-----------------------------------------------------------------------------------
//-----------------------------------------------------------------------------DoWork
DoWork* DoWork::Instance()
{
	static DoWork instance;

	return &instance;
}

void DoWork::Execute(Peddle* pPeddle)
{
	switch(RandInt(0,3))
	{
	case 0:
		cout<<"\n"<<GetNameOfEntity(pPeddle->ID())<<" : 쌉니다! 싸요!";
		break;

	case 1:
		cout<<"\n"<<GetNameOfEntity(pPeddle->ID())<<" : 예휴~! 날파리만 날리네...";
		break;

	case 2:
		cout<<"\n"<<GetNameOfEntity(pPeddle->ID())<<" : 사실 거 아니면 손대지 마쇼!!";
		break;
	case 3:
		cout<<"\n"<<GetNameOfEntity(pPeddle->ID())<<" : 거기 예쁜 아가씨 여기좀 보시고 가세요~!";
		break;
	}
}
void DoWork::Exit(Peddle* pPeddle, bool isRecMsg)
{
	//if(!isRecMsg){}
}

bool DoWork::OnMessage(Peddle* pPeddle, const Telegram& msg)
{
	return false;
}
//-----------------------------------------------------------------------------------


//-----------------------------------------------------------------------------------
//--------------------------------------------------------------------------MeetMiner
MeetMiner* MeetMiner::Instance()
{
	static MeetMiner instance;

	return &instance;
}

void MeetMiner::Enter(Peddle* pPeddle)
{
	if(!pPeddle->IsSale())
	{
		cout<<"\n"<<GetNameOfEntity(pPeddle->ID())<<" : 이 물건으로 말씀드리자면...";

		Dispatch->DispatchMessages(SEND_MSG_IMMEDIATELY,        //time delay
			pPeddle->ID(),				//sender ID
			ent_Miner_Bob,				//receiver ID
			Msg_SaleIsMiner,			//msg
			(void*)NO_ADDITIONAL_INFO);

		pPeddle->SetIsSale(true);
	}
}

void MeetMiner::Execute(Peddle* pPeddle)
{
	switch(RandInt(0,2))
	{
	case 0:
		cout<<"\n"<<GetNameOfEntity(pPeddle->ID())<<" : 블라~블라~.";
		break;
	case 1:
		cout<<"\n"<<GetNameOfEntity(pPeddle->ID())<<" : 솰라~솰라~.";
		break;
	case 2:
		cout<<"\n"<<GetNameOfEntity(pPeddle->ID())<<" : . . .";
		break;
	}
}

void MeetMiner::Exit(Peddle* pPeddle, bool isRecMsg)
{
	/*if(!isRecMsg){
	return;
	}*/
	/*SetTextColor(FOREGROUND_BLUE|FOREGROUND_INTENSITY);
	cout<<"\n"<<GetNameOfEntity(pPeddle->ID())<<" : ";*/
}

bool MeetMiner::OnMessage(Peddle* pPeddle, const Telegram& msg)
{
	switch(msg.Msg)
	{
	case Msg_SaleIsMiner:
		{
			SetTextColor(BACKGROUND_RED | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
			cout<<"\n"<<GetNameOfEntity(pPeddle->ID())<<"이(가) 시간:"<<Clock->GetTickCount()<<"에 수신한 메시지.";

			SetTextColor(BACKGROUND_INTENSITY | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
			cout<<"\n"<<GetNameOfEntity(pPeddle->ID())<<" : 감사합니다. 또오세요~!";

			Dispatch->DispatchMessages(SEND_MSG_IMMEDIATELY,	//time delay
				pPeddle->ID(),									//sender ID
				ent_Miner_Bob,									//receiver ID
				Msg_LeaveMiner,									//msg
				(void*)NO_ADDITIONAL_INFO);

			pPeddle->SetIsSale(false);

			pPeddle->GetFSM()->ChangeState(DoWork::Instance(), TRUE);
		}

		return true;

	}//end switch

	return false;
}
//-----------------------------------------------------------------------------------