#include "GameTimeManager.h"
#include "ObjectManager.h"
#include "GUIManager.h"
#include "UIManager.h"

GameTimeManager::GameTimeManager()
{
    //�ð� üũ
    accumulatedSec = 0.0f;
    nowTimeLine = TimeLine_MORING; oldTimeLine = TimeLine_MORING;
    m_Clock.hour = TimeLine_NIGHT - 1;
    m_Clock.min = 50;

    timeLabel = ENGINE::UIMgr->AddUI<ENGINE::UILabel>("Time Label");
    timeLabel->Initialize("", RGB(255, 255, 255), ENGINE::GUIMgr->Get_Font(FONT_SELECT));
    timeLabel->SetPosition(10, 10); // ���ϴ� ��ġ�� ����


}
GameTimeManager::~GameTimeManager()
{
}

void GameTimeManager::SetPlusHour(int plusHour)
{
    m_Clock.hour += plusHour;

    //24�ð� ��� ����
    if (m_Clock.hour >= TimeLine_ONEDAY)
        m_Clock.hour -= TimeLine_ONEDAY;
}

void GameTimeManager::Update(const FLOAT&  deltaTime)
{
    //�ð� ��� ī��Ʈ
    accumulatedSec += deltaTime;

    if (accumulatedSec >= 1.0f)
    {
        accumulatedSec -= 1.0f;
        m_Clock.min += 1;
        if (m_Clock.min >= 60)
        {
            m_Clock.min -= 60;
            m_Clock.hour += 1;
        }
    }

    //24�ð� ��� ����
    if (m_Clock.hour >= TimeLine_ONEDAY)
        m_Clock.hour -= TimeLine_ONEDAY;


    //�ð��� ���(�� ��)
    if ((m_Clock.hour >= TimeLine_MORING) && (m_Clock.hour < TimeLine_NIGHT))
        nowTimeLine = TimeLine_MORING;
    else
        nowTimeLine = TimeLine_NIGHT;


    //�ð��� ���� �޶����� ��ҵ� ó��(Object, NPC��)

    //���� ��ȯ�� ���� �ܼ� BitpMap �ٲ�� ��ҵ�
    if ((nowTimeLine == TimeLine_NIGHT) && (oldTimeLine == TimeLine_MORING))
    {//�� > ��
        isDrak = true;
        ObjectMgr->TimeChangeBitmap(isDrak);
    }
    else if ((nowTimeLine == TimeLine_MORING) && (oldTimeLine == TimeLine_NIGHT))
    {//�� > ��
        isDrak = false;
        ObjectMgr->TimeChangeBitmap(isDrak);
    }

    oldTimeLine = nowTimeLine;
}
