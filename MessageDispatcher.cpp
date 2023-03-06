#include "MessageDispatcher.h"
#include "BaseGameEntity.h"
#include "EntityManager.h"
#include "CrudeTimer.h"
//#include "FrameCounter.h"
#include "ConsoleUtils.h"
#include "EntityNames.h"
#include "MessageTypes.h"

#include <iostream>
using std::cout;
using std::set;

void MessageDispatcher::Discharge(BaseGameEntity* pReceiver,
	const Telegram& telegram)
{
	if (!pReceiver->HandleMessage(telegram))
	{
		cout << "Message not handled";
	}
}

MessageDispatcher* MessageDispatcher::Instance()
{
	static MessageDispatcher instance;

	return &instance;
}

void MessageDispatcher::DispatchMessages(double delay,
										 int	sender,
										 int	receiver,
										 int	msg,
										 void*	ExtraInfo)
{
	// 텍스트의 색을 변경한다.
	SetTextColor(BACKGROUND_RED|FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE);

	// 메시지 수신자를 가리키는 포인터를 얻어낸다.
	BaseGameEntity* pSender		= EntityMgr->GetEntityFromID(sender);
	BaseGameEntity* pReceiver	= EntityMgr->GetEntityFromID(receiver);
	if (pReceiver == NULL)
	{
		cout << "\nWarning!! " << receiver << " : Receiver ID를 찾을 수 없습니다.";
		return;
	}

	// 전보를 생성한다.
	Telegram telegram(0, sender, receiver, msg, ExtraInfo);

	// 지연될 필요가 없다면, 그 전보를 당장 발송한다.
	if (delay <= 0.0f)                                                        
	{
		cout<<"\n"<<GetNameOfEntity(pSender->ID())<<"이(가)"
			<<GetNameOfEntity(pReceiver->ID())<<"에게 시간:"
			<<Clock->GetTickCount()<<"에 발송한 즉석 전보."
			<<"\n메시지는 "<<MsgToStr(msg);

		// 전보를 수신자에게 보낸다.
		Discharge(pReceiver, telegram);
	}
	// 아니면 전보가 언제 발송되어야 하는지 그 시간을 계산한다.
	else
	{
		double CurrentTime = Clock->GetTickCount(); 

		telegram.DispatchTime = CurrentTime + delay;

		// 그리고 큐에 집어 넣는다.
		PriorityQ.insert(telegram);

		cout<<"\n"<<GetNameOfEntity(pReceiver->ID())<<"를 위해 시간:"
			<<Clock->GetTickCount()<<"에 기록된 "
			<<GetNameOfEntity(pSender->ID())<<"로부터 지연된 전보."
			<<"\n메시지는 "<<MsgToStr(msg);
	}
}

void MessageDispatcher::DispatchDelayedMessages()
{
	SetTextColor(BACKGROUND_RED|FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE);

	// 우선 현재 시간을 가져 온다.
	double CurrentTime = Clock->GetTickCount();

	// 전송될 필요가 있는 전보가 있는지를 알아보기 위해, 큐를 확인한다.
	// 시간상 유통기한이 지난 전보들을 큐의 앞부분부터 제거해 나간다.
	while( !PriorityQ.empty() &&
		(PriorityQ.begin()->DispatchTime < CurrentTime) && 
		(PriorityQ.begin()->DispatchTime > 0) )
	{
		// 큐의 앞부분부터 전보를 읽어 나간다.
		const Telegram& telegram = *PriorityQ.begin();

		// 수신자를 찾아낸다.
		BaseGameEntity* pReceiver = EntityMgr->GetEntityFromID(telegram.Receiver);

		cout<<"\n발송 준비된 대기 전보: "
			<<GetNameOfEntity(pReceiver->ID())<<"에게 보내짐."
			<<"\n메시지는 "<<MsgToStr(telegram.Msg);			

		// 수신자에게 전보를 보낸다.
		Discharge(pReceiver, telegram);
		// 그리고 큐로부터 제거한다.
		PriorityQ.erase(PriorityQ.begin());
	}
}