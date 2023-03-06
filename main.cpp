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

	// Miner 객체를 만들어
	// ID를 ent_Miner_Bob으로 초기화 한다.
	//Miner miner(ent_Miner_Bob);
	Miner* Bob = new Miner(ent_Miner_Bob);

	MinersWife* Elsa = new MinersWife(ent_Elsa);

	Peddle* peddle = new Peddle(ent_Peddle);

	EntityMgr->RegisterEntity(Bob);
	EntityMgr->RegisterEntity(Elsa);
	EntityMgr->RegisterEntity(peddle);

	// 20회 돌아가는 루프문으로
	// 0.8초씩 갱신한다.
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

	// 아무 키나 누르면 다음 작업을 진행한다.
	// 하지만 더이상 수행할 작업이 없어서 그대로 종료된다.
	PressAnyKeyToContinue();

	return 0;
}