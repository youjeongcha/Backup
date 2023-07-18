#pragma once
#include "Character.h"
#include "Object.h"

enum PLAYER_RESPON
{
    PLAYER_RESPON_BED = 60,
    PLAYER_RESPON_LEFT = 10,
    PLAYER_RESPON_RIGHT = 350,
};


class Player : public Character {
private:
    bool isSpace; //스페이스바 누른지 체크 //플레이어만 하면 되는데
    std::vector<Object*> interObject; //현재 상호작용 가능한 가구들을 담는다.a

    

public:
    Player();
    //Player(const std::string& playerName, const std::vector<int>& items, const std::string& path);
    ~Player();
    void Initialize() override;

    //TODO::인벤토리 보여주기
    void Inventory();
    VOID Update(const FLOAT& deltaTime) override;
    // 플레이어에게 특화된 함수들...

    bool GetIsSpace() { return isSpace; }
    void SetIsSpace(bool _isSpace) { isSpace = _isSpace; }
    //RECT Get_Rect() { return renderer->GetRect(); }
};