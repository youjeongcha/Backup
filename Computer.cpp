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

	cout << "===== 환 영 합 니 다 =====\n";
	cout << "1.컴퓨터 상태\n";
	cout << "2.기능\n";
	cout << "3.off\n";
	cout << "입력 >>>> ";
	cin >> select;

	return select;
}

void Computer::ComStatus()
{
	system("cls");
	cout << "제 품 명 : " << m_sProductName << "\n";
	cout << "현재 상태 : " << m_sCurrentStatus << "\n";
	cout << "그래픽카드 : " << m_sGraphicCard << "\n";
	cout << "C P U : " << m_iCPU << "\n";
	cout << "메모리 : " << m_sMemory << "\n";
}

void Computer::Function()
{
	int select;

	while (true)
	{
		system("cls");
		cout << "1.계 산 기\n";
		cout << "2.메 모 장\n";
		cout << "3.그 림 판\n";
		cout << "4.돌아가기\n";
		cout << "선택 >>>> ";
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
			cout << "off " << MAX_COUNT - count << " 전\n";
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