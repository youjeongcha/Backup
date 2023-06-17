#pragma once
#include <iostream>
#include <vector>
#include "EngineMecro.h"
#include "Component.h"
#include "Components/SpriteRenderer.h"
#include "Components/SpriteAnimation.h"
#include "Components/InputComponent.h"
#include "UIManager.h"

class Character : public ENGINE::GameObject {
protected:
    std::string name;
    std::vector<char> itemIDs;
    std::string filePath;

    enum Data { SpritesX = 8, SpritesY = 2, SpritesX_Idle = 4, Speed = 200 };
    enum class State { Idle, Move };
    enum class Direction { Right, Left, Up, Down };

    std::vector<ENGINE::TotalResource> vResources; //리소스 뭉치

    State state;
    Direction dir;

    ENGINE::SpriteRenderer* renderer;
    ENGINE::AnimationComponent* anim;

    VOID Move(const FLOAT& deltaTime);

public:
    Character();
    //Character(const std::string& charName, const std::vector<char>& items);
    ~Character();

    void CheckInventory(int itemID) const;

    //---------------------------------------------------
    // GameObject을(를) 통해 상속됨
    virtual VOID SetScale(CONST Vector2& scale) override;

    //---------------------------------------------------
    VOID Initialize();
    VOID Release();
    VOID Update(const FLOAT& deltaTime);
    VOID Draw();
};