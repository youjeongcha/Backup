#include "MinerOwnedStates.h"
#include "Miner.h"
#include "Locations.h"
#include "MessageDispatcher.h"
#include "MessageTypes.h"
#include "CrudeTimer.h"
#include "EntityNames.h"
//#include "FrameCounter.h"

#include <iostream>
using std::cout;

//define this to output to a file
#ifdef TEXTOUTPUT
#include <fstream>
extern std::ofstream os;
#define cout os
#endif

MinerGlobalState* MinerGlobalState::Instance()
{
	static MinerGlobalState instance;

	return &instance;
}

bool MinerGlobalState::OnMessage(Miner* pMiner, const Telegram& msg)
{
	switch(msg.Msg)
	{
	case Msg_SaleIsMiner:
		SetTextColor(BACKGROUND_RED | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
		cout<<"\n"<<GetNameOfEntity(pMiner->ID())<<"이(가) 시간:"<<Clock->GetTickCount()<<"에 수신한 메시지.";

		SetTextColor(FOREGROUND_BLUE| FOREGROUND_RED | FOREGROUND_GREEN);
		cout<<"\n"<<GetNameOfEntity(pMiner->ID())<<" : "<<"그럼 어디 구경이나 해봅시다.";

		return true;
	}
	return false;
}

EnterMineAndDigForNugget* EnterMineAndDigForNugget::Instance()
{
	static EnterMineAndDigForNugget instance;

	return &instance;
}

void EnterMineAndDigForNugget::Enter(Miner* pMiner)
{
	// 광부가 아직 금광에 있지 않다면,
	// 반드시 금광에 가기 위해 위치를 바꿔야만 한다.
	if(pMiner->Location() != goldmine)
	{
		cout<<"\n"<<GetNameOfEntity(pMiner->ID())<<" : "<<"금광으로 걸어간다.";	

		pMiner->ChangeLocation(goldmine);
	}
}

void EnterMineAndDigForNugget::Execute(Miner* pMiner)
{
	// 광부는 MaxNuggets보다 많이 운반하게 될 때까지 금을 파낸다.
	// 파는 도중 목이 마르게 되면 하던 일을 중단하고
	//위스키를 마시기 위해 술집으로 가도록 상태를 바꾼다.
	pMiner->AddToGoldCarried(1);

	// 땅을 파는 것은 어려운 일이다.
	pMiner->IncreaseFatigue();

	cout<<"\n"<<GetNameOfEntity(pMiner->ID())<<" : "<<"금덩어리를 집는다.";

	// 금이 충분히 많으면, 은행으로 가서 예금한다.
	if(pMiner->PocketsFull())
	{
		pMiner->GetFSM()->ChangeState(VisitBankAndDepositGold::Instance());
	}

	// 갈증이 나면 가서 위스키를 마신다.
	if(pMiner->Thirsty())
	{
		// 전보를 받은 것은 아니나
		// 주머니가 가득차서 금광을 나가는 것이아니기 때문에
		// "나는 주머니에 금덩어리를 한가득 채우고 금광을 떠난다."
		// 출력하지 않기 위해서 isRecMsg의 값을 TRUE로 준다.
		pMiner->GetFSM()->ChangeState(QuenchThirst::Instance(), TRUE);
	}
}

void EnterMineAndDigForNugget::Exit(Miner* pMiner, bool isRecMsg)
{
	cout<<"\n"<<GetNameOfEntity(pMiner->ID())<<" : "<<"주머니에는 현재, 총 "<<pMiner->GoldCarried()<<"개의 금덩어리가 있다.";

	if(!isRecMsg)
	{
		cout<<"\n"<<GetNameOfEntity(pMiner->ID())<<" : "<<"나는 주머니에 금덩어리를 한가득 채우고 금광을 떠난다.";		
	}
}

bool EnterMineAndDigForNugget::OnMessage(Miner* pMiner, const Telegram& msg)
{
	//send msg to global message handler
	return false;
}


VisitBankAndDepositGold* VisitBankAndDepositGold::Instance()
{
	static VisitBankAndDepositGold instance;

	return &instance;
}


void VisitBankAndDepositGold::Enter(Miner* pMiner)
{
	if(RandFloat() < MEET_PROBABILITY && !pMiner->isBuy())
	{
		Dispatch->DispatchMessages(SEND_MSG_IMMEDIATELY,        //time delay
			pMiner->ID(),										//sender ID
			ent_Peddle,											//receiver ID
			Msg_MeetPeddle,										//msg
			(void*)NO_ADDITIONAL_INFO);

		pMiner->SetBuy(TRUE);
		pMiner->GetFSM()->ChangeState(MeetPeddle::Instance(), TRUE);
	}
	else
	{
		//on entry the miner makes sure he is located at the bank
		if (pMiner->Location() != bank)
		{
			cout<<"\n"<<GetNameOfEntity(pMiner->ID())<<" : "<<"은행으로 간다. 네, 고객님.";

			pMiner->ChangeLocation(bank);
		}
	}
}

void VisitBankAndDepositGold::Execute(Miner* pMiner)
{

	//deposit the gold
	pMiner->AddToWealth(pMiner->GoldCarried());

	pMiner->SetGoldCarried(0);

	cout<<"\n"<<GetNameOfEntity(pMiner->ID())<<" : "<<"금을 맡긴다. 총 저축량은 이제 "<<pMiner->Wealth()<<"이다.";

	//wealthy enough to have a well earned rest?
	if (pMiner->Wealth() >= ComfortLevel)
	{
		cout<<"\n"<<GetNameOfEntity(pMiner->ID())<<" : "<<"우후! 이제 충분히 부자가 되었다. 나의 귀여운 아내에게로 돌아가자.";

		pMiner->GetFSM()->ChangeState(GoHomeAndSleepTilRested::Instance());
	}
	//otherwise get more gold
	else 
	{
		pMiner->GetFSM()->ChangeState(EnterMineAndDigForNugget::Instance());
	}
}

void VisitBankAndDepositGold::Exit(Miner* pMiner, bool isRecMsg)
{
	if(!isRecMsg)
	{
		cout<<"\n"<<GetNameOfEntity(pMiner->ID())<<" : "<<"은행을 떠난다.";
	}
}

bool VisitBankAndDepositGold::OnMessage(Miner* pMiner, const Telegram& msg)
{
	//send msg to global message handler
	return false;
}


//----------------------------------------methods for GoHomeAndSleepTilRested

GoHomeAndSleepTilRested* GoHomeAndSleepTilRested::Instance()
{
	static GoHomeAndSleepTilRested instance;

	return &instance;
}

void GoHomeAndSleepTilRested::Enter(Miner* pMiner)
{
	if(RandFloat() < MEET_PROBABILITY && !pMiner->isBuy())
	{
		Dispatch->DispatchMessages(SEND_MSG_IMMEDIATELY,        //time delay
			pMiner->ID(),										//sender ID
			ent_Peddle,											//receiver ID
			Msg_MeetPeddle,										//msg
			(void*)NO_ADDITIONAL_INFO);

		pMiner->SetBuy(TRUE);
		pMiner->GetFSM()->ChangeState(MeetPeddle::Instance(), TRUE);
	}
	else
	{
		if (pMiner->Location() != shack)
		{
			cout<<"\n"<<GetNameOfEntity(pMiner->ID())<<" : "<<"집으로 걸어간다.";

			Dispatch->DispatchMessages(SEND_MSG_IMMEDIATELY,        //time delay
			pMiner->ID(),										//sender ID
			ent_Elsa,											//receiver ID
			Msg_HiHoneyImHome,										//msg
			(void*)NO_ADDITIONAL_INFO);			

			pMiner->ChangeLocation(shack);
		}
	}
}

void GoHomeAndSleepTilRested::Execute(Miner* pMiner)
{ 
	//if miner is not fatigued start to dig for nuggets again.
	if (!pMiner->Fatigued())
	{
		if(pMiner->GetFatigued() != 0)
			cout<<"\n"<<GetNameOfEntity(pMiner->ID())<<" : "<<"정말 환상적인 낮잠이었구나! 금을 더 캐야 할 시간이다.";

		pMiner->GetFSM()->ChangeState(EnterMineAndDigForNugget::Instance());
	}
	else 
	{
		//sleep
		pMiner->DecreaseFatigue();

		cout<<"\n"<<GetNameOfEntity(pMiner->ID())<<" : "<<"쿨쿨... ";
	} 
}

void GoHomeAndSleepTilRested::Exit(Miner* pMiner, bool isRecMsg)
{
	if(!isRecMsg)
	{
		cout<<"\n"<<GetNameOfEntity(pMiner->ID())<<" : "<<"집에서 나간다.";
		pMiner->SetBuy(FALSE);

		//if(RandFloat() < MEET_PROBABILITY)
		//{
		//	Dispatch->DispatchMessages(SEND_MSG_IMMEDIATELY,        //time delay
		//		pMiner->ID(),										//sender ID
		//		ent_Peddle,											//receiver ID
		//		Msg_MeetPeddle,										//msg
		//		NO_ADDITIONAL_INFO);

		//	pMiner->GetFSM()->ChangeState(MeetPeddle::Instance(), TRUE);
		//}
	}
}

bool GoHomeAndSleepTilRested::OnMessage(Miner* pMiner, const Telegram& msg)
{
	SetTextColor(BACKGROUND_RED|FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE);

	switch(msg.Msg)
	{
	case Msg_StewReady:

		cout<<"\n"<<GetNameOfEntity(pMiner->ID())<<"이(가) 시간:"<<Clock->GetTickCount()<<"에 수신한 메시지.";

		SetTextColor(FOREGROUND_BLUE| FOREGROUND_RED | FOREGROUND_GREEN);

		cout<<"\n"<<GetNameOfEntity(pMiner->ID())<<" : 좋아요 여보, 내 곧 가리다!";

		pMiner->GetFSM()->ChangeState(EatStew::Instance(), TRUE);

		return true;
	}//end switch

	return false; //send message to global message handler
}


//------------------------------------------------methods for QuenchThirst

QuenchThirst* QuenchThirst::Instance()
{
	static QuenchThirst instance;

	return &instance;
}

void QuenchThirst::Enter(Miner* pMiner)
{
	if (pMiner->Location() != saloon)
	{    
		pMiner->ChangeLocation(saloon);

		cout<<"\n"<<GetNameOfEntity(pMiner->ID())<<" : "<<"목이 마르군! 술집으로 걸어간다.";
	}
}

void QuenchThirst::Execute(Miner* pMiner)
{
	if (pMiner->Thirsty())
	{
		pMiner->BuyAndDrinkAWhiskey(pMiner);
		cout<<"\n"<<GetNameOfEntity(pMiner->ID())<<" : "<<"저게 홀짝홀짝 마시기에 대단히 좋은 술이군.";

		pMiner->GetFSM()->ChangeState(EnterMineAndDigForNugget::Instance());
	}
	else 
	{
		cout<<"\nERROR!\nERROR!\nERROR!";
	} 
}

void QuenchThirst::Exit(Miner* pMiner, bool isRecMsg)
{ 
	if(!isRecMsg)
	{
		cout<<"\n"<<GetNameOfEntity(pMiner->ID())<<" : "<<"술집을 떠난다, 기분도 좋다.";

		//if(RandFloat() < MEET_PROBABILITY)
		//{
		//	Dispatch->DispatchMessages(SEND_MSG_IMMEDIATELY,        //time delay
		//		pMiner->ID(),										//sender ID
		//		ent_Peddle,											//receiver ID
		//		Msg_MeetPeddle,										//msg
		//		NO_ADDITIONAL_INFO);

		//	pMiner->GetFSM()->ChangeState(MeetPeddle::Instance(), TRUE);
		//}
	}
}

bool QuenchThirst::OnMessage(Miner* pMiner, const Telegram& msg)
{
	//send msg to global message handler
	return false;
}

//------------------------------------------------------------------------EatStew

EatStew* EatStew::Instance()
{
	static EatStew instance;

	return &instance;
}


void EatStew::Enter(Miner* pMiner)
{
	cout<<"\n"<<GetNameOfEntity(pMiner->ID())<<" : "<<"냄새가 정말 좋구려, 여보!";
}

void EatStew::Execute(Miner* pMiner)
{
	cout<<"\n"<<GetNameOfEntity(pMiner->ID())<<" : "<<"맛도 정말 좋군!";

	pMiner->GetFSM()->RevertToPreviousState();
}

void EatStew::Exit(Miner* pMiner, bool isRecMsg)
{
	if(!isRecMsg)
	{
		cout<<"\n"<<GetNameOfEntity(pMiner->ID())<<" : "<<"고마워 여보.";
		cout<<"\n"<<GetNameOfEntity(pMiner->ID())<<" : "<<"하던일을 다시하는 것이 좋겠군.";
	}
}


bool EatStew::OnMessage(Miner* pMiner, const Telegram& msg)
{
	//send msg to global message handler
	return false;
}


MeetPeddle* MeetPeddle::Instance()
{
	static MeetPeddle instance;

	return &instance;
}

void MeetPeddle::Enter(Miner* pMiner)
{
	Dispatch->DispatchMessages(RandInt(0,5)+1.5,        //time delay
		pMiner->ID(),				//sender ID
		ent_Peddle,					//receiver ID
		Msg_SaleIsMiner,			//msg
		(void*)NO_ADDITIONAL_INFO);
}

void MeetPeddle::Execute(Miner* pMiner)
{
	cout<<"\n"<<GetNameOfEntity(pMiner->ID())<<" : "<<". . .";
}

bool MeetPeddle::OnMessage(Miner* pMiner, const Telegram& msg)
{
	switch(msg.Msg)
	{
	case Msg_LeaveMiner:
		{
			SetTextColor(FOREGROUND_BLUE| FOREGROUND_RED | FOREGROUND_GREEN);
			cout<<"\n"<<GetNameOfEntity(pMiner->ID())<<" : "<<"그럼 수고하쇼.";

			pMiner->GetFSM()->RevertToPreviousState();
		}
		return true;
	}
	return false;
}