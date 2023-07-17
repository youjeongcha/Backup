#pragma once
#include "Singleton.h"
#include "DemoScene.h"

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

class GameTimeManager : public Singleton<GameTimeManager>
{
private:

	//시간 흐름
	float accumulatedSec; //시간 누적 카운트(deltaTime이용)
	Clock m_Clock;
	TimeLine nowTimeLine, oldTimeLine; //시간이 바뀐 순간을 감지하기 위해서

	ENGINE::UILabel* timeLabel;
	bool isDrak; //밤 어둠 깔기 확인

	GameTimeManager();
public:
	~GameTimeManager();
	//시간 전달
	//Clock GetClock() { return m_Clock; }
	void SetPlusHour(int plusHour); //시간 추가

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

