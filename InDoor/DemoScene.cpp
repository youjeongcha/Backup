#include "DemoScene.h"
#include "ResourceManager.h"
#include "SceneManager.h"
#include "ObjectManager.h"
#include "GUIManager.h"
//#include "GameManager.h"
// 

VOID DemoScene::Initialize()
{
    ////시간 체크
    //nowTimeLine = TimeLine_MORING; oldTimeLine = TimeLine_MORING;
    //m_Clock.hour = TimeLine_NIGHT - 1;
    //m_Clock.min = 50;
    /*accumulatedSec = 0.0f;*/

    //timeLabel = UIMgr->AddUI<UILabel>("Time Label");
    //timeLabel->Initialize("", RGB(255, 255, 255), GUIMgr->Get_Font(FONT_SELECT));
    //timeLabel->SetPosition(10, 10); // 원하는 위치로 설정

    nowScene = SCENE_BEDROOM;
    //씬의 오브젝트 재구성(현재 씬, 이동할 씬)인데 초기 화면 세팅은 nowScene으로 둘다 세팅한다.
    ENGINE::ObjectMgr->InitSetting(nowScene, nowScene, GameMgr->GetIsDark()); //게임은 아침을 배겨으로 시작

    //-------------추가된 것--------------
    ResourceMgr->Load("background.bmp"); 
    //ResourceMgr->Load("Night.bmp");
    ResourceMgr->Load("Select_Panel_2.bmp");
    ResourceMgr->Load("Select_Panel_3.bmp");
    ResourceMgr->Load("Select_Panel_4.bmp");
    ResourceMgr->Load("Select_Btn_Normal.bmp");
    ResourceMgr->Load("Select_Btn_Pressed.bmp");
    //------------------------------------

    ResourceMgr->Load("pause_normal.bmp");
    ResourceMgr->Load("pause_pressed.bmp");
    ResourceMgr->Load("base_panel.bmp");
    ResourceMgr->Load("continue_normal.bmp");
    ResourceMgr->Load("continue_pressed.bmp");
    ResourceMgr->Load("quit_normal.bmp");
    ResourceMgr->Load("quit_pressed.bmp");

    bounds = SceneMgr->GetWidth();

    background = ResourceMgr->GetBitmap("background.bmp");
    background->SetDrawSize(bounds, SceneMgr->GetHeight());

    /*night = ResourceMgr->GetBitmap("Night.bmp");
    night->SetDrawSize(bounds, SceneMgr->GetHeight());*/
    ///
    //door = ResourceMgr->GetBitmap("Home_Door.bmp");
    //door->SetDrawSize(30, SceneMgr->GetHeight());


    //TODO::GameManager로 이동
    player = new Player;
    player->Initialize();
    playerTr = player->GetTransform();
    playerSr = static_cast<SpriteRenderer*>(player->GetComponent(ComponentType::Graphic));




    ///-----------------------------------------------------------------------
    /*
    pauseBtn = UIMgr->AddUI<UIButton>("Pause Btn");
    pauseBtn->Initialize("pause_normal.bmp", "pause_pressed.bmp", "", "", DrawType::Transparent);
    pauseBtn->SetPosition(bounds - pauseBtn->GetSize().cx - 22, 10);
    pauseBtn->SetListener(std::bind(&DemoScene::PauseBtnClickHandler, this));    

    pauseWindow = UIMgr->AddUI<UIImage>("PauseWindow Canvas");
    if (pauseWindow)
    {
        pauseWindow->Initialize("base_panel.bmp", DrawType::Transparent);
        pauseWindow->SetPosition(bounds * 0.5f, SceneMgr->GetHeight() * 0.5f, TRUE);

        UIButton* continueBtn = UIMgr->AddUI<UIButton>("Continue Btn", pauseWindow);
        continueBtn->Initialize("continue_normal.bmp", "continue_pressed.bmp", "", "", DrawType::Transparent);
        continueBtn->SetLocalPosition(pauseWindow->GetSize().cx * 0.5f, pauseWindow->GetSize().cy * 0.5f - 100, true);
        continueBtn->SetListener(std::bind(&DemoScene::ContinueBtnClickHandler, this));

        UIButton* quitBtn = UIMgr->AddUI<UIButton>("Quit Btn", pauseWindow);
        quitBtn->Initialize("quit_normal.bmp", "quit_pressed.bmp", "", "", DrawType::Transparent);
        quitBtn->SetLocalPosition(pauseWindow->GetSize().cx * 0.5f, pauseWindow->GetSize().cy * 0.5f + 50, true);
        quitBtn->SetListener(std::bind(&DemoScene::QuitBtnClickHandler, this));

        pauseWindow->SetEnable(FALSE);
    }

    bounds -= playerSr->GetDrawSize().cx;

    isPause = FALSE;*/
}


VOID DemoScene::Release()
{
    REL_DEL(player);
}

VOID DemoScene::Update(const FLOAT& deltaTime)
{
    Clock _Clock = GameMgr->GetClock();

    // 시간 표시
    char timeStr[100];
    //sprintf_s(timeStr, "%02d:%02d:%02d", m_Clock.hour, m_Clock.min, m_Clock.sec);
    sprintf_s(timeStr, sizeof(timeStr), "%02d:%02d  건강:%d  허기:%d  갈증:%d  피로:%d", _Clock.hour, _Clock.min, GameMgr->GetHealth(), GameMgr->GetHunger(), GameMgr->GetThirst(), GameMgr->GetFatigue());
    GameMgr->GetTimeLabel()->SetText(timeStr);


    // 일시정지
    isPause = GUIMgr->Get_IsPause();

    if (isPause)
        return;

    
    GameMgr->Update(deltaTime);

    //else if ((nowTimeLine == TimeLine_MORING) && (oldTimeLinde == TimeLine_NIGHT))
    //{

    //}



    //시간의 경과에 따라 변화하는 Objcet의 Bitmap

    player->Update(deltaTime);

    //Player의 위치가 좌우 끝으로 가면 씬 전환 
    ChangeScene();

    //player가 상호작용할 object를 선택
    ObjectMgr->Update(deltaTime);


    if (0 > playerTr->position.x) 
        playerTr->position.x = 0;

    if (bounds < playerTr->position.x) 
        playerTr->position.x = bounds;
}

VOID DemoScene::Draw()
{
    if (!GameMgr->GetIsGameOver())
    {
        background->StretchBlt(0, 0);

        ObjectMgr->Draw();

        player->Draw();
    }

    //밤은 맨 위에 깔아줘야 한다.
    GameMgr->Draw();

    //if (GameMgr->GetIsDark())
    //{
    //    night->AlphaBlendBlt(0, 0, 105);
    //    //isDrak = false;
    //}
}



VOID DemoScene::PauseBtnClickHandler()
{
    isPause = TRUE;
    pauseBtn->SetInteracterble(FALSE);
    pauseWindow->SetEnable(TRUE);
}

VOID DemoScene::ContinueBtnClickHandler()
{
    pauseWindow->SetEnable(FALSE);
    pauseBtn->SetInteracterble(TRUE);
    isPause = FALSE;
}

VOID DemoScene::QuitBtnClickHandler()
{
    PostQuitMessage(0);
}

void DemoScene::ChangeScene()
{
    TimeLine nowTimeLine = GameMgr->GetNowTimeLine();

    //씬 이동할때는 스페이스 바 + 위치가 맨 오른쪽 혹은 맨 왼쪽이어야 한다.
    if (player->GetIsSpace())
    {
        //플레이어가 왼쪽으로 갈때
        if (player->GetRect().left <= 0)
        {
            //씬 최대 인덱스 제한(왼쪽 끝 씬이면 변동 없음)
            if (nowScene != SCENE_COUNT - 1)
            {
                //씬의 오브젝트 재구성(현재 씬, 이동할 씬)
                ObjectMgr->InitSetting(nowScene, nowScene + 1, GameMgr->GetIsDark());

                nowScene = SCENE(nowScene + 1);

                //ObjectMgr->InitSetting(nowScene, (nowTimeLine == TimeLine_MORING) ? true : false);
                //플레이어 위치 재배치
                player->SetPos(PLAYER_RESPON_RIGHT, ENGINE::ClientSize_Height);
                //player->SetPos(ENGINE::ClientSize_Width / 2, ENGINE::ClientSize_Height);
            }
            //else 
            //    nowScene = SCENE(nowScene - 1);
        }
        else if (player->GetRect().right >= ClientSize_Width)
        { //플레이어가 오른쪽으로 갈때
            //씬 최손 인덱스 제한
            if (nowScene == 0)
                return;
            else
            {
                //씬의 오브젝트 재구성(현재 씬, 이동할 씬)
                ObjectMgr->InitSetting(nowScene, nowScene - 1, GameMgr->GetIsDark());

                nowScene = SCENE(nowScene - 1);
                //ObjectMgr->InitSetting(nowScene, (nowTimeLine == TimeLine_MORING) ? true : false);
                //플레이어 위치 재배치
                player->SetPos(PLAYER_RESPON_LEFT, ENGINE::ClientSize_Height);
               // player->SetPos(ENGINE::ClientSize_Width / 2, ENGINE::ClientSize_Height);
            }
        }
        player->SetIsSpace(false);
    }
}

//void DemoScene::SetPlusHour(int plusHour)
//{
//    m_Clock.hour += plusHour;
//
//    //24시간 경과 갱신
//    if (m_Clock.hour >= TimeLine_ONEDAY)
//        m_Clock.hour -= TimeLine_ONEDAY;
//}