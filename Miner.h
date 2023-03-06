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
	// State의 인스턴스를 가리키는 포인터
	StateMachine<Miner>* m_pStateMachine;

	// miner가 현재 위치하고 있는 장소
	location_type m_Location;

	// 주머니에 금덩어리를 갖고 있는지를 나타낸다.
	int m_iGoldCarried;
	// 은행에 돈을 얼마나 저축하고 있는지를 나타낸다.
	int m_iMoneyInBank;
	// 값이 클수록 miner가 더 목마름을 나타낸다.
	int m_iThirst;
	// 값이 클수록 miner가 더 피곤함을 나타낸다.
	int m_iFatigue;

	bool Buy;

public:
	Miner(int ID);
	~Miner(){delete m_pStateMachine;}

	// 이것은 반드시 설치되어야 한다.
	void Update();

	// 현재 상태를 새로운 상태로 변화시킨다.
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