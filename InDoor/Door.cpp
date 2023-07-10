#include "Door.h"
#include "ResourceManager.h"
//#include "SceneManager.h"
#include "UIManager.h"
#include "GUIManager.h"


//TODO::�����ڿ��� ���ڸ� �޾Ƽ� Object�� �󼼰��� �����ϴ� ������ �ٲٰ��� ��
//â���� ������ �� ��쿡 ������. �������� ������ ��ǥ�� �����ϴ� txt�� ���� ����?
Door::Door()
{
   // //������ isACtive�� ����� ���� ���� ��ȣ�ۿ� ���� üũ
   // name = "��";

 
   // typeCheck[OBJECT_TYPE::NORMAL] = false;
   // typeCheck[OBJECT_TYPE::MOVE] = false;
   // typeCheck[OBJECT_TYPE::ANIM] = false;
   // typeCheck[OBJECT_TYPE::ACTIVE] = true;

   // Available = false; //TODO:: ������ �ۿ��ϴ���. �ۿ� ���ϸ� �ٸ� ó��
   // isMove = false;
   // isAnim = false;
   // isActive = false;
   // //state = State::INACTIVE;

   // //dir = Direction::NONE;
   // //moveSpeed = 0;
   // 
   // //���ҽ�
   // SpritesX = 1;
   // SpritesY = 2;

   // ENGINE::ResourceMgr->Load("Home_Door.bmp");

   // renderer = new ENGINE::SpriteRenderer("Home_Door.bmp", SpritesX, SpritesY);
   // renderer->SetPos(650, 55);
   // renderer->SetPivot(ENGINE::Pivot::Left | ENGINE::Pivot::Top);
   // renderer->SetScale(transform->scale.x, transform->scale.y);
   // if (isActive) //�۵� ���ο� ���� �̹��� �ٸ���
   // {
   //     renderer->SetSrc(0, 1);
   // }
   // AddComponent(renderer);
   // 

   // //Anim ����
   // if (isAnim) //TODO::�ִϸ��̼� �ӵ� ���� �κ��� AnimationComponent
   //     AddComponent(anim = new ENGINE::SpriteAnimation(SpritesX, SpritesY));
   // else
   //     anim = NULL;

   // //Move ����
   // if (isMove)
   // {

   // }
   // else
   // {
   //     dir = Direction::NONE; //�̰� 
   //     moveSpeed = 0;
   // }

   ///* ENGINE::InputComponent* input = new ENGINE::InputComponent;
   // input->AddBinding(VK_LEFT, [&]() { dir = Direction::Left; state = State::Move; }, [&]() { state = State::Idle; });
   // input->AddBinding(VK_RIGHT, [&]() { dir = Direction::Right; state = State::Move; }, [&]() { state = State::Idle; });
   // AddComponent(input);*/
}

Door::Door(const ObjectData& dataSet, int index) : Object(dataSet, index)
{

}



Door::~Door()
{
}

VOID Door::Initialize()
{
    return VOID();
}

VOID Door::Move(const FLOAT& deltaTime)
{
    return VOID();
}
/*
void Door::DetailSelectForm()
{
	switch (detailSelectCount)
	{
	case 1:
		detailSelect_UI = ENGINE::UIMgr->AddUI<ENGINE::UIImage>("Detail Optional Form_2");
		detailSelect_UI->Initialize("Select_Panel_2.bmp", ENGINE::DrawType::Transparent);
		break;
	case 2:
		detailSelect_UI = ENGINE::UIMgr->AddUI<ENGINE::UIImage>("Detail Optional Form_3");
		detailSelect_UI->Initialize("Select_Panel_3.bmp", ENGINE::DrawType::Transparent);
		break;
	case 3:
		detailSelect_UI = ENGINE::UIMgr->AddUI<ENGINE::UIImage>("Detail Optional Form_4");
		detailSelect_UI->Initialize("Select_Panel_4.bmp", ENGINE::DrawType::Transparent);
		break;
	default:
		break;
	}


	//�������� �����ϸ�
	if (detailSelect_UI)
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
			btn_select->SetListener(std::bind(&Door::DetailSelect, this, i));

			//�� ������ ����
			ENGINE::UILabel* btn_txt = ENGINE::UIMgr->AddUI<ENGINE::UILabel>(objectName + sDetailSelect[i] + "Detail Optional Txt", btn_select);
			btn_txt->SetLocalPosition(FONT_SELECT_X, FONT_SELECT_Y, true);
			btn_txt->Initialize(sDetailSelect[i], RGB(255, 255, 255), ENGINE::GUIMgr->font[FONT_SELECT]);

			selectBtn_Y += 25;
		}

		ENGINE::UIButton* btn_Cancel = ENGINE::UIMgr->AddUI<ENGINE::UIButton>("Detail_CancelBtn_Panel_" + std::to_string(i + 1), detailSelect_UI);
		btn_Cancel->Initialize("Select_Btn_Normal.bmp", "Select_Btn_Pressed.bmp", "", "", ENGINE::DrawType::Transparent);
		btn_Cancel->SetLocalPosition(selectBtn_X, selectBtn_Y, true);
		btn_Cancel->SetListener(std::bind(&Object::CancelBtnClickHandler, this));


		//������ ����
		ENGINE::UILabel* btnCancel_txt = ENGINE::UIMgr->AddUI<ENGINE::UILabel>("Detail_Cancel_Txt" + std::to_string(i + 1), btn_Cancel);
		btnCancel_txt->SetLocalPosition(FONT_SELECT_X, FONT_SELECT_Y, true);
		btnCancel_txt->Initialize("���", RGB(255, 255, 255), ENGINE::GUIMgr->font[FONT_SELECT]);
	}
	detailSelect_UI->SetEnable(TRUE);
}*/

void Door::DetailSelect(int selectNum)
{//0~������ ����-1�� �����ʸ� ���ε��ϱ� ���� �����Ѵ�. 

    //��� ���� �ִ� ������ ������ 3���� ����
    switch (selectNum)
    {
    case 0: //�� ����(Active) //TODO::���� �ʿ�
		ChangeActiveState();
        //return std::bind(&Door::ChangeActiveState, this);
    case 1: //��ũ //TODO:: �ϴ�â �߰� ... Ȥ�� NPC ���
        break;
    }

    //return nullptr; // ���� ó��: ������ �����ʸ� ã�� ���� ���
}
