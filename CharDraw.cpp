#include"CharDraw.h"

void CharDraw::StartCharDraw(int Start_x, int Start_y, int Width, int Height)
{
	m_position.m_ix = Start_x + Width - 1;
	m_position.m_iy = Start_y + (Height / 2) - 1;

	gotoxy(m_position.m_ix, m_position.m_iy);// 너비/2를 하지 않는 이유 > 특수문자는 가로 두칸 차지
	cout << "♤";
}

bool CharDraw::MoveObstacleCheck(int Start_x, int Start_y, int Width, int Height, char ch)
{
	switch (ch)
	{
	case LEFT:
		if (m_position.m_ix < Start_x + 3)//Start_x가 3이면 45에 그려짐 캐릭터는 6까지
			return true;
		break;
	case RIGHT:
		if (m_position.m_ix > Start_x + Width * 2 - 5)//27인데  //Start_x + 가로길이*2 -5(벽 그리지는 거 고려 -2, 캐릭터 그려지는 거 고려 -2, 커서는 한 칸 앞에 존재 -1)
			return true;
		break;
	case UP:
		if (m_position.m_iy < Start_y + 2)
			return true;
		break;
	case DOWN:
		if (m_position.m_iy > Start_y + Height - 3)
			return true;
		break;
	}
	return false;
}

void CharDraw::ErasePoint(int x, int y)
{
	//gotoxy(x * 2, y);
	gotoxy(x, y);
	cout << "  ";
	return;
}

void CharDraw::MoveCharDraw(int Start_x, int Start_y, int Width, int Height)
{
	char ch;
	ch = getch();
	if (ch == -32)//방향키 입력 받으면 어던걸 받아도 무조건 -32가 먼저 들어온다.
	{
		ch = getch();
	}

	switch (ch)
	{
	case LEFT:
		if (MoveObstacleCheck(Start_x, Start_y, Width, Height, ch) == false)
		{
			ErasePoint(m_position.m_ix, m_position.m_iy);
			m_position.m_ix--;
			gotoxy(m_position.m_ix, m_position.m_iy);
			cout << "♤";
		}
		break;
	case RIGHT:
		if (MoveObstacleCheck(Start_x, Start_y, Width, Height, ch) == false)
		{
			ErasePoint(m_position.m_ix, m_position.m_iy);
			m_position.m_ix++;
			gotoxy(m_position.m_ix, m_position.m_iy);
			cout << "♤";
		}
		break;
	case UP:
		if (MoveObstacleCheck(Start_x, Start_y, Width, Height, ch) == false)
		{
			ErasePoint(m_position.m_ix, m_position.m_iy);
			m_position.m_iy--;
			gotoxy(m_position.m_ix, m_position.m_iy);
			cout << "♤";
		}
		break;
	case DOWN:
		if (MoveObstacleCheck(Start_x, Start_y, Width, Height, ch) == false)
		{
			ErasePoint(m_position.m_ix, m_position.m_iy);
			m_position.m_iy++;
			gotoxy(m_position.m_ix, m_position.m_iy);
			cout << "♤";
		}
		break;
	}
}

inline void CharDraw::gotoxy(int x, int y) //inline 해당함수 호출부분 생략. 호출 전에 미리 data 영역에 메모리를 올려둔다. 빠른 호출 가능
{
	COORD Pos = { x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}