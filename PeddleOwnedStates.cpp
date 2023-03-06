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
			cout<<"\n"<<GetNameOfEntity(pPeddle->ID())<<"��(��) �ð�:"<<Clock->GetTickCount()<<"�� ������ �޽���.";

			SetTextColor(BACKGROUND_INTENSITY | FOREGROUND_BLUE | FOREGROUND_INTENSITY);

			cout<<"\n"<<GetNameOfEntity(pPeddle->ID())<<" : �մ�, �� ���� �� ���ð� ������~!!";

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
		cout<<"\n"<<GetNameOfEntity(pPeddle->ID())<<" : �Դϴ�! �ο�!";
		break;

	case 1:
		cout<<"\n"<<GetNameOfEntity(pPeddle->ID())<<" : ����~! ���ĸ��� ������...";
		break;

	case 2:
		cout<<"\n"<<GetNameOfEntity(pPeddle->ID())<<" : ��� �� �ƴϸ� �մ��� ����!!";
		break;
	case 3:
		cout<<"\n"<<GetNameOfEntity(pPeddle->ID())<<" : �ű� ���� �ư��� ������ ���ð� ������~!";
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
		cout<<"\n"<<GetNameOfEntity(pPeddle->ID())<<" : �� �������� �����帮�ڸ�...";

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
		cout<<"\n"<<GetNameOfEntity(pPeddle->ID())<<" : ���~���~.";
		break;
	case 1:
		cout<<"\n"<<GetNameOfEntity(pPeddle->ID())<<" : ���~���~.";
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
			cout<<"\n"<<GetNameOfEntity(pPeddle->ID())<<"��(��) �ð�:"<<Clock->GetTickCount()<<"�� ������ �޽���.";

			SetTextColor(BACKGROUND_INTENSITY | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
			cout<<"\n"<<GetNameOfEntity(pPeddle->ID())<<" : �����մϴ�. �ǿ�����~!";

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