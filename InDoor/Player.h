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
    bool isSpace; //�����̽��� ������ üũ //�÷��̾ �ϸ� �Ǵµ�
    std::vector<Object*> interObject; //���� ��ȣ�ۿ� ������ �������� ��´�.a

    

public:
    Player();
    //Player(const std::string& playerName, const std::vector<int>& items, const std::string& path);
    ~Player();
    void Initialize() override;

    //TODO::�κ��丮 �����ֱ�
    void Inventory();
    VOID Update(const FLOAT& deltaTime) override;
    // �÷��̾�� Ưȭ�� �Լ���...

    bool GetIsSpace() { return isSpace; }
    void SetIsSpace(bool _isSpace) { isSpace = _isSpace; }
    //RECT Get_Rect() { return renderer->GetRect(); }
};