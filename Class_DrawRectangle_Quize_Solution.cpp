#include<iostream>
using namespace std;

class Quadrangle
{
private:
	int Width;
	int Height;
public:
	void SetQuadrangle();
	void ShowQuadrangle();
};
void Quadrangle::SetQuadrangle()
{
	while (1)
	{
		cout << "가로 입력 : ";
		cin >> Width;
		cout << "세로 단 입력 : ";
		cin >> Height;
		if (Width <= 1 || Height <= 1) //
			cout << "가로 또는 세로가 1이하입니다." << endl;
		else //
			break;
		system("pause");
	}
}
void Quadrangle::ShowQuadrangle()
{//좌표
	for (int y = 0; y < Height; y++)
	{//한 줄씩 완성
		for (int x = 0; x < Width; x++)
		{
			if (y == 0 && x == 0)
				cout << "┌";
			else if (y == 0 && x == Width - 1)
				cout << "┐";
			else if (y == Height - 1 && x == 0)
				cout << "└";
			else if (y == Height - 1 && x == Width - 1)
				cout << "┘";
			else if (y == 0 || y == Height - 1)
				cout << "─";
			else if (x == 0 || x == Width - 1)
				cout << "│";
			else
				cout << "  ";
		}
		cout << endl;
	}
}
void main()
{
	Quadrangle Quad1;
	Quad1.SetQuadrangle();
	Quad1.ShowQuadrangle();
}