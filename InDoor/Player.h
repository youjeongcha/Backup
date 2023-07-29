#pragma once
#include "Character.h"
#include "Object.h"
//#include "ItemManager.h"

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
   /* bool isInventory;*/
    std::vector<Object*> interObject; //���� ��ȣ�ۿ� ������ �������� ��´�.
    //std::vector<ITEM> itemList; 
    

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
    
    //bool GetIsInventory() { return isInventory; }
    //void SetIsInventory(bool _isInventory) { isInventory = _isInventory; }

   // std::vector<std::pair<ITEM, int>> GetItemList() { return itemList; }
    //RECT Get_Rect() { return renderer->GetRect(); }
};