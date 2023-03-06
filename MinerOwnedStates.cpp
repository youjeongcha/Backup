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
		cout<<"\n"<<GetNameOfEntity(pMiner->ID())<<"��(��) �ð�:"<<Clock->GetTickCount()<<"�� ������ �޽���.";

		SetTextColor(FOREGROUND_BLUE| FOREGROUND_RED | FOREGROUND_GREEN);
		cout<<"\n"<<GetNameOfEntity(pMiner->ID())<<" : "<<"�׷� ��� �����̳� �غ��ô�.";

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
	// ���ΰ� ���� �ݱ��� ���� �ʴٸ�,
	// �ݵ�� �ݱ��� ���� ���� ��ġ�� �ٲ�߸� �Ѵ�.
	if(pMiner->Location() != goldmine)
	{
		cout<<"\n"<<GetNameOfEntity(pMiner->ID())<<" : "<<"�ݱ����� �ɾ��.";	

		pMiner->ChangeLocation(goldmine);
	}
}

void EnterMineAndDigForNugget::Execute(Miner* pMiner)
{
	// ���δ� MaxNuggets���� ���� ����ϰ� �� ������ ���� �ĳ���.
	// �Ĵ� ���� ���� ������ �Ǹ� �ϴ� ���� �ߴ��ϰ�
	//����Ű�� ���ñ� ���� �������� ������ ���¸� �ٲ۴�.
	pMiner->AddToGoldCarried(1);

	// ���� �Ĵ� ���� ����� ���̴�.
	pMiner->IncreaseFatigue();

	cout<<"\n"<<GetNameOfEntity(pMiner->ID())<<" : "<<"�ݵ���� ���´�.";

	// ���� ����� ������, �������� ���� �����Ѵ�.
	if(pMiner->PocketsFull())
	{
		pMiner->GetFSM()->ChangeState(VisitBankAndDepositGold::Instance());
	}

	// ������ ���� ���� ����Ű�� ���Ŵ�.
	if(pMiner->Thirsty())
	{
		// ������ ���� ���� �ƴϳ�
		// �ָӴϰ� �������� �ݱ��� ������ ���̾ƴϱ� ������
		// "���� �ָӴϿ� �ݵ���� �Ѱ��� ä��� �ݱ��� ������."
		// ������� �ʱ� ���ؼ� isRecMsg�� ���� TRUE�� �ش�.
		pMiner->GetFSM()->ChangeState(QuenchThirst::Instance(), TRUE);
	}
}

void EnterMineAndDigForNugget::Exit(Miner* pMiner, bool isRecMsg)
{
	cout<<"\n"<<GetNameOfEntity(pMiner->ID())<<" : "<<"�ָӴϿ��� ����, �� "<<pMiner->GoldCarried()<<"���� �ݵ���� �ִ�.";

	if(!isRecMsg)
	{
		cout<<"\n"<<GetNameOfEntity(pMiner->ID())<<" : "<<"���� �ָӴϿ� �ݵ���� �Ѱ��� ä��� �ݱ��� ������.";		
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
			cout<<"\n"<<GetNameOfEntity(pMiner->ID())<<" : "<<"�������� ����. ��, ����.";

			pMiner->ChangeLocation(bank);
		}
	}
}

void VisitBankAndDepositGold::Execute(Miner* pMiner)
{

	//deposit the gold
	pMiner->AddToWealth(pMiner->GoldCarried());

	pMiner->SetGoldCarried(0);

	cout<<"\n"<<GetNameOfEntity(pMiner->ID())<<" : "<<"���� �ñ��. �� ���෮�� ���� "<<pMiner->Wealth()<<"�̴�.";

	//wealthy enough to have a well earned rest?
	if (pMiner->Wealth() >= ComfortLevel)
	{
		cout<<"\n"<<GetNameOfEntity(pMiner->ID())<<" : "<<"����! ���� ����� ���ڰ� �Ǿ���. ���� �Ϳ��� �Ƴ����Է� ���ư���.";

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
		cout<<"\n"<<GetNameOfEntity(pMiner->ID())<<" : "<<"������ ������.";
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
			cout<<"\n"<<GetNameOfEntity(pMiner->ID())<<" : "<<"������ �ɾ��.";

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
			cout<<"\n"<<GetNameOfEntity(pMiner->ID())<<" : "<<"���� ȯ������ �����̾�����! ���� �� ĳ�� �� �ð��̴�.";

		pMiner->GetFSM()->ChangeState(EnterMineAndDigForNugget::Instance());
	}
	else 
	{
		//sleep
		pMiner->DecreaseFatigue();

		cout<<"\n"<<GetNameOfEntity(pMiner->ID())<<" : "<<"����... ";
	} 
}

void GoHomeAndSleepTilRested::Exit(Miner* pMiner, bool isRecMsg)
{
	if(!isRecMsg)
	{
		cout<<"\n"<<GetNameOfEntity(pMiner->ID())<<" : "<<"������ ������.";
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

		cout<<"\n"<<GetNameOfEntity(pMiner->ID())<<"��(��) �ð�:"<<Clock->GetTickCount()<<"�� ������ �޽���.";

		SetTextColor(FOREGROUND_BLUE| FOREGROUND_RED | FOREGROUND_GREEN);

		cout<<"\n"<<GetNameOfEntity(pMiner->ID())<<" : ���ƿ� ����, �� �� ������!";

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

		cout<<"\n"<<GetNameOfEntity(pMiner->ID())<<" : "<<"���� ������! �������� �ɾ��.";
	}
}

void QuenchThirst::Execute(Miner* pMiner)
{
	if (pMiner->Thirsty())
	{
		pMiner->BuyAndDrinkAWhiskey(pMiner);
		cout<<"\n"<<GetNameOfEntity(pMiner->ID())<<" : "<<"���� Ȧ¦Ȧ¦ ���ñ⿡ ����� ���� ���̱�.";

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
		cout<<"\n"<<GetNameOfEntity(pMiner->ID())<<" : "<<"������ ������, ��е� ����.";

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
	cout<<"\n"<<GetNameOfEntity(pMiner->ID())<<" : "<<"������ ���� ������, ����!";
}

void EatStew::Execute(Miner* pMiner)
{
	cout<<"\n"<<GetNameOfEntity(pMiner->ID())<<" : "<<"���� ���� ����!";

	pMiner->GetFSM()->RevertToPreviousState();
}

void EatStew::Exit(Miner* pMiner, bool isRecMsg)
{
	if(!isRecMsg)
	{
		cout<<"\n"<<GetNameOfEntity(pMiner->ID())<<" : "<<"���� ����.";
		cout<<"\n"<<GetNameOfEntity(pMiner->ID())<<" : "<<"�ϴ����� �ٽ��ϴ� ���� ���ڱ�.";
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
			cout<<"\n"<<GetNameOfEntity(pMiner->ID())<<" : "<<"�׷� �����ϼ�.";

			pMiner->GetFSM()->RevertToPreviousState();
		}
		return true;
	}
	return false;
}