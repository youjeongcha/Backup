#pragma once
#include <iostream>
#include "EngineMecro.h"
#include "Component.h"
#include "Components/SpriteRenderer.h"
#include "Components/SpriteAnimation.h"
#include "Components/InputComponent.h"
#include "UIManager.h"

enum OBJECT_TYPE
{
    NORMAL,
    TIMECHANGE, //밤낮에 따라 이미지 전환
    ANIM,
    ACTIVE,
    INTERACTIVE, //상호작용 가능
    TYPE_COUNT
};

struct EachObjectIndex
{//해당 object를 특정해내기 위한 요소들
    std::string name;
    int mapIndex, eachObjectIndex; //사용 맵이 어디인지 //맵에서 해당 object 안에서의 번호
};

struct EachObject
{
    //int mapIndex, index; //사용 맵이 어디인지 //맵에서 해당 object 안에서의 번호
    EachObjectIndex objectIndex;
    bool Available, isMove, isAnim, isActive;
    float x, y, move_X, move_Y, move_Speed;
};

struct ObjectData
{
    //objectData(Door)안에 해당 모든 eachObject들의 데이터들을 가지고 있다
    std::vector<EachObject*> eachObject;


    std::map<OBJECT_TYPE, bool> typeCheck;
    int spritesX, spritesY;

    std::string objectName;
    std::string fileName;

    int objectCount; //해당 오브젝트의 총 수량


    //---상세 상호작용 관련---
    int detailSelectCount; //상세 선택지 개수(취소 버튼은 미포함하여 카운트)
    std::vector<std::string> sDetailSelect;
};

enum FRUITS_GROWTH
{
    SOIL,
    SEDDS,
    FLOWERS,
    FRUITS,
    FRUITS_GROWTH_END
};

class Object;
//상태기계 관련
class State
{
public:
    virtual ~State() {}

    virtual void Enter(Object*) abstract;
    virtual void Excute(Object*) abstract;
    virtual void Exit(Object*) abstract;
};



//오브젝트의 상태 네가지로 나뉜다.
//1.일반 움직이지 않는 오브젝트
//2.이동 가능 오브젝트
//3.애니메이션 있는 오브젝트
//4.상태 전환 있는 오브젝트(커튼,등불)
 class Object abstract : public ENGINE::GameObject
{
protected:
    //std::string name;
    //int mapIndex, index; //mapIndex 해당 Object의 소속 Map //map + 해당 Object에서의 Index 번호
    EachObjectIndex eachObjectIndex;

    //현재 보여지고 상호작용 가능한가? //현재 사용중이어야지 플레이어와 겹치는지 확인하기 위해
    bool isUse;
    //현재 가지고 있는 아이템이 있는지
    bool isHaveItem;

    //명칭
    std::string objectName;
    //파일명
    std::string fileName;

    //리소스
    int spritesX, spritesY;

    ENGINE::SpriteRenderer* renderer;
    ENGINE::AnimationComponent* anim;

    //아이템 사용가능 조정/ 움직임 체크/ 애니메이션 체크/ 활성화 체크
    bool Available, isMove, isAnim, isActive;

    //인벤토리 들어올 수 있음 없음 체크 //TODO::가구 배치 가능하게 할거면 필요 없고

    //오브젝트의 가능 상태 네가지 
    std::map<OBJECT_TYPE, bool> typeCheck; //오브젝트 종류(키), 해당 오브젝트의 작동 종류(bool)

    //OBJECT_TYPE::MOVE
    enum class Direction { NONE, RIGHT, LEFT }; //오브젝트 자동 이동
    Direction dir; //이동 방향
    int moveSpeed;


    //---상세 상호작용 관련---
    int detailSelectCount; //상세 선택지 개수(취소 버튼은 미포함하여 카운트)
    ENGINE::UIImage* detailSelect_UI;
    std::vector<std::string> sDetailSelect;

public:
    Object(const Object& other) {
        // 멤버 변수들을 깊은 복사
        eachObjectIndex = other.eachObjectIndex;
        isUse = other.isUse;
        isHaveItem = other.isHaveItem;

        objectName = other.objectName;
        fileName = other.fileName;
        spritesX = other.spritesX;
        spritesY = other.spritesY;
        Available = other.Available;
        isMove = other.isMove;
        isAnim = other.isAnim;
        isActive = other.isActive;
        typeCheck = other.typeCheck;
        dir = other.dir;
        moveSpeed = other.moveSpeed;
        //상세 선택지
        detailSelectCount = other.detailSelectCount;
        detailSelect_UI = other.detailSelect_UI;
        sDetailSelect = other.sDetailSelect;

        // renderer를 깊은 복사
        AddComponent(renderer = new ENGINE::SpriteRenderer(*other.renderer));

        //transform = other.transform;

        transform->position = { other.transform->position.x,  other.transform->position.y };

        if (typeCheck.find(ANIM)->second) //TODO::애니메이션 속도 조절 부분은 AnimationComponent
            AddComponent(anim = new ENGINE::SpriteAnimation(spritesX , spritesY));
        else
            anim = NULL;
        //renderer = new ENGINE::SpriteRenderer(*other.renderer);
        // anim도 필요한 경우 깊은 복사
        //if (other.anim)
        //    anim = new ENGINE::AnimationComponent(*other.anim);
        //else
        //    anim = nullptr;
    }

    //Object& Object::operator=(const Object& other)
    //{
    //    if (this == &other)
    //        return *this;

    //    // 멤버 변수들을 깊은 복사
    //    eachObjectIndex = other.eachObjectIndex;
    //    objectName = other.objectName;
    //    fileName = other.fileName;
    //    SpritesX = other.SpritesX;
    //    SpritesY = other.SpritesY;
    //    Available = other.Available;
    //    isMove = other.isMove;
    //    isAnim = other.isAnim;
    //    isActive = other.isActive;
    //    typeCheck = other.typeCheck;
    //    dir = other.dir;
    //    moveSpeed = other.moveSpeed;

    //    // renderer를 깊은 복사
    //    delete renderer;
    //    renderer = new ENGINE::SpriteRenderer(*other.renderer);

    //    delete anim;
    //    anim = other.anim ? new ENGINE::AnimationComponent(*other.anim) : nullptr;

    //    return *this;
    //}
    /*
    Object& operator=(const Object& other) {
        // 할당 연산자의 동작을 정의합니다
        // 적절한 멤버 변수들을 other의 멤버 변수 값으로 할당합니다
        // 필요에 따라 얕은 복사 또는 깊은 복사를 수행해야 합니다
        // 반환값으로 *this를 반환합니다

        eachObjectIndex = other.eachObjectIndex;

        //리소스
        SpritesX = other.SpritesX;
        SpritesY = other.SpritesY;

        renderer = other.renderer;
        anim = other.anim;

        //아이템 사용가능 조정/ 움직임 체크/ 애니메이션 체크/ 활성화 체크
        Available = other.Available;
        isMove = other.isMove;
        isAnim = other.isAnim;
        isActive = other.isActive;

        //인벤토리 들어올 수 있음 없음 체크 //TODO::가구 배치 가능하게 할거면 필요 없고

        //오브젝트의 가능 상태 네가지 
        typeCheck = other.typeCheck; //오브젝트 종류(키), 해당 오브젝트의 작동 종류(bool)

        //OBJECT_TYPE::MOVE
        dir = other.dir; //이동 방향
        moveSpeed = other.moveSpeed;

        return *this;
    }*/

    Object();
	Object(const ObjectData& dataSet, int index); //파일기준 인덱스(파일에서 객체들 정보 순서대로 있는 것)//객체 하나만 정보 줘야한다.
	~Object();

    virtual VOID Initialize();
    //VOID Update(const FLOAT& deltaTime);
    virtual void Update(const FLOAT& deltaTime);
    virtual VOID Move(const FLOAT& deltaTime);
    virtual VOID Draw();
    VOID Release();

    //컴포넌트 겹칩 판단
    RECT GetRect() { return renderer->GetRect(); } //반환형에 const 한정자 지정
    EachObjectIndex GetEachObjectIndex() { return eachObjectIndex; }
    std::string GetObjectName() { return objectName; }

    //현재 사용중(맵에서 보여)이어야지 플레이어와 겹치는지 확인하기 위해
    bool GetisUse() { return isUse; }

    //---선택지 관련----
    void DetailSelectForm(); //세부 선택지 양식 틀
    virtual void DetailSelect(int selectNum) abstract; //양식 틀로 만든 구체적 함수 //선택지 순서대로 DetailSelectForm 쪽에 작동 리스너를 넣기 위한 함수
    //상태 변경
    void ChangeActiveState(); //TODO::낀다, 끈다, 닫다의 개념. 현재 상태 판단도 필요하다.
    void CancelBtnClickHandler();
    bool IsInteractive() { return typeCheck.find(INTERACTIVE)->second; } //상호작용 가능한 Object인지 확인

    //밤낮 변화에 따라 이미지 세팅
    void MoringNight_TimeChangeBitmap();
    //시간의 경과에 따른 이미지 세팅(ex.식물 성장)
    virtual void PassOfthe_TimeChangeBitmap();
    //ENGINE::RECT* GetRect() { return &renderer->GetRect(); }
    //Vector2 GetPos() { return renderer->GetPos(); }
    //SIZE GetSize() { return renderer->GetDrawSize(); }
};

