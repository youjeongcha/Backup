#pragma once
#include "BitMapManager.h"
#include "framework.h"

#define MOVE_SPEED 0.1
#define PERFORMANCE_SPEED 0.4
#define BUMP_TIME 1

enum LIFE
{
	LIFE_MAX = 3,
};

enum CHARACTER_MOVE
{
	CHARACTER_MOVE_NONE,
	CHARACTER_MOVE_LEFT,
	CHARACTER_MOVE_RIGHT,
};




enum WIN_PERFORMANCE //Ŭ���� �۸�ս��� XY��ǥ
{
	WIN_PERFORMANCE_X = GOAL_IMG_ARRIVE_X,// + GOAL_IMG_W / 2,
	WIN_PERFORMANCE_Y = GOAL_IMG_Y - IMG_CHARACTER_H + 7,
};

class Character
{
private:
	float m_X;
	float m_Y;
	RECT m_CharcterRect; //TODO::Rect�� xy�� Draw�� �����Ѵ�.
	//���� ���
	int m_Life;
	IMG m_IMG_NowMotion;
	float m_AnimationTime;

	CHARACTER_JUMP m_JumpState; //ĳ������ ���� ���¸� �Ǻ�(�Ϲ�, ���� ���, ���� �ϰ�)
	//�̵��Ÿ�
	float m_TravelDistance;
	//��ֹ� �ε����� ���� �̵��Ÿ�(������ ĳ������ ����̵� ���� X��ǥ�� ���� 
	float m_Prev_TravelDiatance;
	//�̵� Ű�� ��������
	CHARACTER_MOVE m_MoveKey;
	//���� object�� ���� ��������
	BUMP_CHECK m_Bump_Check;


	void Update_Input();
	float Update_Move(float deltaTime);
	void Update_Jump(float deltaTime);

public:
	Character();
	~Character();

	//�ʱ� ����
	void InitialSet(SET setType);

	float Update(float deltaTime);
	void Update_Animation(float deltaTime); //GameClear�ϰ� Animation �����ٶ� ���� �Ǹ� �ȵǹǷ� �̰͸� ���� ȣ��
	void Draw(HDC hdc);

	//ĳ���͸� goal �߾����� �̵���Ų��.
	void Set_XY_GoalMid();

	//��� ���� : ����� 0�� �� ��� ��� ���Ұ� �Ұ��ϹǷ� false�� �����ϰ� GameOver�� �ȴ�.
	bool ReductionLife_End();
	//ĳ���Ͱ� ��ֹ��� �������� ������ ���� ������ ��츸 ���� ������ ����.(�ڷ� ������ ����X)
	bool MoveRightCheck();

	RECT* Get_CharacterRect() { return &m_CharcterRect; }


	float Get_TravelDistance() { return m_TravelDistance; }
	//��ֹ� �ε����� ���� ��µ� M value���� ���� �ľ��ϱ� ����
	//ĳ���� �̵� �Ÿ����� ���� ����Ǵ� Value�� ���� �ٸ���
	float Get_Prev_TravelDistance() { return m_Prev_TravelDiatance; }
	int Get_CharacterLife() { return m_Life; }
	BUMP_CHECK Get_Bump_Check() { return m_Bump_Check; }

	void Set_PerformanceMotion() { m_IMG_NowMotion = IMG_CHARACTER_GOAL_1; }
	void Set_Bump_Check(BUMP_CHECK _Bump_Check) { m_Bump_Check = _Bump_Check; };
};

