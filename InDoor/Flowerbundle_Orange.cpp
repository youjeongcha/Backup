#include "Flowerbundle_Orange.h"
#include "GameManager.h"

Flowerbundle_Orange::Flowerbundle_Orange()
{
    Initialize();
}

Flowerbundle_Orange::Flowerbundle_Orange(const ObjectData& dataSet, int index) : Object(dataSet, index)
{
    Initialize();
}

Flowerbundle_Orange::~Flowerbundle_Orange()
{
}

VOID Flowerbundle_Orange::Initialize()
{
    growthRate = FRUITS;
    renderer->SetSrc(2, 0);
}

VOID Flowerbundle_Orange::Move(const FLOAT& deltaTime)
{
    return VOID();
}

void Flowerbundle_Orange::PassOfthe_TimeChangeBitmap()
{
    //씨앗 부리고 물까지 줘야 성장 : 씨앗 > 꽃 > 열매
    watering = false;
    m_elapsedHour = 0;
    m_elapsedMin = 0;
    m_elapsedSec = 0;

    switch (growthRate)
    {
    case SEDDS:
        growthRate = FLOWERS;
        renderer->SetSrc(1, 0);
        break;
    case FLOWERS:
        growthRate = FRUITS;
        renderer->SetSrc(2, 0);
        break;
    defualt:
        //선택지 누르면 상태 바로 변하는 건 DetailSelect에서 처리한다.
        break;
    }
}

VOID Flowerbundle_Orange::Update(const FLOAT& deltaTime)
{
    // 애니메이션은 가구가 활성화 상태일때 사용된다.
    if ((isAnim && isActive) && (anim != nullptr))
    {
        Operate(this);
        anim->Play(1);
    }

    //시간 경과 카운트
    //경과 시간 업데이트(1초가 게임상 1분)
    if (watering)
    {
        m_elapsedSec += deltaTime;

        if (m_elapsedSec >= 1.0f)
        {
            m_elapsedSec -= 1.0f;
            m_elapsedMin += 1.0f;

            if (m_elapsedMin >= 60.0f)
            {
                m_elapsedMin -= 60.0f;
                m_elapsedHour += 1.0f;

                //시간에 따라 달라지는 요소들 처리(Object, NPC등)
                if (m_elapsedHour >= TimeLine_PlantGrowth) //게임시간 6시간(실제6분) TimeLine_PlantGrowth
                {
                    PassOfthe_TimeChangeBitmap();
                }
            }

            //시간에 따라 달라지는 요소들 처리(Object, NPC등)
            if (m_elapsedMin >= 6) //게임시간 6시간(실제6분) TimeLine_PlantGrowth
            {
                m_elapsedMin -= 6;
                PassOfthe_TimeChangeBitmap();
            }
        }
    }
}

void Flowerbundle_Orange::DetailSelect(int selectNum)
{//0~선택지 개수-1의 리스너를 바인딩하기 위해 리턴한다. 

    //취소 제외 최대 선택지 개수는 3개로 제한
    switch (selectNum)
    {
    case 0:
        if (growthRate == SOIL)
        {
            if (seedPlanting)
                GameMgr->SetShowUnder(FLOWERPOT_PLANTINGSEED_X);
            else
            {
                //아이템 사용
                if (!GameMgr->MinusPlayerItem(SEED_ORANGE))
                {
                    GameMgr->SetShowUnder(DONTHAVE_ITEM);
                    break;
                }
                seedPlanting = true;
                growthRate = SEDDS;
                GameMgr->SetShowUnder(FLOWERPOT_PLANTINGSEED_O);
            }
        }
        else
            GameMgr->SetShowUnder(FLOWERPOT_INCORRECTCHOICE);
        break;
    case 1:
        if ((growthRate == SEDDS) || (growthRate == FLOWERS))
        {
            if (watering)
                GameMgr->SetShowUnder(FLOWERPOT_WATERING_X);
            else
            {
                watering = true;
                GameMgr->SetShowUnder(FLOWERPOT_WATERING_O);
            }
        }
        else
            GameMgr->SetShowUnder(FLOWERPOT_INCORRECTCHOICE);
        break;
    case 2:
        if (growthRate == FRUITS)
        {
            //수확
            GameMgr->SetShowUnder(FLOWERPOT_HARVEST);
            GameMgr->PlusPlayerInventory({ SEED_ORANGE, 1 }); //씨앗
            GameMgr->PlusPlayerInventory({ FRUIT_ORANGE, 1 }); //열매

            //흙으로 초기화
            growthRate = SOIL;
            renderer->SetSrc(0, 0);
            seedPlanting = false;
            watering = false;
        }
        else
            GameMgr->SetShowUnder(FLOWERPOT_INCORRECTCHOICE);
        break;
    }

    detailSelect_UI->SetEnable(FALSE);
}