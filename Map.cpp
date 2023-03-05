#include "Map.h"


Map::Map() { }

string Map::mapLog[MAPMAX][MAPMAX]; //static은 선언 .cpp에서 해야 한다.


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
			cout << "┌";
			for (int x = 1; x < Width - 1; x++)
				cout << "┬";
			cout << "┐";
		}
		else if (y == Height - 1)
		{
			cout << "└";
			for (int x = 1; x < Width - 1; x++)
				cout << "┴";
			cout << "┘";
		}
		else
		{
			cout << "├";
			for (int x = 1; x < Width - 1; x++)
				cout << "┼";
			cout << "┤";
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
			mapLog[x][y] = "┌";
			for (x = 1; x < Width - 1; x++)
				mapLog[x][y] = "┬";
			mapLog[x][y] = "┐";
		}
		else if (y == Height - 1)
		{
			mapLog[x][y] = "└";
			for (x = 1; x < Width - 1; x++)
				mapLog[x][y] = "┴";
			mapLog[x][y] = "┘";
		}
		else
		{
			mapLog[x][y] = "├";
			for (x = 1; x < Width - 1; x++)
				mapLog[x][y] = "┼";
			mapLog[x][y] = "┤";
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
			Mecro::DrawMidText("★ 오 목 ★", MAPMAX, 6);
			break;
		case OTHELLO:
			Mecro::DrawMidText("★ 오 델 로 ★", MAPMAX, 6);
			break;
		}
		Mecro::DrawMidText("1.게임 시작", MAPMAX, 8);
		Mecro::DrawMidText("2.게임 변경", MAPMAX, 10);
		Mecro::DrawMidText("3.게임 종료", MAPMAX, 12);
		Mecro::DrawMidText("┌────────┐", MAPMAX, 14);
		Mecro::DrawMidText("│                │", MAPMAX, 15);
		Mecro::DrawMidText("└────────┘", MAPMAX, 16);
		Mecro::gotoxy(MAPMAX, 15);
		cin >> m_iSelect;


		switch (m_iSelect)
		{
		case 1:
			switch (m_iGame)
			{
			case OMOK: //오목
				Omok_Play();
				break;
			case OTHELLO: //오델로
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

	//캐릭터 정해주고
	m_Omok_BlackCharater.SetCharater("○", "Black");
	m_Omok_WhiteCharater.SetCharater("●", "White");

	//2회차 이상 플레이 시 - 스택 초기화
	m_Omok_WhiteCharater.Reset_m_backXY();
	m_Omok_BlackCharater.Reset_m_backXY();

	/////////////////////////////////////////////////////////////////////
	//2회차 이상 플레이 시 - 무르기 신청 : 기본 false로 유지
	//무르기 상태로 종료시 bool이 계속 ture로 남아있다.
	m_Omok_BlackCharater.SetBack(false);
	m_Omok_WhiteCharater.SetBack(false);

	//2회차 이상 플레이 시 - ESC 초기화
	m_Omok_WhiteCharater.SetESC(false);
	m_Omok_BlackCharater.SetESC(false);
	
	while (true)
	{
		Mecro::gotoxy(MAPMAX + 2, MAPMAX + 4);
		cout << m_turn;

		if (CharaterTurn == BLACK)
		{//코드 중복
			CharaterTurn = WHITE;
			ESC_Check = Omok_PlayerTurn(&m_Omok_BlackCharater, &m_Omok_WhiteCharater); //깊은복사 > 얕은복사
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
	m_NowTurn_Charater->GetBackTurn(m_turn);//무르기 횟수 체크
	m_NowTurn_Charater->Turn();//게임 진행

	/////////////////////////////////////////////////////////////////////
	//무르기 신청 확인
	if (m_NowTurn_Charater->GetBack() == true)
	{
		//black에서 무르기 신청을 받아 white에게 무르기 명령
		m_NextTurn_Charater->SetBack(true);
		m_NowTurn_Charater->SetBack(false);

		//m_turn이 10을 넘을 경우 일의자리가 지워지지 않아서
		Mecro::gotoxy(MAPMAX + 2, MAPMAX + 4);
		cout << "       ";
		m_turn -= 2;
	}

	//ESC
	if (m_NowTurn_Charater->GetEsc() == true)
	{//하단 정보창 지움
		Mecro::ErasePoint(0, MAPMAX);
		return true;
	}
}

void Map::Omok_ShowInfo()
{
	Mecro::DrawMidText("====조작키====", MAPMAX, MAPMAX);
	Mecro::DrawMidText("이동 : A,S,W,D  돌놓기 : ENTER", MAPMAX, MAPMAX + 1);
	/////////////////////////////////////////////////////////////////////
	Mecro::DrawMidText("무르기 : N  종료 : ESC", MAPMAX, MAPMAX + 2);
	Mecro::DrawMidText("Player Name : ", 1, MAPMAX + 3);
	/////////////////////////////////////////////////////////////////////
	Mecro::DrawMidText("무르기 : ", MAPMAX + 11, MAPMAX + 3);
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

	//캐릭터 정해주고
	m_Othello_BlackCharater.SetCharater("○", "●", "Black");
	m_Othello_WhiteCharater.SetCharater("●", "○", "White");

	//2회차 이상 플레이 시 - ESC 초기화
	m_Othello_WhiteCharater.SetESC(false);
	m_Othello_BlackCharater.SetESC(false);

	while (true)
	{
		Mecro::gotoxy(MAPMAX + 2, MAPMAX + 4);
		cout << m_turn;

		if (CharaterTurn == BLACK)
		{//코드 중복
			CharaterTurn = WHITE;
			ESC_Check = Othello_PlayerTurn(&m_Othello_BlackCharater, &m_Othello_WhiteCharater); //깊은복사 > 얕은복사
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
	m_NowTurn_Charater->GetTurn(m_turn);//승패 판단 위해 턴 체크
	m_NowTurn_Charater->Turn();

	//ESC
	if (m_NowTurn_Charater->GetEsc() == true)
	{//하단 정보창 지움
		Mecro::ErasePoint(0, MAPMAX);
		return true;
	}
}

void Map::Othello_ShowInfo()
{
	Mecro::DrawMidText("====조작키====", MAPMAX, MAPMAX);
	Mecro::DrawMidText("이동 : A,S,W,D  돌놓기 : ENTER", MAPMAX, MAPMAX + 1);
	/////////////////////////////////////////////////////////////////////
	Mecro::DrawMidText("종료 : ESC", MAPMAX, MAPMAX + 2);
	Mecro::DrawMidText("Player Name : ", MAPMAX - 2, MAPMAX + 3);
	/////////////////////////////////////////////////////////////////////
	Mecro::DrawMidText("Turn : ", MAPMAX - 2, MAPMAX + 4);
}

Map::~Map() { }