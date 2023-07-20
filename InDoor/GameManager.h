#pragma once
#include "Singleton.h"
#include "ResourceManager.h"
#include "GUIManager.h"
#include "ObjectManager.h"
#include "Window.h"
//#include "DemoScene.h"

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
{
	TimeLine_Start = 8, //게임 시작 시간
	TimeLine_MORING = 6,
	TimeLine_NIGHT = 20,
	TimeLine_ONEDAY = 24,
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
	std::map <std::string, std::vector<Object*>> mDoorObject;
	//부엌 Object 수정 데이터
	std::map <std::string, std::vector<Object*>> mKitchenObject;
	//침실 Object 수정 데이터
	std::map <std::string, std::vector<Object*>> mBedRoomObject;

	ENGINE::Bitmap* night = nullptr;
	ENGINE::Bitmap* gameOver = nullptr;
	ENGINE::Bitmap* underSection = nullptr;
	ENGINE::UIImage* select_Restart = nullptr;
	int gameOver_X, gameOver_Y;

	//게임오버 or 게임클리어(문열기 가능)
	bool isGameOver, isGameClear;


	//시간 흐름
	//float accumulatedSec; //시간 누적 카운트(deltaTime이용)
	float m_elapsedSec, m_elapsedMin; // 경과 시간 (초, 분 단위)
	Clock m_Clock;
	TimeLine nowTimeLine, oldTimeLine; //시간이 바뀐 순간을 감지하기 위해서

	ENGINE::UILabel* timeLabel;
	ENGINE::UILabel* txtLabel;
	//ENGINE::UIImage* underTxt_UI;
	//ENGINE::UIImage* underTxt_UI;
	bool isDark; //밤 어둠 깔기 확인

	//플레이어 관련
	//플레이어 상태
	int m_health, m_hunger, m_thirst, m_fatigue;
	//bool m_isAnyStatOver90; // 90 이상인 수치가 있는지 여부


	GameManager();
public:
	~GameManager();
	
	//txt에서 정보 받아오기
	void LoadData();
	void FileRead(const std::string& file);

	//초기 데이터 설정 (처음 시작 데이터 and 이어하기 데이터 가능 변수에 담긴거에 따라)
	//로드해온 Object 데이터 각 Scene마다 Object 관리하는 변수에 세팅
	void Initialize();
	void Delete_SceneObject();
	void InitSceneData(int _mapIndex, std::map <std::string, std::vector<Object*>>& _Object);
	
	//씬 전환될때 Object의 데이터를 알맞은 씬의 변수에 세이브
	void RenewalSceneData(SCENE saveScene, const std::map <std::string, std::vector<Object*>>& nowSceneObject);
	void DeepCopyMap(std::map<std::string, std::vector<Object*>>& dest, const std::map<std::string, std::vector<Object*>>& src);
	//void ClearSceneData(std::map<std::string, std::vector<Object*>>& sceneData);
	//DemoScene쪽에서 사용할 현재 씬의 데이터를 전달해주는데 사용
	std::map <std::string, std::vector<Object*>> ApplySceneData(SCENE applyScene);

	//시간 전달
	Clock GetClock() { return m_Clock; }
	void SetPlusHour(int plusHour); //시간 추가

	void Update(const FLOAT& deltaTime);
	void Draw();

	//재시작
	void Restart();
	bool GetIsGameOver() { return isGameOver; }


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

	//검은 화면 띄우기

	//플레이어 관련(타 class에서의 호출 함수)
	void PlayerSleep();

	int GetHealth() const { return m_health; }
	int GetHunger() const { return m_hunger; }
	int GetThirst() const { return m_thirst; }
	int GetFatigue() const { return m_fatigue; }

	//void SetHealth(int health) { m_health = health; }
	//void SetHunger(int hunger) { m_hunger = hunger; }
	//void SetThirst(int thirst) { m_thirst = thirst; }
	//void SetFatigue(int fatigue) { m_fatigue = fatigue; }

	friend Singleton;
#define GameMgr GameManager::GetInstance()
};

