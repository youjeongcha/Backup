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
	// State�� �ν��Ͻ��� ����Ű�� ������
	StateMachine<Peddle>* m_pStateMachine;

	// Peddle�� ���� ��ġ�ϰ� �ִ� ���
	location_type m_Location;

	// ���� miner�� �ŷ��� �ϰ� �ִ���
	bool m_bisSale;

public:
	Peddle(int ID);
	~Peddle(){delete m_pStateMachine;}

	// �̰��� �ݵ�� ��ġ�Ǿ�� �Ѵ�.
	void Update();

	// ���� ���¸� ���ο� ���·� ��ȭ��Ų��.
	//void ChangeState(State* pNewState);
	StateMachine<Peddle>*  GetFSM()const{return m_pStateMachine;}

	location_type	Location()const{return m_Location;}
	void			ChangeLocation(const location_type loc){m_Location=loc;}

	bool          IsSale()const{return m_bisSale;}
	void          SetIsSale(const bool val){m_bisSale = val;}

	virtual bool  HandleMessage(const Telegram& msg);
};

#endif