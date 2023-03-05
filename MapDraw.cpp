#include "MapDraw.h"
//static ������ ������ .cpp���� �ؾ� �Ѵ�.


void MapDraw::ErasePoint(int x, int y)
{
	gotoxy(x * 2, y);
	cout << "  "; //"  "
	//gotoxy(-1, -1);
	return;
}
void MapDraw::DrawPoint(string str, int x, int y)
{
	gotoxy(x * 2, y);
	cout << str;
	//gotoxy(-1, -1);
	return;
}
void MapDraw::DrawMidText(string str, int x, int y)
{//����
	if (x > str.size() / 2)
		x -= str.size() / 2;
	gotoxy(x, y);
	cout << str;
	return;
}
void MapDraw::TextDraw(string str, int x, int y)
{
	gotoxy(x, y);
	cout << str;
}

//void MapDraw::Print(string _string)
//{
//	//int Start_x = MAP_END_X;
//	int Start_y = MAP_END_Y / GAP_3 * GAP_2;
//
//	BoxErase(MAP_END_X, Start_y);
//	MapDraw::DrawMidText(_string, MAP_END_X, MENUPRINT_START_Y + GAP_2);
//	//getch();
//
//	switch (getch())
//	{
//	case OPTION_INFO_i:	//ĳ���Ϳ� ���� ����,���� Ȯ��
//	case OPTION_INFO_I:
//		cout << "���⼭ ���� Ȯ��";
//		break;
//	case OPTION_SAVE_s:	//����
//	case OPTION_SAVE_S:
//		break;
//	default:
//		break;
//	}
//}

//void MapDraw::UnderInfo()
//{
//	cout << "====== ??? ======";
//	cout << "���ݷ� = " + to_string(Get_Attack());
//	cout << "����� = ";
//	cout << "����ġ = ";
//
//}


void MapDraw::BoxErase(int Width, int Height)
{//�ڽ� ���ʸ� ����� �ڵ�
	for (int y = 1; y < Height - 1; y++)
	{
		gotoxy(2, y); //2 �ڽ� ��
		for (int x = 1; x < Width - 1; x++)
			cout << "  ";
	}
}

void MapDraw::BoxDraw(int Start_x, int Start_y, int Width, int Height)
{//�ڽ��� ���� ��ĭ �׸�
	if (Start_x > Width)
		Start_x -= Width; //�Է°��� �ڽ� ������ ����� ���� ������ �־��ִ� �� //����� �����ִ���????
	BLUE
	for (int y = 0; y < Height; y++)
	{
		gotoxy(Start_x, Start_y + y);
		if (y == 0)
		{
			cout << "��";
			for (int x = 1; x < Width - 1; x++)
				cout << "��";
			cout << "��";
		}
		else if (y == Height - 1)
		{
			cout << "��";
			for (int x = 1; x < Width - 1; x++)
				cout << "��";
			cout << "��";
		}
		else
		{
			cout << "��";
			for (int x = 1; x < Width - 1; x++)
				cout << "  ";
			cout << "��";
		}
	}
	ORIGINAL
	return;
}

void MapDraw::BoxSectorDraw(int Start_x, int Start_y, int Width, int Height)
{
	int _x = Start_x / GAP_3 * GAP_4;
	int _y = Start_y / GAP_3 * GAP_2;

	BLUE
		//���μ�
		gotoxy(GAP_2, _y);
		for (int x = 0; x < Width - GAP_2; x++)
			cout << "��";
		//���μ�
		for (int y = _y + GAP_1; y < Height - GAP_1; y++)
		{
			gotoxy(_x, y);
			cout << "��";
		}
	ORIGINAL
}

int MapDraw::MenuSelectCursor(int MenuLen, int AddCol, int x, int y)
{//MenuLen �̵� ������ �޴� ũ��, AddCol �� ĭ �Ѿ� �̵�, x,y���� ����
	int Select = 1;

	YELLOW
		DrawPoint("��", x, y);
	ORIGINAL //���� �ٲٰ� ����� ���� �ٽ� �����ִ� �� ����
		while (1)
		{
			switch (getch()) //getch() - ���� �Է��� ������ ���. ���� ������ ���ۿ� �����ߴٰ� ���ۿ��� ������ ����
			{
			case DIRECTION_UP:
			case DIRECTION_BIG_UP:
				if (Select - 1 >= 1)
				{
					ErasePoint(x, y);
					y -= AddCol;
					Select--;
				}
				break;
			case DIRECTION_DOWN:
			case DIRECTION_BIG_DOWN:
				if (Select + 1 <= MenuLen)
				{
					ErasePoint(x, y);
					y += AddCol;
					Select++;
				}
				break;
			case ENTER:
				system("cls");
				return Select;
			}
			RED
				DrawPoint("��", x, y);
			ORIGINAL
		}
}

int MapDraw::MenuSelectCursor_XY(int MenuLenX, int MenuLenY, int AddColX, int AddColY, int x, int y)
{//MenuLen �̵� ������ �޴� ũ��, AddCol �� ĭ �Ѿ� �̵�, x,y���� ����
	int Select = 1;
	int tmpX, tmpY;
	//1,2
	//3,4
	YELLOW
		DrawPoint("��", x, y);
	ORIGINAL //���� �ٲٰ� ����� ���� �ٽ� �����ִ� �� ����
		while (1)
		{
			tmpX = x;
			tmpY = y;

			switch (getch()) //getch() - ���� �Է��� ������ ���. ���� ������ ���ۿ� �����ߴٰ� ���ۿ��� ������ ����
			{
			case DIRECTION_UP:
			case DIRECTION_BIG_UP:
				if ((Select == 3) || (Select == 4))
				{
					ErasePoint(x , y);
					y -= AddColY;
					Select-=2;
				}
				break;
			case DIRECTION_DOWN:
			case DIRECTION_BIG_DOWN:
				if ((Select == 1) || (Select == 2))
				{
					ErasePoint(x , y);
					y += AddColY;
					Select+=2;
				}
				break;
			case DIRECTION_LEFT:
			case DIRECTION_BIG_LEFT:
				//TODO : ���� �̵� - ������ 
				if ((Select == 2) || (Select == 4))
				{
					ErasePoint(x , y);
					x -= AddColX;
					Select--;
				}
				break;
			case DIRECTION_RIGHT:
			case DIRECTION_BIG_RIGHT:
				//TODO : ������ �̵�
				if ((Select == 1) || (Select == 3))
				{
					ErasePoint(x , y);
					x += AddColX;
					Select++;
				}
				break;
			case ENTER:
				ErasePoint(tmpX, tmpY); //
				return Select;
			}
			//�ٸ� �Է°�
			RED
				DrawPoint("��", x, y);
			ORIGINAL
		}
}

