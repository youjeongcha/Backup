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

enum SCENE
{
	SCENE_DOOR,
	SCENE_KITCHEN,
	SCENE_BEDROOM,
	SCENE_COUNT,
};

class DemoScene : public Scene
{
	SCENE nowScene; //���� ���� � ������

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

	//�� ��ȯ
	void ChangeScene(SCENE changeScene);

};

#endif // !DEMO_SCENE_H