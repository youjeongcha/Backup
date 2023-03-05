#include "MultiplicationTable.h"

void MultiplicationTable::SetStart()
{
	cin >> start;
}

void MultiplicationTable::SetEnd()
{
	cin >> end;
}

bool MultiplicationTable::StartRangeCheck()
{
	if (start < GUGUDAN_START || start > GUGUDAN_END)
		return false;
}

bool MultiplicationTable::EndRangeCheck()
{
	if (end < GUGUDAN_START || end > GUGUDAN_END)
		return false;
	if (end < start)
		return false;
}

void MultiplicationTable::PrintDan(int start, int end)
{
	for (int dan = start; dan <= end; dan++)
	{
		cout << "=======" << dan << "��=======\n";
		for (int i = 1; i <= 9; i++)
		{
			cout << "   " << dan << "x" << i << "=" << dan * i << "\n";
		}
		cout << "\n";
	}
}

void MultiplicationTable::Print()
{
	char select;
	bool startCheck;
	bool endCheck;

	cout << "\n���۴ܰ� ������ �Է��Ͻðڽ��ϱ�?(y/n) : ";
	cin >> select;

	if (select == 'y')
	{
		cout << "���� �� �Է� : ";
		SetStart();
		cout << "�� �� �Է� : ";
		SetEnd();

		startCheck = StartRangeCheck();
		endCheck = EndRangeCheck();

		if ((startCheck == false) && (endCheck == false))
			PrintDan();
		else if (startCheck == false)
			PrintDan(2);
		else if (endCheck == false)
			PrintDan(start, 9);
		else
			PrintDan(start, end);
	}
	else
	{
		PrintDan();
	}
}