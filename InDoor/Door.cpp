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
{//0~������ ����-1�� �����ʸ� ���ε��ϱ� ���� �����Ѵ�. 

    //��� ���� �ִ� ������ ������ 3���� ����
    switch (selectNum)
    {
    case 0: //�� ����
		//ChangeActiveState();

            //������ ���� ä���(�ӽ� ������)
        for (int i = 0; i < ITEM_COUNT; i++)
        {
            GameMgr->PlusPlayerInventory({ (ITEM_ID)i, 1 });
        }

        //Ŭ���� ���� Ȯ�� //TODO::������ ���� �߰�.
        if (GameMgr->GetIsGameClear())
        {
            GameMgr->SetShowUnder(DOOR_OPEN_O);
            renderer->SetSrc(0, 1);
            GameMgr->GameClear();
        }
        else
            GameMgr->SetShowUnder(DOOR_OPEN_X);

        break;
    case 1: //��ũ

        //NPC�� ������(�ٸ� NPC���� �۾����� �ʱ�� �뼱 Ʋ����.)
        if (GameMgr->GetIsGameClear())
            GameMgr->SetShowUnder(DOOR_KNOCK_O);
        else
            GameMgr->SetShowUnder(DOOR_KNOCK_X);

        break;
    }

	detailSelect_UI->SetEnable(FALSE);
}