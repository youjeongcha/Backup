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
{//0~선택지 개수-1의 리스너를 바인딩하기 위해 리턴한다. 

    //취소 제외 최대 선택지 개수는 3개로 제한
    switch (selectNum)
    {
    case 0:
        //TODO::날짜 혹은 횟수에 따라 책 다르게
        GameMgr->SetShowUnder(BOOK_0); //단순하게 텍스트 출력
        break;
    }

    detailSelect_UI->SetEnable(FALSE);
}