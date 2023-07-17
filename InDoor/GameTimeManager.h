#pragma once
#include "Singleton.h"
#include "DemoScene.h"

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

class GameTimeManager : public Singleton<GameTimeManager>
{
private:

	//�ð� �帧
	float accumulatedSec; //�ð� ���� ī��Ʈ(deltaTime�̿�)
	Clock m_Clock;
	TimeLine nowTimeLine, oldTimeLine; //�ð��� �ٲ� ������ �����ϱ� ���ؼ�

	ENGINE::UILabel* timeLabel;
	bool isDrak; //�� ��� ��� Ȯ��

	GameTimeManager();
public:
	~GameTimeManager();
	//�ð� ����
	//Clock GetClock() { return m_Clock; }
	void SetPlusHour(int plusHour); //�ð� �߰�

	void Update(const FLOAT& deltaTime);


	Clock GetClock() { return m_Clock; }
	//SCENE GetNowScene() { return nowScene; }
	TimeLine GetNowTimeLine() { return nowTimeLine; }
	TimeLine GetOldTimeLine() { return oldTimeLine; }
	bool GetIsDark() { return isDrak; }
	UILabel* GetTimeLabel() { return timeLabel; }

	void SetClock(Clock _Clock) { m_Clock = _Clock; }
	//void SetNowScene(SCENE _nowScene) { nowScene = _nowScene; }
	void SetNowTimeLine(TimeLine _nowTimeLine) { nowTimeLine = _nowTimeLine; }
	//void SetOldTimeLine() { oldTimeLine = nowTimeLine; }

	friend Singleton;
#define GameTimeMgr GameTimeManager::GetInstance()
};

