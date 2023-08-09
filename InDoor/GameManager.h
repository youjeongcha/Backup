#pragma once
//#include "Singleton.h"
#include "ResourceManager.h"
#include "GUIManager.h"
#include "ObjectManager.h"
#include "ItemManager.h"
#include "Player.h"

enum SCENE
{
	SCENE_DOOR,
	SCENE_KITCHEN,
	SCENE_BEDROOM,
	SCENE_COUNT,
};

enum Time
{
	TimeSleep = 5,
};

enum TimeLine
{//���ӳ� �ð� ����
	//���� �ð�(~����~����)
	TimeLine_Start = 8, //���� ���� �ð�
	TimeLine_MORING = 6, //��ħ ����
	TimeLine_NIGHT = 20, //�� ����
	TimeLine_ONEDAY = 24, //�Ϸ� �� �ð�

	//��� �ð�(~����~������) 
	TimeLine_PlantGrowth = 6, //�Ĺ� ���� ��� �ð�
};

enum TRANSPARENCY
{
	UNDER_SECTION_TRANSPARENCY = 95,
	INVENTORY_TRANSPARENCY = 200,
	ITEM_TRANSPARENCY = 100
};

enum UNDERTXT
{
	UNDERTXT_START = 0,

	//ħ��
	BED_SLEEP_X = UNDERTXT_START,  //���ڱ�� ���� ������ 30 �̸��� ����
	BED_SLEEP_O, //�Ϲ������� �����
	BED_SLEEP_O_HEALTH, //�ǰ� +10
	BED_SLEEP_O_HEALTH_GAMECLEAR, //�ǰ�  +10 Ŭ���� ���� > �� ���� �ִ�.

	//����
	CLOSET_IN_O,
	CLOSET_IN_X,

	//Ŀư
	CURTAIN_OPEN,
	CURTAIN_CLOSE,

	//��
	DOOR_OPEN_O,
	DOOR_OPEN_X,
	DOOR_KNOCK_O,
	DOOR_KNOCK_X,

	//����
	DRAWER_IN_O,
	DRAWER_IN_X,

	//ȭ�� //�ش� �κ��� ��� ���� ��� TODO::������ ����α�����, �ؽ�Ʈ�� ������. ���������� ������ ����
	//���� �ɱ�
	FLOWERPOT_PLANTINGSEED_O,
	FLOWERPOT_PLANTINGSEED_X, //�κ��丮�� ������ ����
	//���ֱ�
	FLOWERPOT_WATERING_O,
	FLOWERPOT_WATERING_X, //���� �̹� �����
	//��Ȯ ����
	FLOWERPOT_HARVEST,
	//���� ���� ������ �������� ���� �۾��� ���
	FLOWERPOT_INCORRECTCHOICE,

	//â�� //���� ��� + ���� �Ұ��� ������ ����
	WINDOW_SHOW_O,
	WINDOW_SHOW_X, //Ŀư�� ����������

	//å��(å)
	BOOK_0,

	//ȭ��(�丮)
	COOK,

	//��(��) ����
	WATER_O,

	//����
	ONECANDLE_O,
	ONECANDLE_X,


	//----------������ ������� �� �ؽ�Ʈ-----------
	USE_WATER,
	//USE_KEY,1 �������� ������.
	USE_FRUIT,
	
	//-----------------------
	//��� ������ �������� ����.
	DONTHAVE_ITEM,
	//����� �� ���� �������Դϴ�.
	UNDERTXT_NONE, //�� ó�� ���ð�. �ϴ� �ؽ�Ʈ�� ��ȭ�� ���� �ؾ��ϱ� ������

	UNDERTXT_COUNT,
};

struct Clock
{
	int hour;
	int min;
	int sec;
};



class GameManager : public Singleton<GameManager>
{
private:
	//Object ���� ����� �ҷ��� ������
	std::map <std::string, ObjectData> objectData; //�����ϱ�, �̾��ϱ� ���� ��� ������ �޶��� ����
	//���� Object ���� ������
	std::vector<Object*> mDoorObject;
	//�ξ� Object ���� ������
	std::vector<Object*> mKitchenObject;
	//ħ�� Object ���� ������
	std::vector<Object*> mBedRoomObject;

	//���� Object ���� ������
	//std::map <std::string, std::vector<Object*>> mDoorObject;
	////�ξ� Object ���� ������
	//std::map <std::string, std::vector<Object*>> mKitchenObject;
	////ħ�� Object ���� ������
	//std::map <std::string, std::vector<Object*>> mBedRoomObject;

	ENGINE::Bitmap* night = nullptr;
	ENGINE::Bitmap* gameOver = nullptr;
	ENGINE::UIImage* select_Restart = nullptr;
	int gameOver_X, gameOver_Y;

	//���ӿ��� or ����Ŭ����(������ ����)
	bool isGameOver, isGameClear;
	bool isReset_OneTime; //���ӿ����ǰ� ���� ���� �Լ�(��, �÷��̾� ��ġ) 1ȸ ����


	//�ϴ�â txt
	std::map<UNDERTXT, std::vector<std::string>> mUnderTxt;
	UNDERTXT prevShowUnderTxt, nowShowUnderTxt; //�ϴ�â �ؽ�Ʈ ��ȭ�� �����ؾ��� �ε��� ������ �����ϴ�.
	bool isShowUnderTxt; //�ϴ�â �����ֱ�
	int indexShowUnderTxt;

	//�Ͻ�����
	bool isPause;

	//�ð� �帧
	float m_elapsedSec, m_elapsedMin; // ��� �ð� (��, �� ����)
	Clock m_Clock;
	TimeLine nowTimeLine, oldTimeLine; //�ð��� �ٲ� ������ �����ϱ� ���ؼ�

	ENGINE::UIImage* Inventory_UI; //�κ��丮
	ENGINE::UIImage* Inventory_UI_ItemDetaiInfo; //�κ��丮 > ������ �̹��� + �� ����
	ENGINE::UIImage* Inventory_UI_ItemUseSelect; //�κ��丮 > ������ ���/���
	ENGINE::UILabel* timeLabel;
	ENGINE::UIButton* underTxt_Section; //���� ��ư���� ������ ���� �ؽ�Ʈ�� ���ų� �Ͻ����� �����ǵ���
	ENGINE::UILabel* txtLabel;
	bool isDark; //�� ��� ��� Ȯ��

	//�÷��̾� ����
	//�÷��̾� ����
	int m_health, m_hunger, m_thirst, m_fatigue;


	//�κ��丮 ����
	//std::vector<std::pair<ITEM, int>> player_ItemList; //�÷��̾ ���� �����۵� + ����
	std::vector<InventoryItem> player_ItemList; //�÷��̾ ���� ������ //InventoryItem ������ + ����


	//�κ��丮�� �� �������� üũ
	bool isInventory;


	GameManager();
public:
	~GameManager();
	
	//txt���� ���� �޾ƿ���
	void LoadData();
	void FileRead(const std::string& file);

	//�ʱ� ������ ���� (ó�� ���� ������ and �̾��ϱ� ������ ���� ������ ���ſ� ����)
	//�ε��ؿ� Object ������ �� Scene���� Object �����ϴ� ������ ����
	void Initialize();
	void Reset_SceneObject();
	//void InitSceneData(int _mapIndex, std::map <std::string, std::vector<Object*>>& _Object);
	void InitSceneData(int _mapIndex, std::vector<Object*>& _Object);
	
	//�� ��ȯ�ɶ� Object�� �����͸� �˸��� ���� ������ ���̺�
	void RenewalSceneData(SCENE saveScene, const std::vector<Object*>& nowSceneObject);
	//void DeepCopyMap(std::map<std::string, std::vector<Object*>>& saveData, const std::vector<Object*>& nowSceneObject);
	void DeepCopyMap(std::vector<Object*> &saveData, const std::vector<Object*>& nowSceneObject);
	//DemoScene�ʿ��� ����� ���� ���� �����͸� �������ִµ� ���
	//std::map <std::string, std::vector<Object*>> ApplySceneData(SCENE applyScene);
	std::vector<Object*> ApplySceneData (SCENE applyScene);
	
	//�ϴ� �ؽ�Ʈâ
	void LoadUnderTxt();
	void ShowUnderSectionTxt();
	void NextShowUnderSection(bool isNextTxt); //�ϴ� â ������ > �Ͻ����� ����, �ϴ�â ��Ȱ�� or ���� txt�ѱ�, txt��Ȱ��(???????
	void SetShowUnder(UNDERTXT _nowShowUnderTxt) { isShowUnderTxt = true; nowShowUnderTxt = _nowShowUnderTxt; } //�ϴ� �ؽ�Ʈ�� �����ϴ� ������ �۵� �Լ�
		

	//�Ͻ����� ����
	void Set_IsPause(bool pauseSet) { isPause = pauseSet; }
	bool Get_IsPause() { return isPause; }

	//�ð� ����
	Clock GetClock() { return m_Clock; }
	void SetPlusHour(int plusHour); //�ð� �߰�

	void Update(const FLOAT& deltaTime);
	void Draw();

	//�����
	void Restart();
	bool GetIsGameOver() { return isGameOver; }

	//���� Ŭ���� > �� ���� ����
	bool GetIsGameClear() { return isGameClear; }
	//���� ������Ҷ� ���� �Լ� �ѹ��� ���� ���� ����
	bool GetisReset_OneTime() { return isReset_OneTime; }
	void SetisReset_OneTime(bool isReset) { isReset_OneTime = isReset; }


	//Clock GetClock() { return m_Clock; }
	//SCENE GetNowScene() { return nowScene; }
	TimeLine GetNowTimeLine() { return nowTimeLine; }
	TimeLine GetOldTimeLine() { return oldTimeLine; }
	bool GetIsDark() { return isDark; }
	ENGINE::UILabel* GetTimeLabel() { return timeLabel; }

	void SetClock(Clock _Clock) { m_Clock = _Clock; }
	//void SetNowScene(SCENE _nowScene) { nowScene = _nowScene; }
	void SetNowTimeLine(TimeLine _nowTimeLine) { nowTimeLine = _nowTimeLine; }
	//void SetOldTimeLine() { oldTimeLine = nowTimeLine; }

	//�÷��̾� ����(Ÿ class������ ȣ�� �Լ�)
	void PlayerSleep(); //���� ���� �Ұ��� > �ϴ� �ؽ�Ʈ ���� �α�

	int GetHealth() const { return m_health; }
	int GetHunger() const { return m_hunger; }
	int GetThirst() const { return m_thirst; }
	int GetFatigue() const { return m_fatigue; }

	void PlusHealth(int health) { m_health += health; if (m_health < 0) m_health = 0; else if (m_health > 100) m_health = 100; }
	void PlusHunger(int hunger) { m_hunger += hunger; if (m_hunger < 0) m_hunger = 0; else if (m_hunger > 100) m_hunger = 100; }
	void PlusThirst(int thirst) { m_thirst += thirst; if (m_thirst < 0) m_thirst = 0; else if (m_thirst > 100) m_thirst = 100; }
	void PlusFatigue(int fatigue) { m_fatigue += fatigue; if (m_fatigue < 0) m_fatigue = 0; else if (m_fatigue > 100) m_fatigue = 100; }

	//�κ��丮
	void Inventory_Panel(Player& player);
	//void PlusPlayerInventory(std::pair<ITEM, int> item) { player_ItemList.push_back(item); }
	void PlusPlayerInventory(InventoryItem item); //�κ��丮�� ������ �߰�
	bool MinusPlayerItem(ITEM_ID itemID); //������ ��� 1�� ����(�������� ������ ture, ������ false;
	int GetCountPlayerItem(ITEM_ID itemID);	
	void ItemUseBtnClickHandler(Item* useItem); //�κ��丮 ���� ������ ������ + ���/��� �ǳ� ����
	void Cancel_InventoryBtnClickHandler(); //�κ��丮 â ����
	//������ ���
	//void ItemDetaiInfo_Panel(Item* useItem); //������ �̹��� + ������ �ִ� �ǳ�
	void ItemUse_Panel(Item* useItem); //������ �̹��� + ������ �ִ� �ǳ� //������ ���/��� ��ư �ִ� �ǳ�
	void Cancel_ItemUseSelectBtnClickHandler(); //������ ������ �ǳ� ����
	//void Reset_Inventory();
	//�κ��丮 ������� üũ
	void SetIsInventory(bool _isInventory) { isInventory = _isInventory; }
	bool GetIsInventory() { return isInventory; }

	friend Singleton;
#define GameMgr GameManager::GetInstance()
};