#pragma once
#include "BaseGameEntity.h"

#define ORIGINAL 0x0007

//시간
#define NIGHTTIME 10000 //0~10000
#define DAYTIME 20000 //10001~20000

//저장량
#define MAX_BLOOD 10 //최대 저장 피
#define MAX_MAGI 10 //최대 저장 마기
#define MAX_FRUIT 5 //맺는 열매의 양(5개 모으면 떨굼)

//과일
#define BLOOD_OFPRODUCING_FRUIT 3 //과일을 생성하는데 필요한 피
#define MAGI_OFPRODUCING_FRUIT 3 //과일을 생성하는데 필요한 마기

//탐지
#define DETECTING_BLOOD 2 //탐지를 시작하는 피의 양

//먹이 피 뽑기
#define BLOODDRAW_COUNT 3 //먹이에서 몇 회 피를 뽑을 수 있는가
#define BLOODDRAW 5 //먹이에서 한번에 뽑을 수 있는 피

class EvilPlant;
class State
{
public:
	virtual ~State() {}

	virtual void Enter(EvilPlant*) abstract;
	virtual void Excute(EvilPlant*) abstract;
	virtual void Exit(EvilPlant*) abstract;
};

class EvilPlant : public BaseGameEntity
{
private:
	State* m_CurrState;

	//저장한 피
	int m_SavedBlood; 
	//저장한 마기
	int m_SavedMagi;
	//맺혀있는 열매
	int m_Fruit;

	//공격 가능 범위에 걸린 동물이 있는지
	bool m_AttackPossibleCheck;
	//사로잡은 동물이 있는지 확인
	bool m_CaptiveAnimalCheck;
	//현재 잡은 생물에게서 피 뽑을 수 있는 횟수 //인간, 몬스터 포함 
	int m_AnimalBlood_Count;

	//휴식기 체크
	bool m_RestCheck;
	//열매 맺고 들어갈 휴식기 풀로 쉬기
	bool m_MaxFruitRestCheck;

	//죽음 체크
	bool m_LiveCheck;

	//열매 맺기 가능 체크
	bool m_ProuduceFruitCheck;

public:
	EvilPlant(const int& id);
	virtual ~EvilPlant() {}

	bool Update() override;
	void ChangeState(State*);

	//피
	//void AddBlood(const int& value);
	bool LackBlood() const;
	bool EmptyBlood() const;
	int Get_Blood() const { return m_SavedBlood; }

	//마기
	bool EmptyMagiCheck() const;
	bool LackMagi() const;
	int Get_Magi() const { return m_SavedMagi; }

	//공격 가능한 범위에 동물 있는지 bool 리턴
	void Set_AttackPossibleCheck(const bool& value);
	bool AttackPossibleCheck() const { return m_AttackPossibleCheck; }

	//동물 잡음
	void CaptiveAnimal();
	//사로잡은 먹이가 있는지 확인
	bool CaptiveAnimalCheck() const { return m_CaptiveAnimalCheck; }
	//먹이의 피를 뽑을 수 있는지 + 없으면 잡은 먹이 false 변환
	bool DrawBloodCheck();
	//먹이 피 뽑기
	void DrawBlood();
	
	//열매 생성 가능 변동 + 리턴
	bool ProuduceFruitCheck();
	//마기3, 피3으로 열매를 만든다
	void ProuduceFruit();
	//가지고 있는 열매의 갯수를 리턴
	int CountFruit() const { return m_Fruit; }
	//5개가 차있는지 확인
	bool MaxFruit() const;
	//열매를 떨군다.
	void DropFruit() { m_Fruit = 0; }

	//휴식기 세팅
	void RestSetting(const bool& value) { m_RestCheck = value; }
	//휴식기 상태 체크
	bool RestCheck() const { return m_RestCheck; }
	//열매 5게 휴식기 세팅 or 해제
	void MaxFruitRestSetting(const bool& value) { m_MaxFruitRestCheck = value; }
	//열매 5개 휴식기 풀 체크
	bool MaxFruitRestCheck() const { return m_MaxFruitRestCheck; }
	
	//죽음 체크 멤버 함수 상태 변경
	void DeathSetting() { m_LiveCheck = false; };
	//죽음 체크 멤버 함수 리턴
	bool LiveCheck() const { return m_LiveCheck; };
};

