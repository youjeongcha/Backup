#include<iostream>
#include<Windows.h>
using namespace std;

enum GUGUDAN
{
	GUGUDAN_START = 2,
	GUGUDAN_TWO = 2,
	GUGUDAN_THREE,
	GUGUDAN_FOUR,
	GUGUDAN_FIVE,
	GUGUDAN_SIX,
	GUGUDAN_SEVEN,
	GUGUDAN_EIGHT,
	GUGUDAN_NINE,
	GUGUDAN_END = GUGUDAN_NINE
};

class Dan
{
private:
	int start, end;
public:
	void SetDan();
	bool RangeCheck();
	void Print();
	void PrintDan(int dan);
};

void Dan::SetDan()
{
	do
	{
		system("cls");
		cout << "���� �� �Է� : ";
		cin >> start;

		cout << "�� �� �Է� : ";
		cin >> end;

	} while (RangeCheck());
}

bool Dan::RangeCheck()
{
	bool check = false;

	if (start < GUGUDAN_START || start > GUGUDAN_END)
	{
		cout << "����";
		check = true;
	}
	else if (end < GUGUDAN_START || end > GUGUDAN_END)
	{
		cout << "��";
		check = true;
	}
	if (check == true)
	{
		cout << " ���� 2���� �۰ų� 9���� Ů�ϴ�.\n";
		system("pause");
	}

	return check;
}

void Dan::Print()
{
	for (int dan = start; dan <= end; dan++)
	{
		PrintDan(dan);
	}
}

void Dan::PrintDan(int dan)
{
	cout << "=======" << dan << "��=======\n";
	for (int i = 1; i <= 9; i++)
	{
		cout << "   " << dan << "x" << i << "=" << dan * i << "\n";
	}
	cout << "\n";
}

//---

void main()
{
	Dan GuguDan;

	GuguDan.SetDan();
	GuguDan.Print();
}