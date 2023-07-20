#include "Drawer.h"
#include "GameManager.h"

Drawer::Drawer()
{
    ////문에서 isACtive는 사람과 문을 통해 상호작용 가능 체크
    //name = "창문";


    //typeCheck[OBJECT_TYPE::NORMAL] = false;
    //typeCheck[OBJECT_TYPE::MOVE] = false;
    //typeCheck[OBJECT_TYPE::ANIM] = false;
    //typeCheck[OBJECT_TYPE::ACTIVE] = true;

    //Available = true;
    //isMove = false;
    //isAnim = false;
    //isActive = true;

    ////state = State::INACTIVE;

    ///*dir = Direction::NONE;
    //moveSpeed = 0;*/

    ////리소스
    //SpritesX = 1;
    //SpritesY = 2;

    //ENGINE::ResourceMgr->Load("Home_Window.bmp");

    //renderer = new ENGINE::SpriteRenderer("Home_Window.bmp", SpritesX, SpritesY);
    //renderer->SetPos(450, 32);
    //renderer->SetPivot(ENGINE::Pivot::Left | ENGINE::Pivot::Top);
    //renderer->SetScale(transform->scale.x, transform->scale.y);
    //if (isActive) //작동 여부에 따라 이미지 다르게
    //{
    //    renderer->SetSrc(0, 1);
    //}
    //AddComponent(renderer);


    ////Anim 관련
    //if (isAnim) //TODO::애니메이션 속도 조절 부분은 AnimationComponent
    //    AddComponent(anim = new ENGINE::SpriteAnimation(SpritesX, SpritesY));
    //else
    //    anim = NULL;

    ////Move 관련
    //if (isMove)
    //{

    //}
    //else
    //{
    //    dir = Direction::NONE; //이거 
    //    moveSpeed = 0;
    //}

    ///* ENGINE::InputComponent* input = new ENGINE::InputComponent;
    // input->AddBinding(VK_LEFT, [&]() { dir = Direction::Left; state = State::Move; }, [&]() { state = State::Idle; });
    // input->AddBinding(VK_RIGHT, [&]() { dir = Direction::Right; state = State::Move; }, [&]() { state = State::Idle; });
    // AddComponent(input);*/
}

Drawer::Drawer(const ObjectData& dataSet, int index) : Object(dataSet, index)
{

}

Drawer::~Drawer()
{
}

VOID Drawer::Initialize()
{
    return VOID();
}

VOID Drawer::Move(const FLOAT& deltaTime)
{
    return VOID();
}

void Drawer::DetailSelect(int selectNum)
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

    detailSelect_UI->SetEnable(FALSE);
    ENGINE::GUIMgr->Set_IsPause(false);
}
