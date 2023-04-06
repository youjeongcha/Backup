#pragma once
#include "BitMapManager.h"

//#define MOVE_SPEED 0.1
#define MOVE_SPEED 0.1
//#define JUMP_SPEED 0.03
#define PERFORMANCE_SPEED 0.4

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


enum CHARACTER_JUMP
{
	CHARACTER_JUMP_NONE,
	CHARACTER_JUMP_UP,
	CHARACTER_JUMP_DOWN,

	///CHARACTER_JUMP_GAP = 10,
	CHARACTER_JUMP_GAP = 300,

	CHARACTER_JUMP_MAX_Y = IMG_CHARACTER_Y - 100, //���� ���� ��ġ
	CHARACTER_JUMP_MIN_Y = IMG_CHARACTER_Y, //���� ���� ��ġ == ó���� Y
};

enum WIN_PERFORMANCE
{
	//WIN_PERFORMANCE_X = 0,
	//WIN_PERFORMANCE_Y = 0,
	
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
	float m_MoveTime;
	float m_JumpTime;
	float m_PerformanceTime;

	CHARACTER_JUMP m_JumpState; //ĳ������ ���� ���¸� �Ǻ�(�Ϲ�, ���� ���, ���� �ϰ�)
	//�̵��Ÿ�
	float m_TravelDistance;
	//�̵� Ű�� ��������
	CHARACTER_MOVE m_MoveKey;


	void Update_Animation(float deltaTime);
	void Update_Input();
	float Update_Move(float deltaTime);
	void Update_Jump(float deltaTime);

public:
	Character();
	~Character();

	//�ʱ� ����
	void InitialSet();

	float Update(float deltaTime);
	void Draw(HDC hdc);

	//���� �¸� �� �����ս�
	void UpdatePerformance(float deltaTime);
	//ĳ���͸� goal �߾����� �̵���Ų��.
	void Set_XY_GoalMid();

	//��� ���� : ����� 0�� �� ��� ��� ���Ұ� �Ұ��ϹǷ� false�� �����ϰ� GameOver�� �ȴ�.
	bool ReductionLife_End();


	float Get_TravelDistance() { return m_TravelDistance; }
	RECT* Get_CharacterRect() { return &m_CharcterRect; }
	int Get_CharacterLife() { return m_Life; }

	void Set_PerformanceMotion() { m_IMG_NowMotion = IMG_CHARACTER_GOAL_1; }
};

