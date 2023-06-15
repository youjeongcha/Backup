#pragma once
#include "Character.h"


class Player : public Character {
private:


public:
    Player();
    //Player(const std::string& playerName, const std::vector<int>& items, const std::string& path);
    ~Player();

    //TODO::인벤토리 보여주기
    void Inventory();

    // 플레이어에게 특화된 함수들...

    
};