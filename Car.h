#pragma once
#include "Mecro.h"
#include "Timer.h"

#define MAX_DESTANCE 80

enum POSITION //enum���� ó��
{
	POSITION_DEFAULT_X = 10,
	POSITION_DEFAULT_Y = 10
};

enum CARPART
{//�׸� �׸��� y�� �̵�
	CARPART_HEAD,
	CARPART_BODY,
	CARPART_WHEEL
};

typedef struct CarShape //class�� typedef�� ����ȣȯ
{//���� ���ε��� ��Ƽ�
	std::string Head;
	std::string Body;
	std::string Wheel;
}CarShape;

class Car
{
private:
	int m_ix;
	int m_iy;

	bool m_bCreateFlag; //
	bool m_bFinishFlag;
	bool m_bFastModeFlag;

	Timer Timer;
	CarShape Car_Character;
	
public:
	Car();
	void Set_ModeChange();
	void MovePosition();
	void Move_Car();
	bool EraseCheck_Car();
	void Draw_Car(CarShape Car_Character, int x, int y);
	void Erase_Car(CarShape Car_Character, int x, int y);

	inline bool Get_m_iFinish()
	{
		return m_bFinishFlag;
	}

	inline void gotoxy(int x, int y)
	{
		COORD Pos = { x, y };
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
	}
	~Car();
};
