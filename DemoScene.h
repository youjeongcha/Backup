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
//	// GameObject을(를) 통해 상속됨
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

	//가구 추가
	//Door door;
	//Window window;

	Bitmap* background = nullptr;
	//Bitmap* door = nullptr; //
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



};

#endif // !DEMO_SCENE_H