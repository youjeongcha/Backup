#include "GameManager.h"

GameManager::GameManager()
{
	m_iGame = OMOK;
}

string GameManager::mapLog[MAPMAX][MAPMAX]; //static�� ���� .cpp���� �ؾ� �Ѵ�.


void GameManager::BoxSetting(string mapLog[][MAPMAX], int Start_x, int Start_y, int Width, int Height)
{
	for (int y = 0; y < Height; y++)
	{
		int x = 0;
		//DrawManager::gotoxy(Start_x, Start_y + y);
		if (y == 0)
		{
			mapLog[x][y] = "��";
			for (x = 1; x < Width - 1; x++)
				mapLog[x][y] = "��";
			mapLog[x][y] = "��";
		}
		else if (y == Height - 1)
		{
			mapLog[x][y] = "��";
			for (x = 1; x < Width - 1; x++)
				mapLog[x][y] = "��";
			mapLog[x][y] = "��";
		}
		else
		{
			mapLog[x][y] = "��";
			for (x = 1; x < Width - 1; x++)
				mapLog[x][y] = "��";
			mapLog[x][y] = "��";
		}
	}
	return;
}


//----------------------------------------------------------------


void GameManager::Menu()
{
	int m_iSelect;

	while (true)
	{
		Setting();
		DrawManager::BoxDraw(m_position.m_ix, m_position.m_iy, m_mapSize.m_iWidth, m_mapSize.m_iHeight);

		switch (m_iGame)
		{
		case OMOK:
			DrawManager::DrawMidText("�� �� �� ��", MAPMAX, 6);
			break;
		case OTHELLO:
			DrawManager::DrawMidText("�� �� �� �� ��", MAPMAX, 6);
			break;
		}
		DrawManager::DrawMidText("1.���� ����", MAPMAX, 8);
		DrawManager::DrawMidText("2.���� ����", MAPMAX, 10);
		DrawManager::DrawMidText("3.���� ����", MAPMAX, 12);
		DrawManager::DrawMidText("��������������������", MAPMAX, 14);
		DrawManager::DrawMidText("��                ��", MAPMAX, 15);
		DrawManager::DrawMidText("��������������������", MAPMAX, 16);
		DrawManager::gotoxy(MAPMAX, 15);
		cin >> m_iSelect;


		switch (m_iSelect)
		{
		case 1:
			Play();//���ڸ� �޾Ƽ� ������ ���� ������ ������ �����ϱ�Ρ�
			break;
		case 2:
			if (m_iGame == OMOK)
				m_iGame = OTHELLO;
			else
				m_iGame = OMOK;
			break;
		case 3:
			return;
		}
	}
}


//-------------------------------------------------------------------


void GameManager::Play()
{
	int CharaterTurn = BLACK;
	m_turn = 1;
	bool ESC_Check = true;

	DrawManager::BoxDraw(m_position.m_ix, m_position.m_iy, m_mapSize.m_iWidth, m_mapSize.m_iHeight);
	ShowInfo();

	//ĳ���� �����ְ�
	m_BlackPlayer.SetCharater("��", "��", "Black");
	m_WhitePlayer.SetCharater("��", "��", "White");

	if (m_iGame == OMOK)
	{
		//2ȸ�� �̻� �÷��� �� - ���� �ʱ�ȭ
		m_WhitePlayer.Reset_m_backXY();
		m_BlackPlayer.Reset_m_backXY();

		//2ȸ�� �̻� �÷��� �� - ������ ��û : �⺻ false�� ����
		//������ ���·� ����� bool�� ��� ture�� �����ִ�.
		m_BlackPlayer.SetBack(false);
		m_WhitePlayer.SetBack(false);
	}

	//2ȸ�� �̻� �÷��� �� - ESC �ʱ�ȭ
	m_WhitePlayer.SetESC(false);
	m_BlackPlayer.SetESC(false);

	while (true)
	{
		DrawManager::gotoxy(MAPMAX + 2, MAPMAX + 4);
		cout << m_turn;

		if (CharaterTurn == BLACK)
		{//�ڵ� �ߺ�
			CharaterTurn = WHITE;
			ESC_Check = PlayerTurn(&m_BlackPlayer, &m_WhitePlayer, BLACK); //�������� > ��������
		}
		else if (CharaterTurn == WHITE)
		{
			CharaterTurn = BLACK;
			ESC_Check = PlayerTurn(&m_WhitePlayer, &m_BlackPlayer, WHITE);
		}
		m_turn++;

		if (ESC_Check == true)
			return;
	}
}

bool GameManager::PlayerTurn(Player* m_NowTurn_Player, Player* m_NextTurn_Player, CHARATER player)
{
	m_NowTurn_Player->GetTurn(m_turn);//������ Ƚ�� üũ
	//m_NowTurn_Player->Turn(m_iGame);//���� ����
	
	switch ((DIRECTION)m_NowTurn_Player->Turn(m_iGame)) //���� ����
	{
	case BACK:
		//������ ��û Ȯ��
		if (m_iGame == OMOK &&
			(m_NowTurn_Player->GetBack() == true))
		{
			//black���� ������ ��û�� �޾� white���� ������ ���
			m_NextTurn_Player->SetBack(true);
			m_NowTurn_Player->SetBack(false);

			//m_turn�� 10�� ���� ��� �����ڸ��� �������� �ʾƼ�
			DrawManager::gotoxy(MAPMAX + 2, MAPMAX + 4);
			cout << "       ";
			m_turn -= 2;
		}
		return false;
	case ENTER:
		if (m_NowTurn_Player->GetEsc() == true)
		{
			DrawManager::gotoxy(MAPMAX - 4, MAPMAX / 2);
			if (player == BLACK)
				cout << "Black Win";
			else
				cout << "White Win";

			char ch = getch();
			DrawManager::ErasePoint(0, MAPMAX); //�ϴ� ����â ����

			return true;
		}
		return false;
	case ESC:
		DrawManager::ErasePoint(0, MAPMAX); //�ϴ� ����â ����
		return true;
	}

	////������ ��û Ȯ��
	//if (m_iGame == OMOK &&
	//	(m_NowTurn_Player->GetBack() == true))
	//{
	//	//black���� ������ ��û�� �޾� white���� ������ ���
	//	m_NextTurn_Player->SetBack(true);
	//	m_NowTurn_Player->SetBack(false);

	//	//m_turn�� 10�� ���� ��� �����ڸ��� �������� �ʾƼ�
	//	DrawManager::gotoxy(MAPMAX + 2, MAPMAX + 4);
	//	cout << "       ";
	//	m_turn -= 2;
	//}

	////ESC
	//if (m_NowTurn_Player->GetEsc() == true)
	//{//�ϴ� ����â ����
	//	DrawManager::ErasePoint(0, MAPMAX);
	//	return true;
	//}
}

void GameManager::ShowInfo()
{
	DrawManager::DrawMidText("====����Ű====", MAPMAX, MAPMAX);
	DrawManager::DrawMidText("�̵� : A,S,W,D  ������ : ENTER", MAPMAX, MAPMAX + 1);
	if (m_iGame == OMOK)
	{
		DrawManager::DrawMidText("������ : N  ���� : ESC", MAPMAX, MAPMAX + 2);
		DrawManager::DrawMidText("Player Name : ", 1, MAPMAX + 3);
		DrawManager::DrawMidText("������ : ", MAPMAX + 11, MAPMAX + 3);
		DrawManager::DrawMidText("Turn : ", MAPMAX - 2, MAPMAX + 4);
	}
	else
	{
		DrawManager::DrawMidText("���� : ESC", MAPMAX, MAPMAX + 2);
		DrawManager::DrawMidText("Player Name : ", MAPMAX - 2, MAPMAX + 3);
		DrawManager::DrawMidText("Turn : ", MAPMAX - 2, MAPMAX + 4);
	}
}


GameManager::~GameManager() { }
