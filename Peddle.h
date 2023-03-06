#ifndef _PEDDLE_H
#define _PEDDLE_H

#include <string>

#include "BaseGameEntity.h"
#include "Locations.h"
#include "PeddleOwnedStates.h"
#include "ConsoleUtils.h"
#include "StateMachine.h"
#include "Utils.h"	//RandFloat, RandInt, switch

template <class entity_type> class State;
struct Telegram;

class Peddle : public BaseGameEntity
{
private:
	// State의 인스턴스를 가리키는 포인터
	StateMachine<Peddle>* m_pStateMachine;

	// Peddle가 현재 위치하고 있는 장소
	location_type m_Location;

	// 현재 miner와 거래를 하고 있는지
	bool m_bisSale;

public:
	Peddle(int ID);
	~Peddle(){delete m_pStateMachine;}

	// 이것은 반드시 설치되어야 한다.
	void Update();

	// 현재 상태를 새로운 상태로 변화시킨다.
	//void ChangeState(State* pNewState);
	StateMachine<Peddle>*  GetFSM()const{return m_pStateMachine;}

	location_type	Location()const{return m_Location;}
	void			ChangeLocation(const location_type loc){m_Location=loc;}

	bool          IsSale()const{return m_bisSale;}
	void          SetIsSale(const bool val){m_bisSale = val;}

	virtual bool  HandleMessage(const Telegram& msg);
};

#endif