#include "EvilPlant.h"
#include "EvilPlantOwnedStates.h"
#include "EntityNames.h"
#include "ConsoleUtils.h"
#include <cassert>

//�ǰ� �� ���� ���̸� ��´�. �����ϴ� ���� ���Ÿ� �δµ� ����� �� �ִ� ��ġ�̹Ƿ�.
//��ġ�� �ѱ�� �ھ������ ���ȴٴ� ����.

bool m_nightCheck = true; //TODO::static ������ �ܺο�

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
	std::cout << " ---------------------  ��  ---------------------" << std::endl;
}


bool EvilPlant::Update()
{ //��UPdate�� ���ѻ��±��(FSM)�� ���� ������Ʈ�� �ϴ� �Լ��� ����. ���� ������ ���� �� �� �� ���� ���ϴ� �͵� �ٸ� �Լ����� ó���ؾ� �� ��.
	//clock���� ��(0~10000) ��(10001~20000) ����
	int iClock = clock() % DAYTIME;
	
	SetTextColor(FOREGROUND_INTENSITY);
	if (iClock > NIGHTTIME)
	{//��
		if (m_nightCheck)
		{
			m_nightCheck = false;
			std::cout << " ---------------------  ��  ---------------------" << std::endl;
		}
	}
	else
	{
		if (m_nightCheck == false)
		{
			m_nightCheck = true;
			std::cout << " ---------------------  ��  ---------------------" << std::endl;
		}
	}


	//m_SavedMagi--;
	//�޽ıⰡ �ƴ� ��� ����1�� �Ҹ� 
	if (!RestCheck())
	{
		if (m_SavedMagi > 0)
			m_SavedMagi--;
		else
		{ // ���Ⱑ �� �������� ��� �� ���
			if (m_SavedBlood > 0)
				m_SavedBlood--;
		}

		if ((m_SavedMagi == 0) && (m_SavedBlood == 0)) //�ǵ� ���µ� 0 == ����
			m_LiveCheck = false;
	}

	//�Ĺ��� ������ ������ ��� false �����Ͽ� Update ����
	if (m_LiveCheck == false)
	{
		std::cout << GetNameOfEntity(ID()) << " : ����������� �ø��ø� �δٰ� �����Ʋ���� �׾���ȴ�." << std::endl << std::endl;
		return false;
	}

	//�㿡�� ���� 3�� ����
	if (m_nightCheck)
	{
		//�� �� �� �� ���� ���� ��ȯ�ϴ� min ����ϱ�....!
		m_SavedMagi = min(m_SavedMagi + 3, MAX_MAGI);
	}

	if (m_CurrState)
	{
		SetTextColor(FOREGROUND_BLUE | FOREGROUND_INTENSITY);
		std::cout << GetNameOfEntity(ID()) << " : [���� : " + std::to_string(m_SavedMagi) + "  �� : " + std::to_string(m_SavedBlood) + "]" << std::endl;
		SetTextColor(FOREGROUND_INTENSITY);

		m_CurrState->Excute(this); 
	}

	return true;
}

void EvilPlant::ChangeState(State* state)
{
	//���ݱ��� ����ߴ� ����(�񸶸�, ����, �Ƿε�)�� ����� �׸��д�.
	m_CurrState->Exit(this);
	//���� �̿��� ���� ����.
	m_CurrState = state;
	//���� �̿��� ���¿� �����Ѵ�. (�����ϸ鼭 �ʱ�ȭ�ؾ� �ϴ� �͵� �Բ� �� ��.)
	m_CurrState->Enter(this);
}

//��
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

//����
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

//����
void EvilPlant::ProuduceFruit()
{
	m_SavedBlood -= BLOOD_OFPRODUCING_FRUIT;
	m_SavedMagi -= MAGI_OFPRODUCING_FRUIT;

	m_Fruit++;
}
bool EvilPlant::ProuduceFruitCheck()
{
	//int necessaryMagi = MAGI_OFPRODUCING_FRUIT;

	//if (!m_nightCheck) //���϶��� Update ��ġ�鼭 ���� -1 �Ǳ�� ���� ���� ���� ����
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

//���� ����
void EvilPlant::Set_AttackPossibleCheck(const bool& value)
{
	m_AttackPossibleCheck = value;
}

//���� ���� + ���� ��
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
