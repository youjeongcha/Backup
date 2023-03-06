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
	// 이 인스턴스를 소유하는 에이전트를 가리키는 포인터
	T*			m_pOwner;
	State<T>*	m_pCurrentState;
	// 에이전트가 속해 있었던 마지막 상태의 기록
	State<T>*	m_pPreviousState;
	// 이 상태 논리는 FSM이 갱신될 때마다 호출된다.
	State<T>*	m_pGlobalState;

public:
	StateMachine(T* owner):m_pOwner(owner),
                                   m_pCurrentState(NULL),
                                   m_pPreviousState(NULL),
                                   m_pGlobalState(NULL) {}
	 virtual ~StateMachine(){}

	// FSM을 초기화하기 위해 다음 함수들을 사용한다.
	void SetCurrentState(State<T>* s){m_pCurrentState = s;}	
	void SetPreviousState(State<T>* s){m_pPreviousState = s;}
	void SetGlobalState(State<T>* s) {m_pGlobalState = s;}

	// FSM을 갱신하기 위해 이것을 호출한다.
	void  Update()const
	{
		// 전역 상태가 존재하면, 그것의 execute 함수를 호출.
		if(m_pGlobalState)   m_pGlobalState->Execute(m_pOwner);

		// 현재 상태에 대해서 동일하게.
		if (m_pCurrentState) m_pCurrentState->Execute(m_pOwner);
	}

	// 새로운 상태로 변화시킨다.
	void ChangeState(State<T>* pNewState, bool isRecMsg = FALSE)
	{
		 assert(pNewState &&
			 "<StateMachine::ChangeState> : trying to assign NULL state to current");

		 // 이전 상태의 기록을 유지한다.
		 m_pPreviousState = m_pCurrentState;
		 // 기존 상태의 exit 함수를 호출한다.
		 m_pCurrentState->Exit(m_pOwner, isRecMsg);
		 // 상태를 새로운 상태로 변화시킨다.
		 m_pCurrentState = pNewState;
		 // 새로운 상태의 enter 함수를 호출한다.
		 m_pCurrentState->Enter(m_pOwner);
	}

	// 상태를 이전 상태로 다시 변화시킨다.
	void RevertToPreviousState()
	{
		ChangeState(m_pPreviousState);
	}

	// 접근자(accessor).
	State<T>*  CurrentState()  const{return m_pCurrentState;}	
	State<T>*  PreviousState() const{return m_pPreviousState;}
	State<T>*  GlobalState()   const{return m_pGlobalState;}

	// 만약 현재 상태의 형식이
	//매개변수로 넘겨받은 클래스의 형식과 같다면 참값을 반환.
	bool isInState(const State<T>& st)const
	{
		if(typeid(*m_pCurrentState) == typeid(st))
			return true;

		return false;
	}

	bool HandleMessage(const Telegram& msg)const
	{
		// 우선 현재 상태가 유효하고 메시지를 처리할 수 있는지를 알아본다.
		if(m_pCurrentState && m_pCurrentState->OnMessage(m_pOwner, msg))
		{
			return true;
		}

		// 처리할 수 없고 전역 상태가 설치되어 있다면, 메시지를 전역 상태로 보낸다.
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