#pragma once
#include "Character.h"
#include "Object.h"

#define VK_I 0x49

enum PLAYER_RESPON
{
    PLAYER_RESPON_BED = 60,
    PLAYER_RESPON_LEFT = 10,
    PLAYER_RESPON_RIGHT = 350,
};


class Player : public Character 
{
private:
    bool isSpace; //�����̽��� ������ üũ //�÷��̾ �ϸ� �Ǵµ�
    std::vector<Object*> interObject; //���� ��ȣ�ۿ� ������ �������� ��´�.

public:
    Player();
    //Player(const std::string& playerName, const std::vector<int>& items, const std::string& path);
    ~Player();
    void Initialize() override;

    VOID Update(const FLOAT& deltaTime) override;

    bool GetIsSpace() { return isSpace; }
    void SetIsSpace(bool _isSpace) { isSpace = _isSpace; }  
};