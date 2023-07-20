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
//	TimeLine_Start = 8, //���� ���� �ð�
//	TimeLine_MORING = 6,
//	TimeLine_NIGHT = 20,
//	TimeLine_ONEDAY = 24,
//};

class DemoScene : public Scene
//class DemoScene : public Singleton<DemoScene>
{
	SCENE nowScene; //���� ���� � ������

	BOOL isPause;
	INT bounds;

	////�ð� �帧
	//Clock m_Clock;
	//float accumulatedSec; //�ð� ���� ī��Ʈ(deltaTime�̿�)
	//bool isMoring;
	//TimeLine nowTimeLine, oldTimeLine; //�ð��� �ٲ� ������ �����ϱ� ���ؼ�
	//float m_Sec;
	//UILabel* timeLabel;
	//bool isDrak; //�� ��� ��� Ȯ��


	Bitmap* background = nullptr;
	//Bitmap* night = nullptr;
	Player* player = nullptr;
	Transform* playerTr = nullptr;
	SpriteRenderer* playerSr = nullptr;

	UIButton* pauseBtn;
	UIImage* pauseWindow; //��Ī �����ϱ�

public:
	// Scene��(��) ���� ��ӵ�
	virtual VOID Initialize() override;
	virtual VOID Release() override;
	virtual VOID Update(const FLOAT& deltaTime) override;
	virtual VOID Draw() override;


	VOID PauseBtnClickHandler();
	VOID ContinueBtnClickHandler();
	VOID QuitBtnClickHandler();

	//�� ��ȯ
	void ChangeScene(); //�¿� �̵� �������� ���� ���� ��ȯ�ȴ�.
	////�ð� ����
	//Clock GetClock() { return m_Clock; }
	//void SetPlusHour(int plusHour); //�ð� �߰�

//	friend Singleton;

//#define GameMgr DemoScene::GetInstance()
};

#endif // !DEMO_SCENE_H