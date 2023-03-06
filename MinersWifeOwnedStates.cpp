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
			cout<<"\n"<<GetNameOfEntity(wife->ID())<<"이(가) 시간:"<<Clock->GetTickCount()<<"에 수신한 메시지.";

			SetTextColor(FOREGROUND_GREEN|FOREGROUND_INTENSITY);

			cout<<"\n"<<GetNameOfEntity(wife->ID())<<" : 여보, 맛있는 시골식 국을 만들어 드릴께요.";

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
	cout<<"\n"<<GetNameOfEntity(wife->ID())<<" : 집안일을 좀더 할 시간이군!";
}


void DoHouseWork::Execute(MinersWife* wife)
{
	switch(RandInt(0,2))
	{
	case 0:
		cout<<"\n"<<GetNameOfEntity(wife->ID())<<" : 바닥을 닦는다.";
		break;

	case 1:
		cout<<"\n"<<GetNameOfEntity(wife->ID())<<" : 접시를 닦는다.";
		break;

	case 2:
		cout<<"\n"<<GetNameOfEntity(wife->ID())<<" : 잠자리를 준비한다.";
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
	cout<<"\n"<<GetNameOfEntity(wife->ID())<<" : 화장실로 걸어간다.";
	cout<<"\n"<<GetNameOfEntity(wife->ID())<<" : 깨끗이 소변을 봐야겠구나.";
}


void VisitBathroom::Execute(MinersWife* wife)
{
	cout<<"\n"<<GetNameOfEntity(wife->ID())<<" : 아~! 시원하다!";

	wife->GetFSM()->RevertToPreviousState();
}

void VisitBathroom::Exit(MinersWife* wife, bool isRecMsg)
{
	if(!isRecMsg)
	{
		cout<<"\n"<<GetNameOfEntity(wife->ID())<<" : 화장실에서 나온다.";
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
		cout<<"\n"<<GetNameOfEntity(wife->ID())<<" : 국을 오븐에 넣는다.";

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
	cout<<"\n"<<GetNameOfEntity(wife->ID())<<" : 밥을 차려 놓고 안달복달한다.";
}

void CookStew::Exit(MinersWife* wife, bool isRecMsg)
{
	if(!isRecMsg)
	{
		return;
	}

	SetTextColor(FOREGROUND_GREEN|FOREGROUND_INTENSITY);
	cout<<"\n"<<GetNameOfEntity(wife->ID())<<" : 식탁위에 국을 올려 놓는다.";
}


bool CookStew::OnMessage(MinersWife* wife, const Telegram& msg)
{
	SetTextColor(BACKGROUND_RED|FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE);

	switch(msg.Msg)
	{
	case Msg_StewReady:
		{
			cout<<"\n"<<GetNameOfEntity(wife->ID())<<"이(가) 시간:"<<Clock->GetTickCount()<<"에 수신한 메시지.";

			SetTextColor(FOREGROUND_GREEN|FOREGROUND_INTENSITY);
			cout<<"\n"<<GetNameOfEntity(wife->ID())<<" : 국이 준비가됐군요! 듭시다.";

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