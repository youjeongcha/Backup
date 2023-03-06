#include "Peddle.h"

Peddle::Peddle(int ID) : BaseGameEntity(ID),
						 m_Location(shack),
						 m_bisSale(false)
{
	m_pStateMachine = new StateMachine<Peddle>(this);
	m_pStateMachine->SetCurrentState(DoWork::Instance());
	m_pStateMachine->SetGlobalState(PeddleGlobalState::Instance());
}

void Peddle::Update()
{
	SetTextColor(BACKGROUND_INTENSITY | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
	m_pStateMachine->Update();
}

bool Peddle::HandleMessage(const Telegram& msg)
{
	return m_pStateMachine->HandleMessage(msg);
}