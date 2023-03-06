#ifndef PEDDLE_OWNED_STATES_H
#define PEDDLE_OWNED_STATES_H

#include "State.h"

class Peddle;

class PeddleGlobalState : public State<Peddle>
{
private:
	PeddleGlobalState(){}
	PeddleGlobalState(const PeddleGlobalState&);
	PeddleGlobalState& operator=(const PeddleGlobalState&);

public:
	// ���� ��ü
	static PeddleGlobalState* Instance();

	virtual void Enter(Peddle* peddle){}

	virtual void Execute(Peddle* peddle){}

	virtual void Exit(Peddle* peddle, bool isRecMsg){}

	virtual bool OnMessage(Peddle* agent, const Telegram& msg);
};

class DoWork : public State<Peddle>
{
private:
	DoWork(){}
	DoWork(const DoWork&);
	DoWork& operator=(const DoWork&);

public:
	// ���� ��ü
	static DoWork* Instance();

	virtual void Enter(Peddle* peddle){}

	virtual void Execute(Peddle* peddle);

	virtual void Exit(Peddle* peddle, bool isRecMsg);

	virtual bool OnMessage(Peddle* agent, const Telegram& msg);
};

class MeetMiner : public State<Peddle>
{
private:
	MeetMiner(){}
	MeetMiner(const MeetMiner&);
	MeetMiner& operator=(const MeetMiner&);

public:
	//���� ��ü
	static MeetMiner* Instance();

	virtual void Enter(Peddle* peddle);

	virtual void Execute(Peddle* peddle);

	virtual void Exit(Peddle* peddle, bool isRecMsg);

	virtual bool OnMessage(Peddle* agent, const Telegram& msg);
};

#endif