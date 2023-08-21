#include "DemoScene.h"

VOID DemoScene::Initialize()
{
    nowScene = SCENE_BEDROOM;
    //nowScene = SCENE_DOOR;
    //���� ������Ʈ �籸��(���� ��, �̵��� ��)�ε� �ʱ� ȭ�� ������ nowScene���� �Ѵ� �����Ѵ�.
    ENGINE::ObjectMgr->InitSetting(nowScene, nowScene, GameMgr->GetIsDark()); //������ ��ħ�� ������� ����

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

    //TODO::GameManager�� �̵�?
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
    if (GameMgr->GetIsGameOver() && GameMgr->GetisReset_OneTime()) //���ӿ����ǰ� ���� ���� �Լ�(��, �÷��̾� ��ġ) 1ȸ ����
    {
        //���� ������Ʈ �籸��(���� ��, �̵��� ��)
        ObjectMgr->InitSetting(nowScene, SCENE_BEDROOM, GameMgr->GetIsDark());
        nowScene = SCENE_BEDROOM;
        player->Initialize();
        GameMgr->SetisReset_OneTime(false);
        return;
    }
    else if (GameMgr->GetIsGameOver() || GameMgr->Get_IsPause()) //���� ������ �ٸ� �̹����� ����ٶ� �÷��̾ �κ��丮�� ������ ��ȣ�ۿ� ���ؾ� �Ѵ�.
        return;

    // �Ͻ�����
    isPause = GameMgr->Get_IsPause();

    if (isPause)
        return;
    
    GameMgr->Update(deltaTime);

    //�ð��� ����� ���� ��ȭ�ϴ� Objcet�� Bitmap
    if (!GameMgr->GetIsGameEnd())
        player->Update(deltaTime);

    //Player�� ��ġ�� �¿� ������ ���� �� ��ȯ 
    ChangeScene();

    //Update������ �Ĺ� ���� �� + ���� �ִϸ��̼� �۵�
    ObjectMgr->Update(deltaTime);


    if (0 > playerTr->position.x) 
        playerTr->position.x = 0;

    if (bounds < playerTr->position.x) 
        playerTr->position.x = bounds;
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

    //���� �� ���� ������ �Ѵ�.
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

    //�� �̵��Ҷ��� �����̽� �� + ��ġ�� �� ������ Ȥ�� �� �����̾�� �Ѵ�.
    if (player->GetIsSpace())
    {
        //�÷��̾ �������� ����
        if (player->GetRect().left <= 0)
        {
            //�� �ִ� �ε��� ����(���� �� ���̸� ���� ����)
            if (nowScene != SCENE_COUNT - 1)
            {
                //���� ������Ʈ �籸��(���� ��, �̵��� ��)
                ObjectMgr->InitSetting(nowScene, nowScene + 1, GameMgr->GetIsDark());

                nowScene = SCENE(nowScene + 1);

                //�÷��̾� ��ġ ���ġ
                player->SetPos(PLAYER_RESPON_RIGHT, ENGINE::ClientSize_Height);
            }
        }
        else if (player->GetRect().right >= ClientSize_Width)
        { //�÷��̾ ���������� ����
            //�� �ּ� �ε��� ����
            if (nowScene == 0)
                return;
            else
            {
                //���� ������Ʈ �籸��(���� ��, �̵��� ��)
                ObjectMgr->InitSetting(nowScene, nowScene - 1, GameMgr->GetIsDark());

                nowScene = SCENE(nowScene - 1);
                //�÷��̾� ��ġ ���ġ
                player->SetPos(PLAYER_RESPON_LEFT, ENGINE::ClientSize_Height);
            }
        }
        player->SetIsSpace(false);
    }
    else if (GameMgr->GetIsInventory())
        GameMgr->Inventory_Panel();
}