#include "EvilPlant.h"
#include "EvilPlantOwnedStates.h"
#include "EntityNames.h"
#include "ConsoleUtils.h"
#include <cassert>

//피가 다 차도 먹이를 잡는다. 저장하는 것은 열매를 맺는데 사용할 수 있는 수치이므로.
//수치를 넘기면 자양분으로 사용된다는 설정.

bool m_nightCheck = true; //TODO::static 변수로 외부에

EvilPlant::EvilPlant(const int& id) :
	BaseGameEntity(id),
	m_SavedBlood(0),
	m_AnimalBlood_Count(0),
	m_SavedMagi(2),
	m_Fruit(0),
	m_CaptiveAnimalCheck(false),
	m_AttackPossibleCheck(false),
	m_LiveCheck(true),
	m_RestCheck(false),
	m_MaxFruitRestCheck(false),
	m_ProuduceFruitCheck(false),
	//m_nightCheck(true),
	m_CurrState(DetectAnimal::Instance())
{
	std::cout << " ---------------------  밤  ---------------------" << std::endl;
}


bool EvilPlant::Update()
{ //★UPdate는 유한상태기계(FSM)로 상태 업데이트만 하는 함수로 구현. 다음 구현은 세부 낮 밤 등 매턴 변하는 것들 다른 함수에서 처리해야 할 것.
	//clock으로 밤(0~10000) 낮(10001~20000) 조절
	int iClock = clock() % DAYTIME;
	
	SetTextColor(FOREGROUND_INTENSITY);
	if (iClock > NIGHTTIME)
	{//낮
		if (m_nightCheck)
		{
			m_nightCheck = false;
			std::cout << " ---------------------  낮  ---------------------" << std::endl;
		}
	}
	else
	{
		if (m_nightCheck == false)
		{
			m_nightCheck = true;
			std::cout << " ---------------------  밤  ---------------------" << std::endl;
		}
	}


	//m_SavedMagi--;
	//휴식기가 아닐 경우 마기1씩 소모 
	if (!RestCheck())
	{
		if (m_SavedMagi > 0)
			m_SavedMagi--;
		else
		{ // 마기가 다 떨어지면 대신 피 사용
			if (m_SavedBlood > 0)
				m_SavedBlood--;
		}

		if ((m_SavedMagi == 0) && (m_SavedBlood == 0)) //피도 마력도 0 == 죽음
			m_LiveCheck = false;
	}

	//식물이 죽음을 맞이한 경우 false 리턴하여 Update 종료
	if (m_LiveCheck == false)
	{
		std::cout << GetNameOfEntity(ID()) << " : 영양부족으로 시름시름 앓다가 말라비틀어져 죽어버렸다." << std::endl << std::endl;
		return false;
	}

	//밤에는 마기 3씩 충전
	if (m_nightCheck)
	{
		//★ 둘 중 더 작은 수를 반환하는 min 사용하기....!
		m_SavedMagi = min(m_SavedMagi + 3, MAX_MAGI);
	}

	if (m_CurrState)
	{
		SetTextColor(FOREGROUND_BLUE | FOREGROUND_INTENSITY);
		std::cout << GetNameOfEntity(ID()) << " : [마기 : " + std::to_string(m_SavedMagi) + "  피 : " + std::to_string(m_SavedBlood) + "]" << std::endl;
		SetTextColor(FOREGROUND_INTENSITY);

		m_CurrState->Excute(this); 
	}

	return true;
}

void EvilPlant::ChangeState(State* state)
{
	//지금까지 사용했던 상태(목마름, 만족, 피로도)의 사용을 그만둔다.
	m_CurrState->Exit(this);
	//새로 이용할 상태 적용.
	m_CurrState = state;
	//새로 이용할 상태에 접근한다. (실행하면서 초기화해야 하는 것도 함께 할 것.)
	m_CurrState->Enter(this);
}

//피
void EvilPlant::DrawBlood()
{
	m_AnimalBlood_Count--;
	m_SavedBlood += BLOODDRAW;

	if (m_SavedBlood > MAX_BLOOD)
		m_SavedBlood = MAX_BLOOD;
	else if (m_SavedBlood < 0)
		m_SavedBlood = 0;
}
bool EvilPlant::LackBlood() const
{
	if (DETECTING_BLOOD >= m_SavedBlood)
		return true;

	return false;
}
bool EvilPlant::EmptyBlood() const
{
	if (0 >= m_SavedBlood)
		return true;

	return false;
}

//마기
bool EvilPlant::EmptyMagiCheck() const
{
	if (m_SavedMagi == 0)
		return true;

	return false;
}
bool EvilPlant::LackMagi() const
{
	if (MAGI_OFPRODUCING_FRUIT > m_SavedMagi)
		return true;

	return false;
}

//열매
void EvilPlant::ProuduceFruit()
{
	m_SavedBlood -= BLOOD_OFPRODUCING_FRUIT;
	m_SavedMagi -= MAGI_OFPRODUCING_FRUIT;

	m_Fruit++;
}
bool EvilPlant::ProuduceFruitCheck()
{
	//int necessaryMagi = MAGI_OFPRODUCING_FRUIT;

	//if (!m_nightCheck) //낮일때는 Update 거치면서 마기 -1 되기고 열매 생성 실행 때문
	//	necessaryMagi++;

	if ((m_Fruit != MAX_FRUIT) &&
		((m_SavedBlood >= BLOOD_OFPRODUCING_FRUIT) &&
		(m_SavedMagi >= MAGI_OFPRODUCING_FRUIT)))
	{
		m_ProuduceFruitCheck = true;
	}
	else
		m_ProuduceFruitCheck = false;

	return m_ProuduceFruitCheck;
}
bool EvilPlant::MaxFruit() const
{
	if (m_Fruit >= MAX_FRUIT)
		return true;

	return false;
}

//공격 가능
void EvilPlant::Set_AttackPossibleCheck(const bool& value)
{
	m_AttackPossibleCheck = value;
}

//잡은 먹이 + 뽑을 피
void EvilPlant::CaptiveAnimal()
{
	m_CaptiveAnimalCheck = true;
	m_AnimalBlood_Count = BLOODDRAW_COUNT;
}
bool EvilPlant::DrawBloodCheck() 
{ 
	if (m_AnimalBlood_Count > 0)
		return true; 
	else
	{
		m_CaptiveAnimalCheck = false;
		return false;
	}
}
