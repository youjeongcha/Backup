#include "MapDraw.h"
//static 변수는 선언을 .cpp에서 해야 한다.


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
{//주의
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
//	case OPTION_INFO_i:	//캐릭터와 몬스터 정보,도감 확인
//	case OPTION_INFO_I:
//		cout << "여기서 도감 확인";
//		break;
//	case OPTION_SAVE_s:	//저장
//	case OPTION_SAVE_S:
//		break;
//	default:
//		break;
//	}
//}

//void MapDraw::UnderInfo()
//{
//	cout << "====== ??? ======";
//	cout << "공격력 = " + to_string(Get_Attack());
//	cout << "생명력 = ";
//	cout << "경험치 = ";
//
//}


void MapDraw::BoxErase(int Width, int Height)
{//박스 안쪽만 지우는 코드
	for (int y = 1; y < Height - 1; y++)
	{
		gotoxy(2, y); //2 박스 안
		for (int x = 1; x < Width - 1; x++)
			cout << "  ";
	}
}

void MapDraw::BoxDraw(int Start_x, int Start_y, int Width, int Height)
{//박스와 안쪽 빈칸 그림
	if (Start_x > Width)
		Start_x -= Width; //입력값이 박스 범위를 벗어나면 범위 안으로 넣어주는 거 //사용할 일이있는지????
	BLUE
	for (int y = 0; y < Height; y++)
	{
		gotoxy(Start_x, Start_y + y);
		if (y == 0)
		{
			cout << "┌";
			for (int x = 1; x < Width - 1; x++)
				cout << "─";
			cout << "┐";
		}
		else if (y == Height - 1)
		{
			cout << "└";
			for (int x = 1; x < Width - 1; x++)
				cout << "─";
			cout << "┘";
		}
		else
		{
			cout << "│";
			for (int x = 1; x < Width - 1; x++)
				cout << "  ";
			cout << "│";
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
		//가로선
		gotoxy(GAP_2, _y);
		for (int x = 0; x < Width - GAP_2; x++)
			cout << "─";
		//세로선
		for (int y = _y + GAP_1; y < Height - GAP_1; y++)
		{
			gotoxy(_x, y);
			cout << "│";
		}
	ORIGINAL
}

int MapDraw::MenuSelectCursor(int MenuLen, int AddCol, int x, int y)
{//MenuLen 이동 가능한 메뉴 크기, AddCol 한 칸 넘어 이동, x,y에서 시작
	int Select = 1;

	YELLOW
		DrawPoint("▷", x, y);
	ORIGINAL //색상 바꾸고 출력한 다음 다시 돌려주는 게 관례
		while (1)
		{
			switch (getch()) //getch() - 값을 입력할 때까지 대기. 값이 들어오면 버퍼에 저장했다가 버퍼에서 꺼내서 리턴
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
				DrawPoint("▷", x, y);
			ORIGINAL
		}
}

int MapDraw::MenuSelectCursor_XY(int MenuLenX, int MenuLenY, int AddColX, int AddColY, int x, int y)
{//MenuLen 이동 가능한 메뉴 크기, AddCol 한 칸 넘어 이동, x,y에서 시작
	int Select = 1;
	int tmpX, tmpY;
	//1,2
	//3,4
	YELLOW
		DrawPoint("▷", x, y);
	ORIGINAL //색상 바꾸고 출력한 다음 다시 돌려주는 게 관례
		while (1)
		{
			tmpX = x;
			tmpY = y;

			switch (getch()) //getch() - 값을 입력할 때까지 대기. 값이 들어오면 버퍼에 저장했다가 버퍼에서 꺼내서 리턴
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
				//TODO : 왼쪽 이동 - 왼쪽이 
				if ((Select == 2) || (Select == 4))
				{
					ErasePoint(x , y);
					x -= AddColX;
					Select--;
				}
				break;
			case DIRECTION_RIGHT:
			case DIRECTION_BIG_RIGHT:
				//TODO : 오른쪽 이동
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
			//다른 입력값
			RED
				DrawPoint("▷", x, y);
			ORIGINAL
		}
}

