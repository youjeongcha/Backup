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
	TimeLine_Start = 8, //���� ���� �ð�
	TimeLine_MORING = 6,
	TimeLine_NIGHT = 20,
	TimeLine_ONEDAY = 24,
};

enum UNDER_SECTION
{
	UNDER_SECTION_TRANSPARENCY = 95
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
	//DOOR_OPEN_O,
	DOOR_OPEN_X,
	DOOR_KNOCK_O,
	DOOR_KNOCK_X,

	//����
	DRAWER_IN_O,
	DRAWER_IN_X,

	//ȭ�� //�ش� �κ��� ��� ���� ��� TODO::������ ����α�����, �ؽ�Ʈ�� ������. ���������� ������ ����
	FLOWERPOT_PLANTINGSEED_O,
	FLOWERPOT_PLANTINGSEED_X,
	FLOWERPOT_WATERING_O,
	FLOWERPOT_WATERING_X,
	//�ڶ�� �Ѵ�.
	FLOWERPOT_HARVEST,

	//â�� //���� ��� + ���� �Ұ��� ������ ����
	//WINDOW_SHOW_O,
	//WINDOW_SHOW_X, //Ŀư�� ����������

	//å��(å)
	BOOK_0,

	UNDERTXT_COUNT,
	UNDERTXT_NONE //�� ó�� ���ð�. �ϴ� �ؽ�Ʈ�� ��ȭ�� ���� �ؾ��ϱ� ������
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
	std::map <std::string, std::vector<Object*>> mDoorObject;
	//�ξ� Object ���� ������
	std::map <std::string, std::vector<Object*>> mKitchenObject;
	//ħ�� Object ���� ������
	std::map <std::string, std::vector<Object*>> mBedRoomObject;

	ENGINE::Bitmap* night = nullptr;
	ENGINE::Bitmap* gameOver = nullptr;
	//ENGINE::Bitmap* underSection = nullptr; //Draw�� ����ȭ ���� �ϱ� ���ؼ� Bitmap���� ����
	ENGINE::UIImage* select_Restart = nullptr;
	int gameOver_X, gameOver_Y;

	//���ӿ��� or ����Ŭ����(������ ����)
	bool isGameOver, isGameClear;

	//�ϴ�â txt
	std::map<UNDERTXT, std::string> mUnderTxt;
	UNDERTXT prevShowUnderTxt, nowShowUnderTxt; //�ϴ�â �ؽ�Ʈ ��ȭ�� �����ؾ��� �ε��� ������ �����ϴ�.
	bool isShowUnderTxt; //�ϴ�â �����ֱ�
	int indexShowUnderTxt;

	//�Ͻ�����
	bool isPause;

	//�ð� �帧
	//float accumulatedSec; //�ð� ���� ī��Ʈ(deltaTime�̿�)
	float m_elapsedSec, m_elapsedMin; // ��� �ð� (��, �� ����)
	Clock m_Clock;
	TimeLine nowTimeLine, oldTimeLine; //�ð��� �ٲ� ������ �����ϱ� ���ؼ�

	ENGINE::UILabel* timeLabel;
	ENGINE::UIButton* underTxt_Section; //���� ��ư���� ������ ���� �ؽ�Ʈ�� ���ų� �Ͻ����� �����ǵ���
	//ENGINE::UIImage* underTxt_Btn; //���� ��ư���� ������ ���� �ؽ�Ʈ�� ���ų� �Ͻ����� �����ǵ���
	ENGINE::UILabel* txtLabel;
	//ENGINE::UIImage* underTxt_UI;//Draw�� ����ȭ�� �Ұ����ؼ�
	bool isDark; //�� ��� ��� Ȯ��

	//�÷��̾� ����
	//�÷��̾� ����
	int m_health, m_hunger, m_thirst, m_fatigue;
	//bool m_isAnyStatOver90; // 90 �̻��� ��ġ�� �ִ��� ����


	GameManager();
public:
	~GameManager();
	
	//txt���� ���� �޾ƿ���
	void LoadData();
	void FileRead(const std::string& file);

	//�ʱ� ������ ���� (ó�� ���� ������ and �̾��ϱ� ������ ���� ������ ���ſ� ����)
	//�ε��ؿ� Object ������ �� Scene���� Object �����ϴ� ������ ����
	void Initialize();
	void Delete_SceneObject();
	void InitSceneData(int _mapIndex, std::map <std::string, std::vector<Object*>>& _Object);
	
	//�� ��ȯ�ɶ� Object�� �����͸� �˸��� ���� ������ ���̺�
	void RenewalSceneData(SCENE saveScene, const std::map <std::string, std::vector<Object*>>& nowSceneObject);
	void DeepCopyMap(std::map<std::string, std::vector<Object*>>& dest, const std::map<std::string, std::vector<Object*>>& src);
	//void ClearSceneData(std::map<std::string, std::vector<Object*>>& sceneData);
	//DemoScene�ʿ��� ����� ���� ���� �����͸� �������ִµ� ���
	std::map <std::string, std::vector<Object*>> ApplySceneData(SCENE applyScene);

	
	//�ϴ� �ؽ�Ʈâ
	void LoadUnderTxt();
	void ShowUnderSectionTxt(UNDERTXT showTxt);
	//void DisableUnderSection(); //�ϴ� â ������ > �Ͻ����� ����, �ϴ�â ��Ȱ�� or ���� txt�ѱ�, txt��Ȱ��(???????
	void NextShowUnderSection(bool isNextTxt); //�ϴ� â ������ > �Ͻ����� ����, �ϴ�â ��Ȱ�� or ���� txt�ѱ�, txt��Ȱ��(???????

	//�Ͻ����� ����
	//void SetPause(bool isPause) { ENGINE::GUIMgr->Set_IsPause(isPause); }
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

	//void SetHealth(int health) { m_health = health; }
	//void SetHunger(int hunger) { m_hunger = hunger; }
	//void SetThirst(int thirst) { m_thirst = thirst; }
	//void SetFatigue(int fatigue) { m_fatigue = fatigue; }

	friend Singleton;
#define GameMgr GameManager::GetInstance()
};

