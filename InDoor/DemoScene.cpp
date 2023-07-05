#include "DemoScene.h"
#include "ResourceManager.h"
#include "SceneManager.h"
#include "ObjectManager.h"
#include "GUIManager.h"

// 

VOID DemoScene::Initialize()
{
    //-------------추가된 것--------------
    ResourceMgr->Load("background.bmp"); 
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
    isPause = GUIMgr->Get_IsPause();

    if (isPause) 
        return;

    player->Update(deltaTime);

    //player가 상호작용할 object를 선택

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


    //각종 가구들 그리기
    //door.Draw();
    //window.Draw();

    player->Draw();

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


