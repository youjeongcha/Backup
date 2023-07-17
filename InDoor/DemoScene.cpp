#include "DemoScene.h"
#include "ResourceManager.h"
#include "SceneManager.h"
#include "ObjectManager.h"
#include "GUIManager.h"
#include "GameTimeManager.h"
// 

VOID DemoScene::Initialize()
{
    ////�ð� üũ
    //nowTimeLine = TimeLine_MORING; oldTimeLine = TimeLine_MORING;
    //m_Clock.hour = TimeLine_NIGHT - 1;
    //m_Clock.min = 50;
    /*accumulatedSec = 0.0f;*/

    //timeLabel = UIMgr->AddUI<UILabel>("Time Label");
    //timeLabel->Initialize("", RGB(255, 255, 255), GUIMgr->Get_Font(FONT_SELECT));
    //timeLabel->SetPosition(10, 10); // ���ϴ� ��ġ�� ����

    nowScene = SCENE_BEDROOM;
    ENGINE::ObjectMgr->InitSetting(nowScene, (GameTimeMgr->GetNowTimeLine() == TimeLine_MORING) ? true : false);

    //-------------�߰��� ��--------------
    ResourceMgr->Load("background.bmp"); 
    ResourceMgr->Load("Night.bmp"); 
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

    night = ResourceMgr->GetBitmap("Night.bmp");
    night->SetDrawSize(bounds, SceneMgr->GetHeight());
    ///
    //door = ResourceMgr->GetBitmap("Home_Door.bmp");
    //door->SetDrawSize(30, SceneMgr->GetHeight());


    //TODO::GameManager�� �̵�
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
    Clock _Clock = GameTimeMgr->GetClock();

    // �ð� ǥ��
    char timeStr[50];
    //sprintf_s(timeStr, "%02d:%02d:%02d", m_Clock.hour, m_Clock.min, m_Clock.sec);
    sprintf_s(timeStr, "%02d:%02d", _Clock.hour, _Clock.min);
    GameTimeMgr->GetTimeLabel()->SetText(timeStr);


    // �Ͻ�����
    isPause = GUIMgr->Get_IsPause();

    if (isPause)
        return;

    
    GameTimeMgr->Update(deltaTime);

    //else if ((nowTimeLine == TimeLine_MORING) && (oldTimeLinde == TimeLine_NIGHT))
    //{

    //}



    //�ð��� ����� ���� ��ȭ�ϴ� Objcet�� Bitmap

    player->Update(deltaTime);

    //Player�� ��ġ�� �¿� ������ ���� �� ��ȯ 
    ChangeScene();

    //player�� ��ȣ�ۿ��� object�� ����
    ObjectMgr->Update(deltaTime);


    if (0 > playerTr->position.x) 
        playerTr->position.x = 0;

    if (bounds < playerTr->position.x) 
        playerTr->position.x = bounds;
}

VOID DemoScene::Draw()
{
    background->StretchBlt(0, 0);
    
    ObjectMgr->Draw();

    player->Draw();

    if (GameTimeMgr->GetIsDark())
    {
        night->AlphaBlendBlt(0, 0, 105);
        //isDrak = false;
    }
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
    TimeLine nowTimeLine = GameTimeMgr->GetNowTimeLine();

    //�� �̵��Ҷ��� �����̽� �� + ��ġ�� �� ������ Ȥ�� �� �����̾�� �Ѵ�.
    if (player->GetIsSpace())
    {
        //�÷��̾ �������� ����
        if (player->GetRect().left <= 0)
        {
            nowScene = SCENE(nowScene + 1);

            //�� �ִ� �ε��� ����
            if (nowScene == SCENE_COUNT)
                nowScene = SCENE(nowScene - 1);
            else
            {
                //���� ������Ʈ �籸��
                ObjectMgr->InitSetting(nowScene, (nowTimeLine == TimeLine_MORING) ? true : false);
                //�÷��̾� ��ġ ���ġ
                player->SetPos(PLAYER_RESPON_RIGHT, ENGINE::ClientSize_Height);
                //player->SetPos(ENGINE::ClientSize_Width / 2, ENGINE::ClientSize_Height);
            }
        }
        else if (player->GetRect().right >= ClientSize_Width)
        { //�÷��̾ ���������� ����
            //�� �ּ� �ε��� ����
            if (nowScene == 0)
                return;
            else
            {
                nowScene = SCENE(nowScene - 1);

                //���� ������Ʈ �籸��
                ObjectMgr->InitSetting(nowScene, (nowTimeLine == TimeLine_MORING) ? true : false);
                //�÷��̾� ��ġ ���ġ
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
//    //24�ð� ��� ����
//    if (m_Clock.hour >= TimeLine_ONEDAY)
//        m_Clock.hour -= TimeLine_ONEDAY;
//}