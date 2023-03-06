#include "MinersWifeOwnedStates.h"
#include "MinersWife.h"
#include "Locations.h"
#include "CrudeTimer.h"
#include "MessageDispatcher.h"
#include "MessageTypes.h"
#include "EntityNames.h"
//#include "FrameCounter.h"

#include <iostream>
using std::cout;

#ifdef TEXTOUTPUT
#include <fstream>
extern std::ofstream os;
#define cout os
#endif

//-----------------------------------------------------------------------Global state

WifesGlobalState* WifesGlobalState::Instance()
{
	static WifesGlobalState instance;

	return &instance;
}


void WifesGlobalState::Execute(MinersWife* wife)
{
	//1 in 10 chance of needing the bathroom (provided she is not already
	//in the bathroom)
	if ( (RandFloat() < 0.1) && 
		!wife->GetFSM()->isInState(*VisitBathroom::Instance()) )
	{
		wife->GetFSM()->ChangeState(VisitBathroom::Instance());
	}
}

bool WifesGlobalState::OnMessage(MinersWife* wife, const Telegram& msg)
{
	SetTextColor(BACKGROUND_RED|FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE);

	switch(msg.Msg)
	{
	case Msg_HiHoneyImHome:
		{
			cout<<"\n"<<GetNameOfEntity(wife->ID())<<"��(��) �ð�:"<<Clock->GetTickCount()<<"�� ������ �޽���.";

			SetTextColor(FOREGROUND_GREEN|FOREGROUND_INTENSITY);

			cout<<"\n"<<GetNameOfEntity(wife->ID())<<" : ����, ���ִ� �ð�� ���� ����� �帱����.";

			wife->GetFSM()->ChangeState(CookStew::Instance(), TRUE);
		}

		return true;

	}//end switch

	return false;
}

//-------------------------------------------------------------------------DoHouseWork

DoHouseWork* DoHouseWork::Instance()
{
	static DoHouseWork instance;

	return &instance;
}


void DoHouseWork::Enter(MinersWife* wife)
{
	cout<<"\n"<<GetNameOfEntity(wife->ID())<<" : �������� ���� �� �ð��̱�!";
}


void DoHouseWork::Execute(MinersWife* wife)
{
	switch(RandInt(0,2))
	{
	case 0:
		cout<<"\n"<<GetNameOfEntity(wife->ID())<<" : �ٴ��� �۴´�.";
		break;

	case 1:
		cout<<"\n"<<GetNameOfEntity(wife->ID())<<" : ���ø� �۴´�.";
		break;

	case 2:
		cout<<"\n"<<GetNameOfEntity(wife->ID())<<" : ���ڸ��� �غ��Ѵ�.";
		break;
	}
}

void DoHouseWork::Exit(MinersWife* wife, bool isRecMsg)
{
	//if(!isRecMsg){}
}

bool DoHouseWork::OnMessage(MinersWife* wife, const Telegram& msg)
{
	return false;
}

//------------------------------------------------------------------------VisitBathroom

VisitBathroom* VisitBathroom::Instance()
{
	static VisitBathroom instance;

	return &instance;
}


void VisitBathroom::Enter(MinersWife* wife)
{
	cout<<"\n"<<GetNameOfEntity(wife->ID())<<" : ȭ��Ƿ� �ɾ��.";
	cout<<"\n"<<GetNameOfEntity(wife->ID())<<" : ������ �Һ��� ���߰ڱ���.";
}


void VisitBathroom::Execute(MinersWife* wife)
{
	cout<<"\n"<<GetNameOfEntity(wife->ID())<<" : ��~! �ÿ��ϴ�!";

	wife->GetFSM()->RevertToPreviousState();
}

void VisitBathroom::Exit(MinersWife* wife, bool isRecMsg)
{
	if(!isRecMsg)
	{
		cout<<"\n"<<GetNameOfEntity(wife->ID())<<" : ȭ��ǿ��� ���´�.";
	}
}


bool VisitBathroom::OnMessage(MinersWife* wife, const Telegram& msg)
{
	return false;
}


//------------------------------------------------------------------------CookStew

CookStew* CookStew::Instance()
{
	static CookStew instance;

	return &instance;
}


void CookStew::Enter(MinersWife* wife)
{
	//if not already cooking put the stew in the oven
	if (!wife->Cooking())
	{
		cout<<"\n"<<GetNameOfEntity(wife->ID())<<" : ���� ���쿡 �ִ´�.";

		//send a delayed message myself so that I know when to take the stew
		//out of the oven
		Dispatch->DispatchMessages(1.5,                  //time delay
			wife->ID(),           //sender ID
			wife->ID(),           //receiver ID
			Msg_StewReady,        //msg
			(void*)NO_ADDITIONAL_INFO);

		wife->SetCooking(true);
	}
}


void CookStew::Execute(MinersWife* wife)
{
	cout<<"\n"<<GetNameOfEntity(wife->ID())<<" : ���� ���� ���� �ȴ޺����Ѵ�.";
}

void CookStew::Exit(MinersWife* wife, bool isRecMsg)
{
	if(!isRecMsg)
	{
		return;
	}

	SetTextColor(FOREGROUND_GREEN|FOREGROUND_INTENSITY);
	cout<<"\n"<<GetNameOfEntity(wife->ID())<<" : ��Ź���� ���� �÷� ���´�.";
}


bool CookStew::OnMessage(MinersWife* wife, const Telegram& msg)
{
	SetTextColor(BACKGROUND_RED|FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE);

	switch(msg.Msg)
	{
	case Msg_StewReady:
		{
			cout<<"\n"<<GetNameOfEntity(wife->ID())<<"��(��) �ð�:"<<Clock->GetTickCount()<<"�� ������ �޽���.";

			SetTextColor(FOREGROUND_GREEN|FOREGROUND_INTENSITY);
			cout<<"\n"<<GetNameOfEntity(wife->ID())<<" : ���� �غ񰡵Ʊ���! ��ô�.";

			//let hubby know the stew is ready
			Dispatch->DispatchMessages(SEND_MSG_IMMEDIATELY,
				wife->ID(),
				ent_Miner_Bob,
				Msg_StewReady,
				(void*)NO_ADDITIONAL_INFO);

			wife->SetCooking(false);

			wife->GetFSM()->ChangeState(DoHouseWork::Instance(), TRUE);               
		}

		return true;

	}//end switch

	return false;
}