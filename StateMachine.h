#ifndef _STATE_MACHINE_H
#define _STATE_MACHINE_H

#include <cassert>
#include <string>

#include "StateMachine.h"
#include "Telegram.h"

template<typename T>
class StateMachine
{
private:
	// �� �ν��Ͻ��� �����ϴ� ������Ʈ�� ����Ű�� ������
	T*			m_pOwner;
	State<T>*	m_pCurrentState;
	// ������Ʈ�� ���� �־��� ������ ������ ���
	State<T>*	m_pPreviousState;
	// �� ���� ���� FSM�� ���ŵ� ������ ȣ��ȴ�.
	State<T>*	m_pGlobalState;

public:
	StateMachine(T* owner):m_pOwner(owner),
                                   m_pCurrentState(NULL),
                                   m_pPreviousState(NULL),
                                   m_pGlobalState(NULL) {}
	 virtual ~StateMachine(){}

	// FSM�� �ʱ�ȭ�ϱ� ���� ���� �Լ����� ����Ѵ�.
	void SetCurrentState(State<T>* s){m_pCurrentState = s;}	
	void SetPreviousState(State<T>* s){m_pPreviousState = s;}
	void SetGlobalState(State<T>* s) {m_pGlobalState = s;}

	// FSM�� �����ϱ� ���� �̰��� ȣ���Ѵ�.
	void  Update()const
	{
		// ���� ���°� �����ϸ�, �װ��� execute �Լ��� ȣ��.
		if(m_pGlobalState)   m_pGlobalState->Execute(m_pOwner);

		// ���� ���¿� ���ؼ� �����ϰ�.
		if (m_pCurrentState) m_pCurrentState->Execute(m_pOwner);
	}

	// ���ο� ���·� ��ȭ��Ų��.
	void ChangeState(State<T>* pNewState, bool isRecMsg = FALSE)
	{
		 assert(pNewState &&
			 "<StateMachine::ChangeState> : trying to assign NULL state to current");

		 // ���� ������ ����� �����Ѵ�.
		 m_pPreviousState = m_pCurrentState;
		 // ���� ������ exit �Լ��� ȣ���Ѵ�.
		 m_pCurrentState->Exit(m_pOwner, isRecMsg);
		 // ���¸� ���ο� ���·� ��ȭ��Ų��.
		 m_pCurrentState = pNewState;
		 // ���ο� ������ enter �Լ��� ȣ���Ѵ�.
		 m_pCurrentState->Enter(m_pOwner);
	}

	// ���¸� ���� ���·� �ٽ� ��ȭ��Ų��.
	void RevertToPreviousState()
	{
		ChangeState(m_pPreviousState);
	}

	// ������(accessor).
	State<T>*  CurrentState()  const{return m_pCurrentState;}	
	State<T>*  PreviousState() const{return m_pPreviousState;}
	State<T>*  GlobalState()   const{return m_pGlobalState;}

	// ���� ���� ������ ������
	//�Ű������� �Ѱܹ��� Ŭ������ ���İ� ���ٸ� ������ ��ȯ.
	bool isInState(const State<T>& st)const
	{
		if(typeid(*m_pCurrentState) == typeid(st))
			return true;

		return false;
	}

	bool HandleMessage(const Telegram& msg)const
	{
		// �켱 ���� ���°� ��ȿ�ϰ� �޽����� ó���� �� �ִ����� �˾ƺ���.
		if(m_pCurrentState && m_pCurrentState->OnMessage(m_pOwner, msg))
		{
			return true;
		}

		// ó���� �� ���� ���� ���°� ��ġ�Ǿ� �ִٸ�, �޽����� ���� ���·� ������.
		if(m_pGlobalState && m_pGlobalState->OnMessage(m_pOwner, msg))
		{
			return true;
		}

		return false;
	}

	std::string GetNameOfCurrentState()const
	{
		std::string s(typeid(*m_pCurrentState).name());

		//remove the 'class ' part from the front of the string
		if (s.size() > 5)
		{
			s.erase(0, 6);
		}

		return s;
	}
};

#endif