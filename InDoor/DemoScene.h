//#include "EngineMecro.h"
//#include "Components/SpriteRenderer.h"
//#include "Components/SpriteAnimation.h"
//#include "Components/InputComponent.h"
//#include "UIManager.h"
#include "Player.h"
#include "Door.h"
#include "Window.h"
#include "GameManager.h"
//#include "Singleton.h"

#ifndef DEMO_SCENE_H
#define DEMO_SCENE_H

using namespace ENGINE;



//struct Clock
//{
//	int hour;
//	int min;
//	int sec;
//};

//enum TimeLine
//{
//	TimeLine_Start = 8, //게임 시작 시간
//	TimeLine_MORING = 6,
//	TimeLine_NIGHT = 20,
//	TimeLine_ONEDAY = 24,
//};

class DemoScene : public Scene
//class DemoScene : public Singleton<DemoScene>
{
	SCENE nowScene; //현재 맵이 어떤 맵인지

	BOOL isPause;
	INT bounds;

	////시간 흐름
	//Clock m_Clock;
	//float accumulatedSec; //시간 누적 카운트(deltaTime이용)
	//bool isMoring;
	//TimeLine nowTimeLine, oldTimeLine; //시간이 바뀐 순간을 감지하기 위해서
	//float m_Sec;
	//UILabel* timeLabel;
	//bool isDrak; //밤 어둠 깔기 확인


	Bitmap* background = nullptr;
	//Bitmap* night = nullptr;
	Player* player = nullptr;
	Transform* playerTr = nullptr;
	SpriteRenderer* playerSr = nullptr;

	UIButton* pauseBtn;
	UIImage* pauseWindow; //명칭 변경하기

public:
	// Scene을(를) 통해 상속됨
	virtual VOID Initialize() override;
	virtual VOID Release() override;
	virtual VOID Update(const FLOAT& deltaTime) override;
	virtual VOID Draw() override;


	VOID PauseBtnClickHandler();
	VOID ContinueBtnClickHandler();
	VOID QuitBtnClickHandler();

	//씬 전환
	void ChangeScene(); //좌우 이동 끝단으로 가면 씬이 전환된다.
	////시간 전달
	//Clock GetClock() { return m_Clock; }
	//void SetPlusHour(int plusHour); //시간 추가

//	friend Singleton;

//#define GameMgr DemoScene::GetInstance()
};

#endif // !DEMO_SCENE_H