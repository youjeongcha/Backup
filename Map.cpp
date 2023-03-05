#include "Map.h"


Map::Map() { }

string Map::mapLog[MAPMAX][MAPMAX]; //static�� ���� .cpp���� �ؾ� �Ѵ�.


void Map::Setting()
{
	m_position.m_ix = 0;
	m_position.m_iy = 0;
	m_mapSize.m_iWidth = MAPMAX;
	m_mapSize.m_iHeight = MAPMAX;
	m_Omok_BlackCharater.SetPosition(m_position, m_mapSize);
	m_Omok_WhiteCharater.SetPosition(m_position, m_mapSize);
	m_Othello_BlackCharater.SetPosition(m_position, m_mapSize);
	m_Othello_WhiteCharater.SetPosition(m_position, m_mapSize);
	BoxSetting(m_position.m_ix, m_position.m_iy, m_mapSize.m_iWidth, m_mapSize.m_iHeight);
}

void Map::BoxDraw(int Start_x, int Start_y, int Width, int Height)
{
	for (int y = 0; y < Height; y++)
	{
		Mecro::gotoxy(Start_x, Start_y + y);
		if (y == 0)
		{
			cout << "��";
			for (int x = 1; x < Width - 1; x++)
				cout << "��";
			cout << "��";
		}
		else if (y == Height - 1)
		{
			cout << "��";
			for (int x = 1; x < Width - 1; x++)
				cout << "��";
			cout << "��";
		}
		else
		{
			cout << "��";
			for (int x = 1; x < Width - 1; x++)
				cout << "��";
			cout << "��";
		}
	}
	return;
}

void Map::BoxSetting(int Start_x, int Start_y, int Width, int Height)
{
	for (int y = 0; y < Height; y++)
	{
		int x = 0;
		Mecro::gotoxy(Start_x, Start_y + y);
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


void Map::Menu()
{
	int m_iSelect;
	int m_iGame = OMOK;
	
	while (true)
	{
		Setting();
		BoxDraw(m_position.m_ix, m_position.m_iy, m_mapSize.m_iWidth, m_mapSize.m_iHeight);

		switch (m_iGame)
		{
		case OMOK:
			Mecro::DrawMidText("�� �� �� ��", MAPMAX, 6);
			break;
		case OTHELLO:
			Mecro::DrawMidText("�� �� �� �� ��", MAPMAX, 6);
			break;
		}
		Mecro::DrawMidText("1.���� ����", MAPMAX, 8);
		Mecro::DrawMidText("2.���� ����", MAPMAX, 10);
		Mecro::DrawMidText("3.���� ����", MAPMAX, 12);
		Mecro::DrawMidText("��������������������", MAPMAX, 14);
		Mecro::DrawMidText("��                ��", MAPMAX, 15);
		Mecro::DrawMidText("��������������������", MAPMAX, 16);
		Mecro::gotoxy(MAPMAX, 15);
		cin >> m_iSelect;


		switch (m_iSelect)
		{
		case 1:
			switch (m_iGame)
			{
			case OMOK: //����
				Omok_Play();
				break;
			case OTHELLO: //������
				Othello_Play();
				break;
			}
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


void Map::Omok_Play()
{
	int CharaterTurn = BLACK;
	m_turn = 1;
	bool ESC_Check = true;

	BoxDraw(m_position.m_ix, m_position.m_iy, m_mapSize.m_iWidth, m_mapSize.m_iHeight);
	Omok_ShowInfo();

	//ĳ���� �����ְ�
	m_Omok_BlackCharater.SetCharater("��", "Black");
	m_Omok_WhiteCharater.SetCharater("��", "White");

	//2ȸ�� �̻� �÷��� �� - ���� �ʱ�ȭ
	m_Omok_WhiteCharater.Reset_m_backXY();
	m_Omok_BlackCharater.Reset_m_backXY();

	/////////////////////////////////////////////////////////////////////
	//2ȸ�� �̻� �÷��� �� - ������ ��û : �⺻ false�� ����
	//������ ���·� ����� bool�� ��� ture�� �����ִ�.
	m_Omok_BlackCharater.SetBack(false);
	m_Omok_WhiteCharater.SetBack(false);

	//2ȸ�� �̻� �÷��� �� - ESC �ʱ�ȭ
	m_Omok_WhiteCharater.SetESC(false);
	m_Omok_BlackCharater.SetESC(false);
	
	while (true)
	{
		Mecro::gotoxy(MAPMAX + 2, MAPMAX + 4);
		cout << m_turn;

		if (CharaterTurn == BLACK)
		{//�ڵ� �ߺ�
			CharaterTurn = WHITE;
			ESC_Check = Omok_PlayerTurn(&m_Omok_BlackCharater, &m_Omok_WhiteCharater); //�������� > ��������
		}
		else if (CharaterTurn == WHITE)
		{
			CharaterTurn = BLACK;
			ESC_Check = Omok_PlayerTurn(&m_Omok_WhiteCharater, &m_Omok_BlackCharater);
		}
		m_turn++;

		if (ESC_Check == true)
			return;
	}
}

bool Map::Omok_PlayerTurn(Omok_Character* m_NowTurn_Charater, Omok_Character* m_NextTurn_Charater)
{
	m_NowTurn_Charater->GetBackTurn(m_turn);//������ Ƚ�� üũ
	m_NowTurn_Charater->Turn();//���� ����

	/////////////////////////////////////////////////////////////////////
	//������ ��û Ȯ��
	if (m_NowTurn_Charater->GetBack() == true)
	{
		//black���� ������ ��û�� �޾� white���� ������ ���
		m_NextTurn_Charater->SetBack(true);
		m_NowTurn_Charater->SetBack(false);

		//m_turn�� 10�� ���� ��� �����ڸ��� �������� �ʾƼ�
		Mecro::gotoxy(MAPMAX + 2, MAPMAX + 4);
		cout << "       ";
		m_turn -= 2;
	}

	//ESC
	if (m_NowTurn_Charater->GetEsc() == true)
	{//�ϴ� ����â ����
		Mecro::ErasePoint(0, MAPMAX);
		return true;
	}
}

void Map::Omok_ShowInfo()
{
	Mecro::DrawMidText("====����Ű====", MAPMAX, MAPMAX);
	Mecro::DrawMidText("�̵� : A,S,W,D  ������ : ENTER", MAPMAX, MAPMAX + 1);
	/////////////////////////////////////////////////////////////////////
	Mecro::DrawMidText("������ : N  ���� : ESC", MAPMAX, MAPMAX + 2);
	Mecro::DrawMidText("Player Name : ", 1, MAPMAX + 3);
	/////////////////////////////////////////////////////////////////////
	Mecro::DrawMidText("������ : ", MAPMAX + 11, MAPMAX + 3);
	Mecro::DrawMidText("Turn : ", MAPMAX - 2, MAPMAX + 4);
}




//-----------------------------------------



void Map::Othello_Play()
{
	int CharaterTurn = BLACK;
	m_turn = 1;
	bool ESC_Check = true;

	BoxDraw(m_position.m_ix, m_position.m_iy, m_mapSize.m_iWidth, m_mapSize.m_iHeight);
	Othello_ShowInfo();

	//ĳ���� �����ְ�
	m_Othello_BlackCharater.SetCharater("��", "��", "Black");
	m_Othello_WhiteCharater.SetCharater("��", "��", "White");

	//2ȸ�� �̻� �÷��� �� - ESC �ʱ�ȭ
	m_Othello_WhiteCharater.SetESC(false);
	m_Othello_BlackCharater.SetESC(false);

	while (true)
	{
		Mecro::gotoxy(MAPMAX + 2, MAPMAX + 4);
		cout << m_turn;

		if (CharaterTurn == BLACK)
		{//�ڵ� �ߺ�
			CharaterTurn = WHITE;
			ESC_Check = Othello_PlayerTurn(&m_Othello_BlackCharater, &m_Othello_WhiteCharater); //�������� > ��������
		}
		else if (CharaterTurn == WHITE)
		{
			CharaterTurn = BLACK;
			ESC_Check = Othello_PlayerTurn(&m_Othello_WhiteCharater, &m_Othello_BlackCharater);
		}
		m_turn++;

		if (ESC_Check == true)
			return;
	}
}

bool Map::Othello_PlayerTurn(Othello_Character* m_NowTurn_Charater, Othello_Character* m_NextTurn_Charater)
{
	m_NowTurn_Charater->GetTurn(m_turn);//���� �Ǵ� ���� �� üũ
	m_NowTurn_Charater->Turn();

	//ESC
	if (m_NowTurn_Charater->GetEsc() == true)
	{//�ϴ� ����â ����
		Mecro::ErasePoint(0, MAPMAX);
		return true;
	}
}

void Map::Othello_ShowInfo()
{
	Mecro::DrawMidText("====����Ű====", MAPMAX, MAPMAX);
	Mecro::DrawMidText("�̵� : A,S,W,D  ������ : ENTER", MAPMAX, MAPMAX + 1);
	/////////////////////////////////////////////////////////////////////
	Mecro::DrawMidText("���� : ESC", MAPMAX, MAPMAX + 2);
	Mecro::DrawMidText("Player Name : ", MAPMAX - 2, MAPMAX + 3);
	/////////////////////////////////////////////////////////////////////
	Mecro::DrawMidText("Turn : ", MAPMAX - 2, MAPMAX + 4);
}

Map::~Map() { }