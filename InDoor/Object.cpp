#include "Object.h"
#include "GameManager.h"

Object::Object()
{
    Initialize();
}

Object::Object(const ObjectData& dataSet, int index)
{
    Initialize();


    eachObjectIndex.name = dataSet.eachObject[index]->objectIndex.name;
    //������Ʈ Ÿ�� ����
    typeCheck = dataSet.typeCheck;
    //���ҽ�
    SpritesX = dataSet.spritesX;
    SpritesY = dataSet.spritesY;

    //������Ʈ ��Ī
    objectName = dataSet.objectName;
    //���ϸ�
    fileName = dataSet.fileName;

    //Objeect ����
    eachObjectIndex.mapIndex = dataSet.eachObject[index]->objectIndex.mapIndex;
    eachObjectIndex.eachObjectIndex = dataSet.eachObject[index]->objectIndex.eachObjectIndex;

    Available = dataSet.eachObject[index]->Available;
    isMove = dataSet.eachObject[index]->isMove;
    isAnim = dataSet.eachObject[index]->isAnim;
    isActive = dataSet.eachObject[index]->isActive;

    ENGINE::ResourceMgr->Load(dataSet.fileName);

    renderer = new ENGINE::SpriteRenderer(dataSet.fileName.c_str(), SpritesX, SpritesY);
    renderer->SetPos(dataSet.eachObject[index]->x, dataSet.eachObject[index]->y);
    renderer->SetPivot(ENGINE::Pivot::Left | ENGINE::Pivot::Top);
    renderer->SetScale(transform->scale.x, transform->scale.y);
    if (isActive) //�۵� ���ο� ���� �̹��� �ٸ���
        renderer->SetSrc(0, 1);
    AddComponent(renderer);

    //renderer->SetRect(); //��ǥ �̵��� ���� Rect ��ȭ

    //Anim ����
    if (isAnim) //TODO::�ִϸ��̼� �ӵ� ���� �κ��� AnimationComponent
        AddComponent(anim = new ENGINE::SpriteAnimation(SpritesX, SpritesY));
    else
        anim = NULL;

    //Move ����
    dir = (Direction)dataSet.eachObject[index]->move_X; //TODO::�̰� 
    //dir = (Direction)dataSet.eachObject[index].move_Y; //move_Y �κе� �ش� �ǰ�
    moveSpeed = dataSet.eachObject[index]->move_Speed;


    //�� ������
    detailSelectCount = dataSet.detailSelectCount;
    sDetailSelect = dataSet.sDetailSelect;

}

Object::~Object()
{
}

VOID Object::Initialize()
{
    isUse = true;
    isHaveItem = false;
}

VOID Object::Update(const FLOAT& deltaTime)
{//TODO::�ִϸ��̼� �ִ� ������ ������ �߰�
    //Ȱ��, ��Ȱ��ȭ �����ؼ�. Ȱ��ȭ �����϶�
    //TODO::�ִϸ��̼� �������, �ƴϸ� �̹����� �ٲ��� �����غ��� ��.

    //��Ȱ��ȭ �����̸� 

    //Operate(this);
    //TODO:: ������ ���¿� ���� ��� �̹��� ��ȭ
    //if (prevState == State::Move) //'0'�� move �����϶�
    //{
    //    renderer->SetPivot(ENGINE::Pivot::Left | ENGINE::Pivot::Bottom);
    //}

    //if (isActive) //�۵� ���ο� ���� �̹��� �ٸ���
    //    renderer->SetSrc(0, 1);
    //else
    //    renderer->SetSrc(0, 0);

}

VOID Object::Move(const FLOAT& deltaTime)
{
    switch (dir)
    {
    case Direction::RIGHT:
        anim->Play(0);
        transform->position.x += moveSpeed * deltaTime;
        break;
    case Direction::LEFT:
        anim->Play(1);
        transform->position.x -= moveSpeed * deltaTime;
        break;
    }
}

VOID Object::Draw()
{
    if (isUse)
	    renderer->Draw();
}

void Object::DetailSelectForm()
{
	switch (detailSelectCount)
	{
	case 1:
        ENGINE::UIMgr->Remove("Detail Optional Form_2");
        detailSelect_UI = nullptr;
        detailSelect_UI = ENGINE::UIMgr->AddUI<ENGINE::UIImage>("Detail Optional Form_2");
        detailSelect_UI->Initialize("Select_Panel_2.bmp", ENGINE::DrawType::Transparent);
		break;
	case 2:
        ENGINE::UIMgr->Remove("Detail Optional Form_3");
        detailSelect_UI = nullptr;
        detailSelect_UI = ENGINE::UIMgr->AddUI<ENGINE::UIImage>("Detail Optional Form_3");
        detailSelect_UI->Initialize("Select_Panel_3.bmp", ENGINE::DrawType::Transparent);
		break;
	case 3:
        ENGINE::UIMgr->Remove("Detail Optional Form_4");
        detailSelect_UI = nullptr;
        detailSelect_UI = ENGINE::UIMgr->AddUI<ENGINE::UIImage>("Detail Optional Form_4");
        detailSelect_UI->Initialize("Select_Panel_4.bmp", ENGINE::DrawType::Transparent);
		break;
    default:
        break;
	}


    //�������� �����ϸ�
	if (detailSelect_UI) //Available�̸� ���� 0 �̻��̹Ƿ� bool������ �������� �ʾҴ�.
	{
		int i, selectBtn_X, selectBtn_Y;

        detailSelect_UI->SetPosition(UI_SELECT_X, UI_SELECT_Y, false);
		selectBtn_X = detailSelect_UI->GetSize().cx * 0.5f;
		selectBtn_Y = 17;


        //���� ������ �����
		for (i = 0; i < detailSelectCount; i++)
		{
			//��ư-������
            ENGINE::UIButton* btn_select = ENGINE::UIMgr->AddUI<ENGINE::UIButton>(objectName + "Detail Optional " + std::to_string(i + 1) + " Btn", detailSelect_UI); //���� �̸����� ����
			btn_select->Initialize("Select_Btn_Normal.bmp", "Select_Btn_Pressed.bmp", "", "", ENGINE::DrawType::Transparent);
			btn_select->SetLocalPosition(selectBtn_X, selectBtn_Y, true);
			//btn_select->SetListener(std::bind(&Object::DetailSelect, this, i));
            btn_select->SetListener(std::bind(&Object::DetailSelect, this, i));

			//�� ������ ����
            ENGINE::UILabel* btn_txt = ENGINE::UIMgr->AddUI<ENGINE::UILabel>(objectName + sDetailSelect[i] + "Detail Optional Txt", btn_select);
			btn_txt->SetLocalPosition(FONT_SELECT_X, FONT_SELECT_Y, true);
			btn_txt->Initialize(sDetailSelect[i], RGB(255, 255, 255), ENGINE::GUIMgr->Get_Font(FONT_SELECT));

			selectBtn_Y += 25;
		}

        ENGINE::UIButton* btn_Cancel = ENGINE::UIMgr->AddUI<ENGINE::UIButton>("Detail_CancelBtn_Panel_" + std::to_string(i + 1), detailSelect_UI);
		btn_Cancel->Initialize("Select_Btn_Normal.bmp", "Select_Btn_Pressed.bmp", "", "", ENGINE::DrawType::Transparent);
		btn_Cancel->SetLocalPosition(selectBtn_X, selectBtn_Y, true);
		btn_Cancel->SetListener(std::bind(&Object::CancelBtnClickHandler, this));
        

		//������ ����
        ENGINE::UILabel* btnCancel_txt = ENGINE::UIMgr->AddUI<ENGINE::UILabel>("Detail_Cancel_Txt" + std::to_string(i + 1), btn_Cancel);
		btnCancel_txt->SetLocalPosition(FONT_SELECT_X, FONT_SELECT_Y, true);
		btnCancel_txt->Initialize("���", RGB(255, 255, 255), ENGINE::GUIMgr->Get_Font(FONT_SELECT));
	}
    detailSelect_UI->SetEnable(TRUE);
}


//void Object::DetailSelect(int selectNum)
//{
//    detailSelect_UI->SetEnable(FALSE);
//    ENGINE::GUIMgr->Set_IsPause(false);
//    //return nullptr; // ���� ó��: ������ �����ʸ� ã�� ���� ���
//}

void Object::CancelBtnClickHandler()
{
    detailSelect_UI->SetEnable(FALSE);
    //pauseBtn->SetInteracterble(TRUE);
   // isPause = FALSE;
    GameMgr->Set_IsPause(false);
}

void Object::ChangeActiveState()
{ 
    isActive = !isActive; 

    if (isActive) //�۵� ���ο� ���� �̹��� �ٸ���
        renderer->SetSrc(0, 1);
    else
        renderer->SetSrc(0, 0);

    //return isActive;
}


void Object::TimeChangeBitmap(bool isDrak)
{
    if (isDrak)
        isActive = false;
    else
        isActive = true;

    if (isActive) //�۵� ���ο� ���� �̹��� �ٸ���
        renderer->SetSrc(0, 1);
    else
        renderer->SetSrc(0, 0);
}

VOID Object::Release()
{
}