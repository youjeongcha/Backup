#include <iostream>
//#include <Windows.h> //Rectangle�Լ� �־ ������
using namespace std;

class Rectangle
{
private:
	int width, hight;
public:
	void GetLength();
	bool RangeCheck();
	void DrawPart(string part1, string part2, string part3);
	void Draw();
};

void Rectangle::GetLength()
{
	do
	{
		cout << "���� �Է� : ";
		cin >> width;
		cout << "���� �Է� : ";
		cin >> hight;
	} while (RangeCheck());
}

bool Rectangle::RangeCheck()
{
	bool check = false;

	if (width <= 0 || hight <= 0)
	{
		check = true;
		cout << "���� �Ǵ� ���ΰ� 1���� �۽��ϴ�.\n";
		system("pause");
		system("cls");
	}

	return check;
}

void Rectangle::DrawPart(string part1, string part2, string part3)
{
	cout << part1;
	for (int i = 0; i < width - 2; i++)
		cout << part2;
	cout << part3;
	cout << endl;
}

void Rectangle::Draw()
{
	DrawPart("��", "��", "��");

	for (int i = 0; i < hight - 2; i++)
		DrawPart("��", "  ", "��");

	DrawPart("��", "��", "��");
}

void main()
{
	Rectangle Rectangle;

	Rectangle.GetLength();
	Rectangle.Draw();
}