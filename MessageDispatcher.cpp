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
	// �ؽ�Ʈ�� ���� �����Ѵ�.
	SetTextColor(BACKGROUND_RED|FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE);

	// �޽��� �����ڸ� ����Ű�� �����͸� ����.
	BaseGameEntity* pSender		= EntityMgr->GetEntityFromID(sender);
	BaseGameEntity* pReceiver	= EntityMgr->GetEntityFromID(receiver);
	if (pReceiver == NULL)
	{
		cout << "\nWarning!! " << receiver << " : Receiver ID�� ã�� �� �����ϴ�.";
		return;
	}

	// ������ �����Ѵ�.
	Telegram telegram(0, sender, receiver, msg, ExtraInfo);

	// ������ �ʿ䰡 ���ٸ�, �� ������ ���� �߼��Ѵ�.
	if (delay <= 0.0f)                                                        
	{
		cout<<"\n"<<GetNameOfEntity(pSender->ID())<<"��(��)"
			<<GetNameOfEntity(pReceiver->ID())<<"���� �ð�:"
			<<Clock->GetTickCount()<<"�� �߼��� �Ｎ ����."
			<<"\n�޽����� "<<MsgToStr(msg);

		// ������ �����ڿ��� ������.
		Discharge(pReceiver, telegram);
	}
	// �ƴϸ� ������ ���� �߼۵Ǿ�� �ϴ��� �� �ð��� ����Ѵ�.
	else
	{
		double CurrentTime = Clock->GetTickCount(); 

		telegram.DispatchTime = CurrentTime + delay;

		// �׸��� ť�� ���� �ִ´�.
		PriorityQ.insert(telegram);

		cout<<"\n"<<GetNameOfEntity(pReceiver->ID())<<"�� ���� �ð�:"
			<<Clock->GetTickCount()<<"�� ��ϵ� "
			<<GetNameOfEntity(pSender->ID())<<"�κ��� ������ ����."
			<<"\n�޽����� "<<MsgToStr(msg);
	}
}

void MessageDispatcher::DispatchDelayedMessages()
{
	SetTextColor(BACKGROUND_RED|FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE);

	// �켱 ���� �ð��� ���� �´�.
	double CurrentTime = Clock->GetTickCount();

	// ���۵� �ʿ䰡 �ִ� ������ �ִ����� �˾ƺ��� ����, ť�� Ȯ���Ѵ�.
	// �ð��� ��������� ���� �������� ť�� �պκк��� ������ ������.
	while( !PriorityQ.empty() &&
		(PriorityQ.begin()->DispatchTime < CurrentTime) && 
		(PriorityQ.begin()->DispatchTime > 0) )
	{
		// ť�� �պκк��� ������ �о� ������.
		const Telegram& telegram = *PriorityQ.begin();

		// �����ڸ� ã�Ƴ���.
		BaseGameEntity* pReceiver = EntityMgr->GetEntityFromID(telegram.Receiver);

		cout<<"\n�߼� �غ�� ��� ����: "
			<<GetNameOfEntity(pReceiver->ID())<<"���� ������."
			<<"\n�޽����� "<<MsgToStr(telegram.Msg);			

		// �����ڿ��� ������ ������.
		Discharge(pReceiver, telegram);
		// �׸��� ť�κ��� �����Ѵ�.
		PriorityQ.erase(PriorityQ.begin());
	}
}