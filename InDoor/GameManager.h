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
{//게임내 시간 기준
	//기준 시간(~부터~까지)
	TimeLine_Start = 8, //게임 시작 시간
	TimeLine_MORING = 6, //아침 시작
	TimeLine_NIGHT = 20, //밤 시작
	TimeLine_ONEDAY = 24, //하루 총 시간

	//경과 시간(~동안~지나야) 
	TimeLine_PlantGrowth = 6, //식물 성장 경과 시간
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

	//침대
	BED_SLEEP_X = UNDERTXT_START,  //잠자기는 허기와 갈증이 30 미만에 가능
	BED_SLEEP_O, //일반적으로 잠든경우
	BED_SLEEP_O_HEALTH, //건강 +10
	BED_SLEEP_O_HEALTH_GAMECLEAR, //건강  +10 클리어 판정 > 문 열수 있다.

	//옷장
	CLOSET_IN_O,
	CLOSET_IN_X,

	//커튼
	CURTAIN_OPEN,
	CURTAIN_CLOSE,

	//문
	DOOR_OPEN_O,
	DOOR_OPEN_X,
	DOOR_KNOCK_O,
	DOOR_KNOCK_X,

	//서랍
	DRAWER_IN_O,
	DRAWER_IN_X,

	//화분 //해당 부분을 어떻게 할지 고민 TODO::선택지 감춰두기할지, 텍스트로 막을지. 개인전으로 선택지 막기
	//씨앗 심기
	FLOWERPOT_PLANTINGSEED_O,
	FLOWERPOT_PLANTINGSEED_X, //인벤토리에 씨앗이 없음
	//물주기
	FLOWERPOT_WATERING_O,
	FLOWERPOT_WATERING_X, //물이 이미 충분함
	//수확 성공
	FLOWERPOT_HARVEST,
	//현재 성장 진도에 적합하지 않은 작업일 경우
	FLOWERPOT_INCORRECTCHOICE,

	//창문 //실행 즉시 + 실행 불가면 선택지 막기
	WINDOW_SHOW_O,
	WINDOW_SHOW_X, //커튼에 가려있으면

	//책장(책)
	BOOK_0,

	//화로(요리)
	COOK,

	//물(컵) 가구
	WATER_O,

	//양초
	ONECANDLE_O,
	ONECANDLE_X,


	//----------아이템 사용이후 뜰 텍스트-----------
	USE_WATER,
	//USE_KEY,1 보관함을 열었다.
	USE_FRUIT,
	
	//-----------------------
	//사용 가능한 아이템이 없다.
	DONTHAVE_ITEM,
	//사용할 수 없는 아이템입니다.
	UNDERTXT_NONE, //맨 처음 세팅값. 하단 텍스트의 변화를 감지 해야하기 때문에

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
	//Object 파일 입출력 불러온 데이터
	std::map <std::string, ObjectData> objectData; //새로하기, 이어하기 따라 담는 데이터 달라질 예정
	//현관 Object 수정 데이터
	std::vector<Object*> mDoorObject;
	//부엌 Object 수정 데이터
	std::vector<Object*> mKitchenObject;
	//침실 Object 수정 데이터
	std::vector<Object*> mBedRoomObject;

	//현관 Object 수정 데이터
	//std::map <std::string, std::vector<Object*>> mDoorObject;
	////부엌 Object 수정 데이터
	//std::map <std::string, std::vector<Object*>> mKitchenObject;
	////침실 Object 수정 데이터
	//std::map <std::string, std::vector<Object*>> mBedRoomObject;

	ENGINE::Bitmap* night = nullptr;
	ENGINE::Bitmap* gameOver = nullptr;
	ENGINE::UIImage* select_Restart = nullptr;
	int gameOver_X, gameOver_Y;

	//게임오버 or 게임클리어(문열기 가능)
	bool isGameOver, isGameClear;
	bool isReset_OneTime; //게임오버되고 게임 리셋 함수(맵, 플레이어 위치) 1회 실행


	//하단창 txt
	std::map<UNDERTXT, std::vector<std::string>> mUnderTxt;
	UNDERTXT prevShowUnderTxt, nowShowUnderTxt; //하단창 텍스트 변화를 감지해야지 인덱스 세팅이 가능하다.
	bool isShowUnderTxt; //하단창 보여주기
	int indexShowUnderTxt;

	//일시정지
	bool isPause;

	//시간 흐름
	float m_elapsedSec, m_elapsedMin; // 경과 시간 (초, 분 단위)
	Clock m_Clock;
	TimeLine nowTimeLine, oldTimeLine; //시간이 바뀐 순간을 감지하기 위해서

	ENGINE::UIImage* Inventory_UI; //인벤토리
	ENGINE::UIImage* Inventory_UI_ItemDetaiInfo; //인벤토리 > 아이템 이미지 + 상세 정보
	ENGINE::UIImage* Inventory_UI_ItemUseSelect; //인벤토리 > 아이템 사용/취소
	ENGINE::UILabel* timeLabel;
	ENGINE::UIButton* underTxt_Section; //투명 버튼으로 누르면 다음 텍스트를 띄우거나 일시정지 해제되도록
	ENGINE::UILabel* txtLabel;
	bool isDark; //밤 어둠 깔기 확인

	//플레이어 관련
	//플레이어 상태
	int m_health, m_hunger, m_thirst, m_fatigue;


	//인벤토리 관련
	//std::vector<std::pair<ITEM, int>> player_ItemList; //플레이어가 지닌 아이템들 + 수량
	std::vector<InventoryItem> player_ItemList; //플레이어가 지닌 아이템 //InventoryItem 아이템 + 수량


	//인벤토리를 연 상태인지 체크
	bool isInventory;


	GameManager();
public:
	~GameManager();
	
	//txt에서 정보 받아오기
	void LoadData();
	void FileRead(const std::string& file);

	//초기 데이터 설정 (처음 시작 데이터 and 이어하기 데이터 가능 변수에 담긴거에 따라)
	//로드해온 Object 데이터 각 Scene마다 Object 관리하는 변수에 세팅
	void Initialize();
	void Reset_SceneObject();
	//void InitSceneData(int _mapIndex, std::map <std::string, std::vector<Object*>>& _Object);
	void InitSceneData(int _mapIndex, std::vector<Object*>& _Object);
	
	//씬 전환될때 Object의 데이터를 알맞은 씬의 변수에 세이브
	void RenewalSceneData(SCENE saveScene, const std::vector<Object*>& nowSceneObject);
	//void DeepCopyMap(std::map<std::string, std::vector<Object*>>& saveData, const std::vector<Object*>& nowSceneObject);
	void DeepCopyMap(std::vector<Object*> &saveData, const std::vector<Object*>& nowSceneObject);
	//DemoScene쪽에서 사용할 현재 씬의 데이터를 전달해주는데 사용
	//std::map <std::string, std::vector<Object*>> ApplySceneData(SCENE applyScene);
	std::vector<Object*> ApplySceneData (SCENE applyScene);
	
	//하단 텍스트창
	void LoadUnderTxt();
	void ShowUnderSectionTxt();
	void NextShowUnderSection(bool isNextTxt); //하단 창 누르면 > 일시정지 해제, 하단창 비활성 or 다음 txt넘김, txt비활성(???????
	void SetShowUnder(UNDERTXT _nowShowUnderTxt) { isShowUnderTxt = true; nowShowUnderTxt = _nowShowUnderTxt; } //하단 텍스트가 떠야하는 선택지 작동 함수
		

	//일시정지 조정
	void Set_IsPause(bool pauseSet) { isPause = pauseSet; }
	bool Get_IsPause() { return isPause; }

	//시간 전달
	Clock GetClock() { return m_Clock; }
	void SetPlusHour(int plusHour); //시간 추가

	void Update(const FLOAT& deltaTime);
	void Draw();

	//재시작
	void Restart();
	bool GetIsGameOver() { return isGameOver; }

	//게임 클리어 > 문 열기 가능
	bool GetIsGameClear() { return isGameClear; }
	//게임 재시작할때 리셋 함수 한번만 실행 관리 위해
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

	//플레이어 관련(타 class에서의 호출 함수)
	void PlayerSleep(); //잠들기 가능 불가능 > 하단 텍스트 차이 두기

	int GetHealth() const { return m_health; }
	int GetHunger() const { return m_hunger; }
	int GetThirst() const { return m_thirst; }
	int GetFatigue() const { return m_fatigue; }

	void PlusHealth(int health) { m_health += health; if (m_health < 0) m_health = 0; else if (m_health > 100) m_health = 100; }
	void PlusHunger(int hunger) { m_hunger += hunger; if (m_hunger < 0) m_hunger = 0; else if (m_hunger > 100) m_hunger = 100; }
	void PlusThirst(int thirst) { m_thirst += thirst; if (m_thirst < 0) m_thirst = 0; else if (m_thirst > 100) m_thirst = 100; }
	void PlusFatigue(int fatigue) { m_fatigue += fatigue; if (m_fatigue < 0) m_fatigue = 0; else if (m_fatigue > 100) m_fatigue = 100; }

	//인벤토리
	void Inventory_Panel(Player& player);
	//void PlusPlayerInventory(std::pair<ITEM, int> item) { player_ItemList.push_back(item); }
	void PlusPlayerInventory(InventoryItem item); //인벤토리에 아이템 추가
	bool MinusPlayerItem(ITEM_ID itemID); //아이템 사용 1개 감소(아이템이 있으면 ture, 없으면 false;
	int GetCountPlayerItem(ITEM_ID itemID);	
	void ItemUseBtnClickHandler(Item* useItem); //인벤토리 에서 아이템 상세정보 + 사용/취소 판넬 띄우기
	void Cancel_InventoryBtnClickHandler(); //인벤토리 창 끄기
	//아이템 사용
	//void ItemDetaiInfo_Panel(Item* useItem); //아이템 이미지 + 상세정보 있는 판넬
	void ItemUse_Panel(Item* useItem); //아이템 이미지 + 상세정보 있는 판넬 //아이템 사용/취소 버튼 있는 판넬
	void Cancel_ItemUseSelectBtnClickHandler(); //아이템 상세정보 판넬 끄기
	//void Reset_Inventory();
	//인벤토리 사용유무 체크
	void SetIsInventory(bool _isInventory) { isInventory = _isInventory; }
	bool GetIsInventory() { return isInventory; }

	friend Singleton;
#define GameMgr GameManager::GetInstance()
};