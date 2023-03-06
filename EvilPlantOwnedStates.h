#pragma once
#include "EvilPlant.h"

#define ONESEC 1000

//class PrintState
//{
//public:
//	void PrintSaved(std::string ID, int blood, int magi);
//};

//떨군 열매가 15개가 되면 휴식기에 접어든다(5초)
//열매 생성할 마기나 피가 부족하면 휴식기
class BreakTime : public State
{
private:
	int m_Sec; //★ 실제 시간 체크는 clock으로 하고 있고 내부 함수로 한 턴 돌때마다 sec를 세고 있어서 괴리 발생(다음에는 고려 바람)
	int m_OldClock;

	BreakTime() {}
	//아래 두 코드는 싱글톤에서 사용되면 안되는 코드이기 때문에 private으로 막아둔 것(보험. 굳이 필요X)
	BreakTime(const BreakTime&);
	BreakTime& operator=(const BreakTime&);
public:
	static BreakTime* Instance();

	virtual void Enter(EvilPlant*);
	virtual void Excute(EvilPlant*);
	virtual void Exit(EvilPlant*);
};


//먹이가 없고, 열매 맺기가 끝난 경우
class DetectAnimal : public State
{
private:
	int m_Sec;//★ 실제 시간 체크는 clock으로 하고 있고 내부 함수로 한 턴 돌때마다 sec를 세고 있어서 괴리 발생(다음에는 고려 바람)
	int m_OldClock;

	//탐지의 Excute로 바로 시작하기 때문에 생성자 초기화 필수 
	DetectAnimal();
	DetectAnimal(const DetectAnimal&);
	DetectAnimal& operator=(const DetectAnimal&);
public:
	static DetectAnimal* Instance();

	virtual void Enter(EvilPlant*);
	virtual void Excute(EvilPlant*);
	virtual void Exit(EvilPlant*);
};


//동물 잡아서 피뽑는 중에는 선공당할 때만 공격
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


//잡아둔 먹이가 있으면 피를 3회 뽑는다.
//휴식기와, 탐지 제외하고 발동.
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


//열매 맺기
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