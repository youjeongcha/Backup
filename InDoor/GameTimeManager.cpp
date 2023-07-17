#include "GameTimeManager.h"
#include "ObjectManager.h"
#include "GUIManager.h"
#include "UIManager.h"

GameTimeManager::GameTimeManager()
{
    //시간 체크
    accumulatedSec = 0.0f;
    nowTimeLine = TimeLine_MORING; oldTimeLine = TimeLine_MORING;
    m_Clock.hour = TimeLine_NIGHT - 1;
    m_Clock.min = 50;

    timeLabel = ENGINE::UIMgr->AddUI<ENGINE::UILabel>("Time Label");
    timeLabel->Initialize("", RGB(255, 255, 255), ENGINE::GUIMgr->Get_Font(FONT_SELECT));
    timeLabel->SetPosition(10, 10); // 원하는 위치로 설정


}
GameTimeManager::~GameTimeManager()
{
}

void GameTimeManager::SetPlusHour(int plusHour)
{
    m_Clock.hour += plusHour;

    //24시간 경과 갱신
    if (m_Clock.hour >= TimeLine_ONEDAY)
        m_Clock.hour -= TimeLine_ONEDAY;
}

void GameTimeManager::Update(const FLOAT&  deltaTime)
{
    //시간 경과 카운트
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

    //24시간 경과 갱신
    if (m_Clock.hour >= TimeLine_ONEDAY)
        m_Clock.hour -= TimeLine_ONEDAY;


    //시간대 기록(낮 밤)
    if ((m_Clock.hour >= TimeLine_MORING) && (m_Clock.hour < TimeLine_NIGHT))
        nowTimeLine = TimeLine_MORING;
    else
        nowTimeLine = TimeLine_NIGHT;


    //시간에 따라 달라지는 요소들 처리(Object, NPC등)

    //낮밤 전환에 따라 단순 BitpMap 바뀌는 요소들
    if ((nowTimeLine == TimeLine_NIGHT) && (oldTimeLine == TimeLine_MORING))
    {//낮 > 밤
        isDrak = true;
        ObjectMgr->TimeChangeBitmap(isDrak);
    }
    else if ((nowTimeLine == TimeLine_MORING) && (oldTimeLine == TimeLine_NIGHT))
    {//밤 > 낮
        isDrak = false;
        ObjectMgr->TimeChangeBitmap(isDrak);
    }

    oldTimeLine = nowTimeLine;
}
