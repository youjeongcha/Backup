#include"CharDraw.h"

void CharDraw::StartCharDraw(int Start_x, int Start_y, int Width, int Height)
{
	m_position.m_ix = Start_x + Width - 1;
	m_position.m_iy = Start_y + (Height / 2) - 1;

	gotoxy(m_position.m_ix, m_position.m_iy);// �ʺ�/2�� ���� �ʴ� ���� > Ư�����ڴ� ���� ��ĭ ����
	cout << "��";
}

bool CharDraw::MoveObstacleCheck(int Start_x, int Start_y, int Width, int Height, char ch)
{
	switch (ch)
	{
	case LEFT:
		if (m_position.m_ix < Start_x + 3)//Start_x�� 3�̸� 45�� �׷��� ĳ���ʹ� 6����
			return true;
		break;
	case RIGHT:
		if (m_position.m_ix > Start_x + Width * 2 - 5)//27�ε�  //Start_x + ���α���*2 -5(�� �׸����� �� ��� -2, ĳ���� �׷����� �� ��� -2, Ŀ���� �� ĭ �տ� ���� -1)
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
	if (ch == -32)//����Ű �Է� ������ ����� �޾Ƶ� ������ -32�� ���� ���´�.
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
			cout << "��";
		}
		break;
	case RIGHT:
		if (MoveObstacleCheck(Start_x, Start_y, Width, Height, ch) == false)
		{
			ErasePoint(m_position.m_ix, m_position.m_iy);
			m_position.m_ix++;
			gotoxy(m_position.m_ix, m_position.m_iy);
			cout << "��";
		}
		break;
	case UP:
		if (MoveObstacleCheck(Start_x, Start_y, Width, Height, ch) == false)
		{
			ErasePoint(m_position.m_ix, m_position.m_iy);
			m_position.m_iy--;
			gotoxy(m_position.m_ix, m_position.m_iy);
			cout << "��";
		}
		break;
	case DOWN:
		if (MoveObstacleCheck(Start_x, Start_y, Width, Height, ch) == false)
		{
			ErasePoint(m_position.m_ix, m_position.m_iy);
			m_position.m_iy++;
			gotoxy(m_position.m_ix, m_position.m_iy);
			cout << "��";
		}
		break;
	}
}

inline void CharDraw::gotoxy(int x, int y) //inline �ش��Լ� ȣ��κ� ����. ȣ�� ���� �̸� data ������ �޸𸮸� �÷��д�. ���� ȣ�� ����
{
	COORD Pos = { x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}