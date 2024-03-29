#include "DemoScene.h"

VOID DemoScene::Initialize()
{
    nowScene = SCENE_BEDROOM;
    //nowScene = SCENE_DOOR;
    //씬의 오브젝트 재구성(현재 씬, 이동할 씬)인데 초기 화면 세팅은 nowScene으로 둘다 세팅한다.
    ENGINE::ObjectMgr->InitSetting(nowScene, nowScene, GameMgr->GetIsDark()); //게임은 아침을 배경으로 시작

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

    //TODO::GameManager로 이동?
    player = new Player;
    player->Initialize();
    playerTr = player->GetTransform();
    playerSr = static_cast<SpriteRenderer*>(player->GetComponent(ComponentType::Graphic));

}


VOID DemoScene::Release()
{
    REL_DEL(player);
}

VOID DemoScene::Update(const FLOAT& deltaTime)
{
    if (GameMgr->GetIsGameOver() && GameMgr->GetisReset_OneTime()) //게임오버되고 게임 리셋 함수(맵, 플레이어 위치) 1회 실행
    {
        //씬의 오브젝트 재구성(현재 씬, 이동할 씬)
        ObjectMgr->InitSetting(nowScene, SCENE_BEDROOM, GameMgr->GetIsDark());
        nowScene = SCENE_BEDROOM;
        player->Initialize();
        GameMgr->SetisReset_OneTime(false);
        return;
    }
    else if (GameMgr->GetIsGameOver() || GameMgr->Get_IsPause()) //게임 오버나 다른 이미지를 띄워줄때 플레이어가 인벤토리와 가구에 상호작용 못해야 한다.
        return;

    // 일시정지
    isPause = GameMgr->Get_IsPause();

    if (isPause)
        return;
    
    GameMgr->Update(deltaTime);

    //시간의 경과에 따라 변화하는 Objcet의 Bitmap
    if (!GameMgr->GetIsGameEnd())
        player->Update(deltaTime);

    //Player의 위치가 좌우 끝으로 가면 씬 전환 
    ChangeScene();

    //Update문에서 식물 성장 등 + 가구 애니메이션 작동
    ObjectMgr->Update(deltaTime);

    if (PLAYER_MOVE_END_LEFT > playerTr->position.x)
        playerTr->position.x = PLAYER_MOVE_END_LEFT;

    if (PLAYER_MOVE_END_RIGHT < playerTr->position.x)
        playerTr->position.x = PLAYER_MOVE_END_RIGHT;

    /*if (0 > playerTr->position.x)
        playerTr->position.x = 0;

    if (bounds < playerTr->position.x) 
        playerTr->position.x = bounds;*/
}

VOID DemoScene::Draw()
{
    if (!GameMgr->GetIsGameOver() || !GameMgr->Get_IsPause())
    {
        background->StretchBlt(0, 0);

        ObjectMgr->Draw();

        if (!GameMgr->GetIsGameEnd())
            player->Draw();
    }

    //밤은 맨 위에 깔아줘야 한다.
    GameMgr->Draw();
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

                //플레이어 위치 재배치
                player->SetPos(PLAYER_RESPON_RIGHT, ENGINE::ClientSize_Height);
            }
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
                //플레이어 위치 재배치
                player->SetPos(PLAYER_RESPON_LEFT, ENGINE::ClientSize_Height);
            }
        }
        player->SetIsSpace(false);
    }
    else if (GameMgr->GetIsInventory())
        GameMgr->Inventory_Panel();
}