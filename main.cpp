#include <fstream>
#include <time.h>

#include "Locations.h"
#include "Miner.h"
#include "ConsoleUtils.h"
#include "EntityNames.h"
#include "EntityManager.h"
#include "MessageDispatcher.h"
#include "CrudeTimer.h"
//#include "FrameCounter.h"

#include "MinersWife.h"
#include "Peddle.h"


int main()
{
	srand((unsigned) time(NULL));

	// Miner ��ü�� �����
	// ID�� ent_Miner_Bob���� �ʱ�ȭ �Ѵ�.
	//Miner miner(ent_Miner_Bob);
	Miner* Bob = new Miner(ent_Miner_Bob);

	MinersWife* Elsa = new MinersWife(ent_Elsa);

	Peddle* peddle = new Peddle(ent_Peddle);

	EntityMgr->RegisterEntity(Bob);
	EntityMgr->RegisterEntity(Elsa);
	EntityMgr->RegisterEntity(peddle);

	// 20ȸ ���ư��� ����������
	// 0.8�ʾ� �����Ѵ�.
	for (int i=0; i<50; ++i)
	{
		Bob->Update();
		Elsa->Update();
		peddle->Update();

		Dispatch->DispatchDelayedMessages();

		Sleep(800);
	}

	delete Bob;
	delete Elsa;
	delete peddle;

	// �ƹ� Ű�� ������ ���� �۾��� �����Ѵ�.
	// ������ ���̻� ������ �۾��� ��� �״�� ����ȴ�.
	PressAnyKeyToContinue();

	return 0;
}