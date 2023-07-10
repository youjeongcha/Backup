#include "Door.h"
#include "ResourceManager.h"
//#include "SceneManager.h"
#include "UIManager.h"
#include "GUIManager.h"


//TODO::생성자에서 인자를 받아서 Object의 상세값을 설정하는 쪽으로 바꾸고자 함
//창문을 여러개 달 경우에 관리는. 가구들을 개수와 좌표를 관리하는 txt가 따로 존재?
Door::Door()
{
   // //문에서 isACtive는 사람과 문을 통해 상호작용 가능 체크
   // name = "문";

 
   // typeCheck[OBJECT_TYPE::NORMAL] = false;
   // typeCheck[OBJECT_TYPE::MOVE] = false;
   // typeCheck[OBJECT_TYPE::ANIM] = false;
   // typeCheck[OBJECT_TYPE::ACTIVE] = true;

   // Available = false; //TODO:: 마땅히 작용하는지. 작용 안하면 다른 처리
   // isMove = false;
   // isAnim = false;
   // isActive = false;
   // //state = State::INACTIVE;

   // //dir = Direction::NONE;
   // //moveSpeed = 0;
   // 
   // //리소스
   // SpritesX = 1;
   // SpritesY = 2;

   // ENGINE::ResourceMgr->Load("Home_Door.bmp");

   // renderer = new ENGINE::SpriteRenderer("Home_Door.bmp", SpritesX, SpritesY);
   // renderer->SetPos(650, 55);
   // renderer->SetPivot(ENGINE::Pivot::Left | ENGINE::Pivot::Top);
   // renderer->SetScale(transform->scale.x, transform->scale.y);
   // if (isActive) //작동 여부에 따라 이미지 다르게
   // {
   //     renderer->SetSrc(0, 1);
   // }
   // AddComponent(renderer);
   // 

   // //Anim 관련
   // if (isAnim) //TODO::애니메이션 속도 조절 부분은 AnimationComponent
   //     AddComponent(anim = new ENGINE::SpriteAnimation(SpritesX, SpritesY));
   // else
   //     anim = NULL;

   // //Move 관련
   // if (isMove)
   // {

   // }
   // else
   // {
   //     dir = Direction::NONE; //이거 
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


	//선택지가 존재하면
	if (detailSelect_UI)
	{
		int i, selectBtn_X, selectBtn_Y;

		detailSelect_UI->SetPosition(UI_SELECT_X, UI_SELECT_Y, false);
		selectBtn_X = detailSelect_UI->GetSize().cx * 0.5f;
		selectBtn_Y = 17;


		//세부 선택지 만들기
		for (i = 0; i < detailSelectCount; i++)
		{
			//버튼-선택지
			ENGINE::UIButton* btn_select = ENGINE::UIMgr->AddUI<ENGINE::UIButton>(objectName + "Detail Optional " + std::to_string(i + 1) + " Btn", detailSelect_UI); //파일 이름으로 구분
			btn_select->Initialize("Select_Btn_Normal.bmp", "Select_Btn_Pressed.bmp", "", "", ENGINE::DrawType::Transparent);
			btn_select->SetLocalPosition(selectBtn_X, selectBtn_Y, true);
			btn_select->SetListener(std::bind(&Door::DetailSelect, this, i));

			//상세 선택지 문구
			ENGINE::UILabel* btn_txt = ENGINE::UIMgr->AddUI<ENGINE::UILabel>(objectName + sDetailSelect[i] + "Detail Optional Txt", btn_select);
			btn_txt->SetLocalPosition(FONT_SELECT_X, FONT_SELECT_Y, true);
			btn_txt->Initialize(sDetailSelect[i], RGB(255, 255, 255), ENGINE::GUIMgr->font[FONT_SELECT]);

			selectBtn_Y += 25;
		}

		ENGINE::UIButton* btn_Cancel = ENGINE::UIMgr->AddUI<ENGINE::UIButton>("Detail_CancelBtn_Panel_" + std::to_string(i + 1), detailSelect_UI);
		btn_Cancel->Initialize("Select_Btn_Normal.bmp", "Select_Btn_Pressed.bmp", "", "", ENGINE::DrawType::Transparent);
		btn_Cancel->SetLocalPosition(selectBtn_X, selectBtn_Y, true);
		btn_Cancel->SetListener(std::bind(&Object::CancelBtnClickHandler, this));


		//선택지 문구
		ENGINE::UILabel* btnCancel_txt = ENGINE::UIMgr->AddUI<ENGINE::UILabel>("Detail_Cancel_Txt" + std::to_string(i + 1), btn_Cancel);
		btnCancel_txt->SetLocalPosition(FONT_SELECT_X, FONT_SELECT_Y, true);
		btnCancel_txt->Initialize("취소", RGB(255, 255, 255), ENGINE::GUIMgr->font[FONT_SELECT]);
	}
	detailSelect_UI->SetEnable(TRUE);
}*/

void Door::DetailSelect(int selectNum)
{//0~선택지 개수-1의 리스너를 바인딩하기 위해 리턴한다. 

    //취소 제외 최대 선택지 개수는 3개로 제한
    switch (selectNum)
    {
    case 0: //문 열기(Active) //TODO::수정 필요
		ChangeActiveState();
        //return std::bind(&Door::ChangeActiveState, this);
    case 1: //노크 //TODO:: 하단창 뜨고 ... 혹은 NPC 대면
        break;
    }

    //return nullptr; // 예외 처리: 적절한 리스너를 찾지 못한 경우
}
