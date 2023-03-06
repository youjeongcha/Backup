#ifndef _MESSAGE_DISPATCHER_H
#define _MESSAGE_DISPATCHER_H

#pragma warning (disable:4786)

#include <set>
#include <string>

#include "Telegram.h"

using namespace std;

class BaseGameEntity;

const double SEND_MSG_IMMEDIATELY = 0.0;
const int    NO_ADDITIONAL_INFO   = 0;
const int    SENDER_ID_IRRELEVANT = -1;

class MessageDispatcher
{
private:
	// std::set는 자동 정렬과 중뵥 회피라는 이점 때문에,
	// 지연된 메시지를 담고 있기 위한 용기로 사용된다.
	// 메시지들은 자신들이 발송된 시간에 따라 정렬 된다.
	set<Telegram> PriorityQ;

	// DispatcherMessage나 DispatcherDelayedMessage가 활용한다.
	// 수신용 엔티티인 pReceiver라고 하는 메시지 처리 멤버 함수를 새로 생성된 전보와 함께 호출한다.
	void Discharge(BaseGameEntity* pReceiver, const Telegram& msg);

	MessageDispatcher(){}
	MessageDispatcher(const MessageDispatcher&);
	MessageDispatcher& operator=(const MessageDispatcher&);

public:
	// 이 클래스는 유일 객체이다.
	static MessageDispatcher* Instance();

	void DispatchMessages(double delay,
						 int	sender,
						 int	receiver,
						 int	msg,
						 void*	ExtraInfo);

	// 지연된 모든 메시지를 보낸다.
	// 게임의 주 루프를 통해서 매번 호출된다.
	void DispatchDelayedMessages();
};

#define Dispatch MessageDispatcher::Instance()

#endif