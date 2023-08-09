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
    //���� �θ��� ������ ��� ���� : ���� > �� > ����
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
        //������ ������ ���� �ٷ� ���ϴ� �� DetailSelect���� ó���Ѵ�.
        break;
    }
}

VOID Flowerbundle_Orange::Update(const FLOAT& deltaTime)
{
    // �ִϸ��̼��� ������ Ȱ��ȭ �����϶� ���ȴ�.
    if ((isAnim && isActive) && (anim != nullptr))
    {
        Operate(this);
        anim->Play(1);
    }

    //�ð� ��� ī��Ʈ
    //��� �ð� ������Ʈ(1�ʰ� ���ӻ� 1��)
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

                //�ð��� ���� �޶����� ��ҵ� ó��(Object, NPC��)
                if (m_elapsedHour >= TimeLine_PlantGrowth) //���ӽð� 6�ð�(����6��) TimeLine_PlantGrowth
                {
                    PassOfthe_TimeChangeBitmap();
                }
            }

            //�ð��� ���� �޶����� ��ҵ� ó��(Object, NPC��)
            if (m_elapsedMin >= 6) //���ӽð� 6�ð�(����6��) TimeLine_PlantGrowth
            {
                m_elapsedMin -= 6;
                PassOfthe_TimeChangeBitmap();
            }
        }
    }
}

void Flowerbundle_Orange::DetailSelect(int selectNum)
{//0~������ ����-1�� �����ʸ� ���ε��ϱ� ���� �����Ѵ�. 

    //��� ���� �ִ� ������ ������ 3���� ����
    switch (selectNum)
    {
    case 0:
        if (growthRate == SOIL)
        {
            if (seedPlanting)
                GameMgr->SetShowUnder(FLOWERPOT_PLANTINGSEED_X);
            else
            {
                //������ ���
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
            //��Ȯ
            GameMgr->SetShowUnder(FLOWERPOT_HARVEST);
            GameMgr->PlusPlayerInventory({ SEED_ORANGE, 1 }); //����
            GameMgr->PlusPlayerInventory({ FRUIT_ORANGE, 1 }); //����

            //������ �ʱ�ȭ
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