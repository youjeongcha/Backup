#pragma once
#include "EvilPlant.h"

#define ONESEC 1000

//class PrintState
//{
//public:
//	void PrintSaved(std::string ID, int blood, int magi);
//};

//���� ���Ű� 15���� �Ǹ� �޽ı⿡ ������(5��)
//���� ������ ���⳪ �ǰ� �����ϸ� �޽ı�
class BreakTime : public State
{
private:
	int m_Sec; //�� ���� �ð� üũ�� clock���� �ϰ� �ְ� ���� �Լ��� �� �� �������� sec�� ���� �־ ���� �߻�(�������� ��� �ٶ�)
	int m_OldClock;

	BreakTime() {}
	//�Ʒ� �� �ڵ�� �̱��濡�� ���Ǹ� �ȵǴ� �ڵ��̱� ������ private���� ���Ƶ� ��(����. ���� �ʿ�X)
	BreakTime(const BreakTime&);
	BreakTime& operator=(const BreakTime&);
public:
	static BreakTime* Instance();

	virtual void Enter(EvilPlant*);
	virtual void Excute(EvilPlant*);
	virtual void Exit(EvilPlant*);
};


//���̰� ����, ���� �αⰡ ���� ���
class DetectAnimal : public State
{
private:
	int m_Sec;//�� ���� �ð� üũ�� clock���� �ϰ� �ְ� ���� �Լ��� �� �� �������� sec�� ���� �־ ���� �߻�(�������� ��� �ٶ�)
	int m_OldClock;

	//Ž���� Excute�� �ٷ� �����ϱ� ������ ������ �ʱ�ȭ �ʼ� 
	DetectAnimal();
	DetectAnimal(const DetectAnimal&);
	DetectAnimal& operator=(const DetectAnimal&);
public:
	static DetectAnimal* Instance();

	virtual void Enter(EvilPlant*);
	virtual void Excute(EvilPlant*);
	virtual void Exit(EvilPlant*);
};


//���� ��Ƽ� �ǻ̴� �߿��� �������� ���� ����
class AttackMode : public State
{
private:
	AttackMode() {}
	AttackMode(const AttackMode&);
	AttackMode& operator=(const AttackMode&);
public:
	static AttackMode* Instance();

	virtual void Enter(EvilPlant*);
	virtual void Excute(EvilPlant*);
	virtual void Exit(EvilPlant*);
};


//��Ƶ� ���̰� ������ �Ǹ� 3ȸ �̴´�.
//�޽ı��, Ž�� �����ϰ� �ߵ�.
class DrawBlood : public State
{
private:
	DrawBlood() {}
	DrawBlood(const DrawBlood&);
	DrawBlood& operator=(const DrawBlood&);
public:
	static DrawBlood* Instance();

	virtual void Enter(EvilPlant*);
	virtual void Excute(EvilPlant*);
	virtual void Exit(EvilPlant*);
};


//���� �α�
class MakeFruit : public State
{
private:
	MakeFruit() {}
	MakeFruit(const MakeFruit&);
	MakeFruit& operator=(const MakeFruit&);
public:
	static MakeFruit* Instance();

	virtual void Enter(EvilPlant*);
	virtual void Excute(EvilPlant*);
	virtual void Exit(EvilPlant*);
};