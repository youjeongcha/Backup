#include<iostream>
#include<Windows.h>
using namespace std;
//�� ������ ���⸸�ϸ� �Ǵ� �ڵ�

/*���� ���ϴ� �ܼ�â�� ��ǥ�� Ŀ���� �̵������ش�.
ȭ�� ������ �ذ�
���� ���ϴ� �͸� �Դٰ��� �ϸ鼭 ����*/

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