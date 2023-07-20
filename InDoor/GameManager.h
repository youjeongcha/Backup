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
	ENGINE::Bitmap* underSection = nullptr;
	ENGINE::UIImage* select_Restart = nullptr;
	int gameOver_X, gameOver_Y;

	//���ӿ��� or ����Ŭ����(������ ����)
	bool isGameOver, isGameClear;


	//�ð� �帧
	//float accumulatedSec; //�ð� ���� ī��Ʈ(deltaTime�̿�)
	float m_elapsedSec, m_elapsedMin; // ��� �ð� (��, �� ����)
	Clock m_Clock;
	TimeLine nowTimeLine, oldTimeLine; //�ð��� �ٲ� ������ �����ϱ� ���ؼ�

	ENGINE::UILabel* timeLabel;
	ENGINE::UILabel* txtLabel;
	//ENGINE::UIImage* underTxt_UI;
	//ENGINE::UIImage* underTxt_UI;
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

	//���� ȭ�� ����

	//�÷��̾� ����(Ÿ class������ ȣ�� �Լ�)
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

