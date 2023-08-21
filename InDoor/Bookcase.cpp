#include "Bookcase.h"
#include "GameManager.h"

Bookcase::Bookcase()
{
}

Bookcase::Bookcase(const ObjectData& dataSet, int index) : Object(dataSet, index)
{
}

Bookcase::~Bookcase()
{
}

VOID Bookcase::Initialize()
{
    return VOID();
}

VOID Bookcase::Move(const FLOAT& deltaTime)
{
    return VOID();
}

void Bookcase::DetailSelect(int selectNum)
{//0~������ ����-1�� �����ʸ� ���ε��ϱ� ���� �����Ѵ�. 

    //��� ���� �ִ� ������ ������ 3���� ����
    switch (selectNum)
    {
    case 0:
        //TODO::��¥ Ȥ�� Ƚ���� ���� å �ٸ���
        GameMgr->SetShowUnder(BOOK_0); //�ܼ��ϰ� �ؽ�Ʈ ���
        break;
    }

    detailSelect_UI->SetEnable(FALSE);
}