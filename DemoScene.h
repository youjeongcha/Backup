//#include "EngineMecro.h"
//#include "Components/SpriteRenderer.h"
//#include "Components/SpriteAnimation.h"
//#include "Components/InputComponent.h"
//#include "UIManager.h"
#include "Player.h"
#include "Door.h"
#include "Window.h"

#ifndef DEMO_SCENE_H
#define DEMO_SCENE_H

using namespace ENGINE;

//class Player : public GameObject
//{
//	enum Data { SpritesX = 4, SpritesY = 2, Speed = 200 };
//	enum class State { Idle, Move };
//	enum class Direction { Right, Left };
//
//	State state;
//	Direction dir;
//
//	SpriteRenderer* renderer;
//	AnimationComponent* anim;
//public:
//	Player();
//
//	// GameObject��(��) ���� ��ӵ�
//	virtual VOID SetScale(CONST Vector2& scale) override;
//
//	VOID Initialize();
//	VOID Release();
//	VOID Update(const FLOAT& deltaTime);
//	VOID Draw();
//private:
//	VOID Move(const FLOAT& deltaTime);
//};

class DemoScene : public Scene
{
	BOOL isPause;
	INT bounds;

	//���� �߰�
	//Door door;
	//Window window;

	Bitmap* background = nullptr;
	//Bitmap* door = nullptr; //
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



};

#endif // !DEMO_SCENE_H