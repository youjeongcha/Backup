#ifndef _MINER_H_
#define _MINER_H_

#include <string>
#include <cassert>
#include <iostream>

#include"BaseGameEntity.h"
#include"Locations.h"
#include "ConsoleUtils.h"
#include "MinerOwnedStates.h"
#include "StateMachine.h"
#include "Utils.h"

template <class entity_type> class State;
struct Telegram;

const int ComfortLevel       = 5;
const int MaxNuggets         = 3;
const int ThirstLevel        = 5;
const int TirednessThreshold = 5;

const float MEET_PROBABILITY = 0.3f;

class Miner : public BaseGameEntity
{
private:
	// State�� �ν��Ͻ��� ����Ű�� ������
	StateMachine<Miner>* m_pStateMachine;

	// miner�� ���� ��ġ�ϰ� �ִ� ���
	location_type m_Location;

	// �ָӴϿ� �ݵ���� ���� �ִ����� ��Ÿ����.
	int m_iGoldCarried;
	// ���࿡ ���� �󸶳� �����ϰ� �ִ����� ��Ÿ����.
	int m_iMoneyInBank;
	// ���� Ŭ���� miner�� �� �񸶸��� ��Ÿ����.
	int m_iThirst;
	// ���� Ŭ���� miner�� �� �ǰ����� ��Ÿ����.
	int m_iFatigue;

	bool Buy;

public:
	Miner(int ID);
	~Miner(){delete m_pStateMachine;}

	// �̰��� �ݵ�� ��ġ�Ǿ�� �Ѵ�.
	void Update();

	// ���� ���¸� ���ο� ���·� ��ȭ��Ų��.
	//void ChangeState(State* pNewState);
	StateMachine<Miner>*  GetFSM()const{return m_pStateMachine;}

	location_type	Location()const{return m_Location;}
	void			ChangeLocation(const location_type loc){m_Location=loc;}

	int				GoldCarried()const{return m_iGoldCarried;}
	void			SetGoldCarried(const int val){m_iGoldCarried = val;}
	void			AddToGoldCarried(const int val);
	bool			PocketsFull()const{return m_iGoldCarried >= MaxNuggets;}

	int				Wealth()const{return m_iMoneyInBank;}
	void			SetWealth(const int val){m_iMoneyInBank = val;}
	void			AddToWealth(const int val);

	bool			Thirsty()const;
	bool			Fatigued()const;
	int				GetFatigued()const{return m_iFatigue;}

	void			BuyAndDrinkAWhiskey(Miner* pMiner);
	void			DecreaseFatigue(){m_iFatigue -= 1;}
	void			IncreaseFatigue(){m_iFatigue += 1;}

	bool          isBuy()const{return Buy;}
	void          SetBuy(const bool val){Buy = val;}

	virtual bool  HandleMessage(const Telegram& msg);
};

#endif