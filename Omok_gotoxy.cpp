#include<iostream>
#include<Windows.h>
using namespace std;
//걍 가져다 쓰기만하면 되는 코드

/*내가 원하는 콘솔창의 좌표로 커서를 이동시켜준다.
화면 깜빡인 해결
내가 원하는 것만 왔다갔다 하면서 지움*/

void gotoxy(int x, int y)
{
	COORD Pos = { x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

void main()
{
	gotoxy(10, 10);
	cout << "Hello~!";
}