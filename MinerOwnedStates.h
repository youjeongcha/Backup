#ifndef MINER_OWNED_STATES_H
#define MINER_OWNED_STATES_H

#include "State.h"

class Miner;
struct Telegram;

class MinerGlobalState : public State<Miner>
{
private:
	MinerGlobalState(){}
	MinerGlobalState(const MinerGlobalState&);
	MinerGlobalState& operator=(const MinerGlobalState&);

public:
	// 蜡老 按眉
	static MinerGlobalState* Instance();

	virtual void Enter(Miner* miner){}

	virtual void Execute(Miner* miner){}

	virtual void Exit(Miner* miner, bool isRecMsg){}

	virtual bool OnMessage(Miner* agent, const Telegram& msg);
};

class EnterMineAndDigForNugget : public State<Miner>
{
private:
	EnterMineAndDigForNugget(){}

	//copy ctor and assignment should be private
	EnterMineAndDigForNugget(const EnterMineAndDigForNugget&);
	EnterMineAndDigForNugget& operator=(const EnterMineAndDigForNugget&);

public:
	// 蜡老 按眉
	static EnterMineAndDigForNugget* Instance();

	virtual void Enter(Miner* miner);

	virtual void Execute(Miner* miner);

	virtual void Exit(Miner* miner, bool isRecMsg);

	virtual bool OnMessage(Miner* agent, const Telegram& msg);
};

class VisitBankAndDepositGold : public State<Miner>
{
private:

	VisitBankAndDepositGold(){}

	//copy ctor and assignment should be private
	VisitBankAndDepositGold(const VisitBankAndDepositGold&);
	VisitBankAndDepositGold& operator=(const VisitBankAndDepositGold&);

public:

	// 蜡老 按眉
	static VisitBankAndDepositGold* Instance();

	virtual void Enter(Miner* miner);

	virtual void Execute(Miner* miner);

	virtual void Exit(Miner* miner, bool isRecMsg);

	virtual bool OnMessage(Miner* agent, const Telegram& msg);
};

class GoHomeAndSleepTilRested : public State<Miner>
{
private:

	GoHomeAndSleepTilRested(){}

	//copy ctor and assignment should be private
	GoHomeAndSleepTilRested(const GoHomeAndSleepTilRested&);
	GoHomeAndSleepTilRested& operator=(const GoHomeAndSleepTilRested&);

public:

	// 蜡老 按眉
	static GoHomeAndSleepTilRested* Instance();

	virtual void Enter(Miner* miner);

	virtual void Execute(Miner* miner);

	virtual void Exit(Miner* miner, bool isRecMsg);

	virtual bool OnMessage(Miner* agent, const Telegram& msg);
};

class QuenchThirst : public State<Miner>
{
private:

	QuenchThirst(){}

	//copy ctor and assignment should be private
	QuenchThirst(const QuenchThirst&);
	QuenchThirst& operator=(const QuenchThirst&);

public:

	// 蜡老 按眉
	static QuenchThirst* Instance();

	virtual void Enter(Miner* miner);

	virtual void Execute(Miner* miner);

	virtual void Exit(Miner* miner, bool isRecMsg);

	virtual bool OnMessage(Miner* agent, const Telegram& msg);
};

class EatStew : public State<Miner>
{
private:

	EatStew(){}

	//copy ctor and assignment should be private
	EatStew(const EatStew&);
	EatStew& operator=(const EatStew&);

public:

	//this is a singleton
	static EatStew* Instance();

	virtual void Enter(Miner* miner);

	virtual void Execute(Miner* miner);

	virtual void Exit(Miner* miner, bool isRecMsg);

	virtual bool OnMessage(Miner* agent, const Telegram& msg);
};

class MeetPeddle : public State<Miner>
{
private:
	MeetPeddle(){}
	MeetPeddle(const MeetPeddle&);
	MeetPeddle& operator=(const MeetPeddle&);

public:
	static MeetPeddle* Instance();

	virtual void Enter(Miner* miner);

	virtual void Execute(Miner* miner);

	virtual void Exit(Miner* miner, bool isRecMsg){}

	virtual bool OnMessage(Miner* agent, const Telegram& msg);
};

#endif