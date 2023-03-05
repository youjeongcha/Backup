#include "Computer.h"

Computer::Computer()
{
	m_sProductName = "Atents";
	m_sCurrentStatus = "ON";
	m_sGraphicCard = "GTX990";
	m_iCPU = 17;
	m_sMemory = "8G";
}


int Computer::Menu()
{
	int select;

	cout << "===== ȯ �� �� �� �� =====\n";
	cout << "1.��ǻ�� ����\n";
	cout << "2.���\n";
	cout << "3.off\n";
	cout << "�Է� >>>> ";
	cin >> select;

	return select;
}

void Computer::ComStatus()
{
	system("cls");
	cout << "�� ǰ �� : " << m_sProductName << "\n";
	cout << "���� ���� : " << m_sCurrentStatus << "\n";
	cout << "�׷���ī�� : " << m_sGraphicCard << "\n";
	cout << "C P U : " << m_iCPU << "\n";
	cout << "�޸� : " << m_sMemory << "\n";
}

void Computer::Function()
{
	int select;

	while (true)
	{
		system("cls");
		cout << "1.�� �� ��\n";
		cout << "2.�� �� ��\n";
		cout << "3.�� �� ��\n";
		cout << "4.���ư���\n";
		cout << "���� >>>> ";
		cin >> select;

		switch (select)
		{
		case 1:
			system("calc");
			break;
		case 2:
			system("notepad");
			break;
		case 3:
			system("mspaint");
			break;
		case 4:
			return;
		}
	}
}

void Computer::Off(int oldClock)
{
	int count = 0;

	while (count < MAX_COUNT)
	{
		if (clock() - oldClock >= SEC)
		{
			cout << "off " << MAX_COUNT - count << " ��\n";
			count++;
			oldClock = clock();
		}
	}
}

void Computer::Main()
{
	int oldClock = clock();

	while (true)
	{
		switch (Menu())
		{
		case 1:
			ComStatus();
			break;
		case 2:
			Function();
			break;
		case 3:
			Off(oldClock);
			return;
		}
		system("pause");
		system("cls");
	}
}