#pragma once
#include "Character.h"
#include "Object.h"


class Player : public Character {
private:
    bool isSpace; //�����̽��� ������ üũ //�÷��̾ �ϸ� �Ǵµ�
    std::vector<Object*> interObject; //���� ��ȣ�ۿ� ������ �������� ��´�.

public:
    Player();
    //Player(const std::string& playerName, const std::vector<int>& items, const std::string& path);
    ~Player();

    //TODO::�κ��丮 �����ֱ�
    void Inventory();
    VOID Update(const FLOAT& deltaTime) override;
    // �÷��̾�� Ưȭ�� �Լ���...

    
};