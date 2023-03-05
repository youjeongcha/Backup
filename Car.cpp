#include "Car.h"


Car::Car()
{
	Timer.SetTimer(TIMER_TYPE_LOOP, TIME_NORMALMODE_MOVE, std::bind(&Car::MovePosition, this));
	m_bFinishFlag = false;
	m_ix = POSITION_DEFAULT_X;
	m_iy = POSITION_DEFAULT_Y;
	m_bCreateFlag = false;
	m_bFastModeFlag = false;
	Car_Character.Head =  "  ����������  \n";
	Car_Character.Body =  "���� �Ƣ� ����\n";
	Car_Character.Wheel = "���ۦ������ۦ�\n";
}
void Car::Set_ModeChange()
{
	m_bFastModeFlag = !(m_bFastModeFlag); //m_bFastModeFlag �ʱ갪�� false�̰� ���������ִ� ����

	if(m_bFastModeFlag)
		Timer.SetTimer(TIMER_TYPE_LOOP, TIME_FASTMODE_MOVE, std::bind(&Car::MovePosition, this)); //fast
	else
		Timer.SetTimer(TIMER_TYPE_LOOP, TIME_NORMALMODE_MOVE, std::bind(&Car::MovePosition, this)); //normal
}

void Car::Draw_Car(CarShape Car_Character, int x, int y)
{
	gotoxy(x, y + CARPART_HEAD);
	std::cout << Car_Character.Head;
	gotoxy(x, y + CARPART_BODY);
	std::cout << Car_Character.Body;
	gotoxy(x, y + CARPART_WHEEL);
	std::cout << Car_Character.Wheel;
}
void Car::Erase_Car(CarShape Car_Character, int x, int y)
{//�ߺ��α� ' '�� �׸� �ϳ��ϳ� �� ���� ����
	for (int Count = 0; Count < Car_Character.Head.length(); Count++)
	{
		gotoxy(x + Count, y + CARPART_HEAD);
		std::cout << " ";
	}
	for (int Count = 0; Count < Car_Character.Body.length(); Count++)
	{
		gotoxy(x + Count, y + CARPART_BODY);
		std::cout << " ";
	}
	for (int Count = 0; Count < Car_Character.Wheel.length(); Count++)
	{
		gotoxy(x + Count, y + CARPART_WHEEL);
		std::cout << " ";
	}
}

void Car::Move_Car()
{//�ð�üũ�� ��
	Timer.CheckTimer();
}


void Car::MovePosition()
{//�׸����� �� �̵� ǥ��
	Erase_Car(Car_Character, m_ix, m_iy);
	++m_ix;
	Draw_Car(Car_Character, m_ix, m_iy); 
}


bool Car::EraseCheck_Car()
{
	if (m_ix <= MAX_DESTANCE) //x�� ���̵� �ִ� �Ÿ����� ������ �ߴ�
		return false;
	Erase_Car(Car_Character, m_ix, m_iy);
	return true;
}

Car::~Car()
{
}