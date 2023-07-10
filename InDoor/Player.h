#pragma once
#include "Character.h"
#include "Object.h"


class Player : public Character {
private:
    bool isSpace; //스페이스바 누른지 체크 //플레이어만 하면 되는데
    std::vector<Object*> interObject; //현재 상호작용 가능한 가구들을 담는다.

public:
    Player();
    //Player(const std::string& playerName, const std::vector<int>& items, const std::string& path);
    ~Player();

    //TODO::인벤토리 보여주기
    void Inventory();
    VOID Update(const FLOAT& deltaTime) override;
    // 플레이어에게 특화된 함수들...

    
};