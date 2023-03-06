#include "Miner.h"
#include "EntityNames.h"

#include <iostream>
using std::cout;

Miner::Miner(int id):BaseGameEntity(id),
	m_Location(shack),
	m_iGoldCarried(0),
	m_iMoneyInBank(0),
	m_iThirst(0),
	m_iFatigue(0),
	Buy(FALSE)
{
	m_pStateMachine = new StateMachine<Miner>(this);
	
	//m_pStateMachine->SetGlobalState(MinerGlobalState::Instance());
	m_pStateMachine->SetCurrentState(GoHomeAndSleepTilRested::Instance());
}

void Miner::Update()
{
	SetTextColor(FOREGROUND_BLUE| FOREGROUND_RED | FOREGROUND_GREEN);

	m_pStateMachine->Update();

	m_iThirst += 1;
}

void Miner::AddToGoldCarried(const int val)
{
	m_iGoldCarried += val;

	if (m_iGoldCarried < 0) m_iGoldCarried = 0;
}

void Miner::AddToWealth(const int val)
{
	m_iMoneyInBank += val;

	if (m_iMoneyInBank < 0) m_iMoneyInBank = 0;
}

bool Miner::Thirsty()const
{
	if (m_iThirst >= ThirstLevel){return true;}

	return false;
}

bool Miner::Fatigued()const
{
	if (m_iFatigue > TirednessThreshold)
	{
		return true;
	}

	return false;
}

void Miner::BuyAndDrinkAWhiskey(Miner* pMiner)
{
	m_iThirst = 0;

	if(m_iGoldCarried < 2)
	{
		m_iMoneyInBank-=2;
		cout<<"\n"<<GetNameOfEntity(pMiner->ID())<<" : "<<"���� ���ñ� ���� ���࿡ �����ص� ��, 2���� �ݵ���� ����.";
	}
	else
	{
		m_iGoldCarried-=2;
		cout<<"\n"<<GetNameOfEntity(pMiner->ID())<<" : "<<"���� ���ñ� ���� �ָӴϿ��� 2���� �ݵ���� ����.";
	}
}

bool Miner::HandleMessage(const Telegram& msg)
{
	return m_pStateMachine->HandleMessage(msg);
}