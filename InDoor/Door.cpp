#include "Door.h"
#include "GameManager.h"


Door::Door()
{
}

Door::Door(const ObjectData& dataSet, int index) : Object(dataSet, index)
{

}

Door::~Door()
{
}

VOID Door::Initialize()
{
    return VOID();
}

VOID Door::Move(const FLOAT& deltaTime)
{
    return VOID();
}


void Door::DetailSelect(int selectNum)
{//0~선택지 개수-1의 리스너를 바인딩하기 위해 리턴한다. 

    //취소 제외 최대 선택지 개수는 3개로 제한
    switch (selectNum)
    {
    case 0: //문 열기
		//ChangeActiveState();

            //아이템 전부 채우기(임시 디버깅용)
        for (int i = 0; i < ITEM_COUNT; i++)
        {
            GameMgr->PlusPlayerInventory({ (ITEM_ID)i, 1 });
        }

        //클리어 가능 확인 //TODO::문열면 엔딩 추가.
        if (GameMgr->GetIsGameClear())
        {
            GameMgr->SetShowUnder(DOOR_OPEN_O);
            renderer->SetSrc(0, 1);
            GameMgr->GameClear();
        }
        else
            GameMgr->SetShowUnder(DOOR_OPEN_X);

        break;
    case 1: //노크

        //NPC가 있으면(다만 NPC까지 작업하지 않기로 노선 틀었다.)
        if (GameMgr->GetIsGameClear())
            GameMgr->SetShowUnder(DOOR_KNOCK_O);
        else
            GameMgr->SetShowUnder(DOOR_KNOCK_X);

        break;
    }

	detailSelect_UI->SetEnable(FALSE);
}