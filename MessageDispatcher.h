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
	// std::set�� �ڵ� ���İ� �ߔ� ȸ�Ƕ�� ���� ������,
	// ������ �޽����� ��� �ֱ� ���� ���� ���ȴ�.
	// �޽������� �ڽŵ��� �߼۵� �ð��� ���� ���� �ȴ�.
	set<Telegram> PriorityQ;

	// DispatcherMessage�� DispatcherDelayedMessage�� Ȱ���Ѵ�.
	// ���ſ� ��ƼƼ�� pReceiver��� �ϴ� �޽��� ó�� ��� �Լ��� ���� ������ ������ �Բ� ȣ���Ѵ�.
	void Discharge(BaseGameEntity* pReceiver, const Telegram& msg);

	MessageDispatcher(){}
	MessageDispatcher(const MessageDispatcher&);
	MessageDispatcher& operator=(const MessageDispatcher&);

public:
	// �� Ŭ������ ���� ��ü�̴�.
	static MessageDispatcher* Instance();

	void DispatchMessages(double delay,
						 int	sender,
						 int	receiver,
						 int	msg,
						 void*	ExtraInfo);

	// ������ ��� �޽����� ������.
	// ������ �� ������ ���ؼ� �Ź� ȣ��ȴ�.
	void DispatchDelayedMessages();
};

#define Dispatch MessageDispatcher::Instance()

#endif