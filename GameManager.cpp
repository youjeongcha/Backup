#include "GameManager.h"

GameManager::GameManager()
{
	m_iGame = OMOK;
}

string GameManager::mapLog[MAPMAX][MAPMAX]; //static은 선언 .cpp에서 해야 한다.


void GameManager::BoxSetting(string mapLog[][MAPMAX], int Start_x, int Start_y, int Width, int Height)
{
	for (int y = 0; y < Height; y++)
	{
		int x = 0;
		//DrawManager::gotoxy(Start_x, Start_y + y);
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
			DrawManager::DrawMidText("★ 오 목 ★", MAPMAX, 6);
			break;
		case OTHELLO:
			DrawManager::DrawMidText("★ 오 델 로 ★", MAPMAX, 6);
			break;
		}
		DrawManager::DrawMidText("1.게임 시작", MAPMAX, 8);
		DrawManager::DrawMidText("2.게임 변경", MAPMAX, 10);
		DrawManager::DrawMidText("3.게임 종료", MAPMAX, 12);
		DrawManager::DrawMidText("┌────────┐", MAPMAX, 14);
		DrawManager::DrawMidText("│                │", MAPMAX, 15);
		DrawManager::DrawMidText("└────────┘", MAPMAX, 16);
		DrawManager::gotoxy(MAPMAX, 15);
		cin >> m_iSelect;


		switch (m_iSelect)
		{
		case 1:
			Play();//인자를 받아서 일일이 오목 오델로 차이점 구분하기로★
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

	//캐릭터 정해주고
	m_BlackPlayer.SetCharater("○", "●", "Black");
	m_WhitePlayer.SetCharater("●", "○", "White");

	if (m_iGame == OMOK)
	{
		//2회차 이상 플레이 시 - 스택 초기화
		m_WhitePlayer.Reset_m_backXY();
		m_BlackPlayer.Reset_m_backXY();

		//2회차 이상 플레이 시 - 무르기 신청 : 기본 false로 유지
		//무르기 상태로 종료시 bool이 계속 ture로 남아있다.
		m_BlackPlayer.SetBack(false);
		m_WhitePlayer.SetBack(false);
	}

	//2회차 이상 플레이 시 - ESC 초기화
	m_WhitePlayer.SetESC(false);
	m_BlackPlayer.SetESC(false);

	while (true)
	{
		DrawManager::gotoxy(MAPMAX + 2, MAPMAX + 4);
		cout << m_turn;

		if (CharaterTurn == BLACK)
		{//코드 중복
			CharaterTurn = WHITE;
			ESC_Check = PlayerTurn(&m_BlackPlayer, &m_WhitePlayer, BLACK); //깊은복사 > 얕은복사
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
	m_NowTurn_Player->GetTurn(m_turn);//무르기 횟수 체크
	//m_NowTurn_Player->Turn(m_iGame);//게임 진행
	
	switch ((DIRECTION)m_NowTurn_Player->Turn(m_iGame)) //게임 진행
	{
	case BACK:
		//무르기 신청 확인
		if (m_iGame == OMOK &&
			(m_NowTurn_Player->GetBack() == true))
		{
			//black에서 무르기 신청을 받아 white에게 무르기 명령
			m_NextTurn_Player->SetBack(true);
			m_NowTurn_Player->SetBack(false);

			//m_turn이 10을 넘을 경우 일의자리가 지워지지 않아서
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
			DrawManager::ErasePoint(0, MAPMAX); //하단 정보창 지움

			return true;
		}
		return false;
	case ESC:
		DrawManager::ErasePoint(0, MAPMAX); //하단 정보창 지움
		return true;
	}

	////무르기 신청 확인
	//if (m_iGame == OMOK &&
	//	(m_NowTurn_Player->GetBack() == true))
	//{
	//	//black에서 무르기 신청을 받아 white에게 무르기 명령
	//	m_NextTurn_Player->SetBack(true);
	//	m_NowTurn_Player->SetBack(false);

	//	//m_turn이 10을 넘을 경우 일의자리가 지워지지 않아서
	//	DrawManager::gotoxy(MAPMAX + 2, MAPMAX + 4);
	//	cout << "       ";
	//	m_turn -= 2;
	//}

	////ESC
	//if (m_NowTurn_Player->GetEsc() == true)
	//{//하단 정보창 지움
	//	DrawManager::ErasePoint(0, MAPMAX);
	//	return true;
	//}
}

void GameManager::ShowInfo()
{
	DrawManager::DrawMidText("====조작키====", MAPMAX, MAPMAX);
	DrawManager::DrawMidText("이동 : A,S,W,D  돌놓기 : ENTER", MAPMAX, MAPMAX + 1);
	if (m_iGame == OMOK)
	{
		DrawManager::DrawMidText("무르기 : N  종료 : ESC", MAPMAX, MAPMAX + 2);
		DrawManager::DrawMidText("Player Name : ", 1, MAPMAX + 3);
		DrawManager::DrawMidText("무르기 : ", MAPMAX + 11, MAPMAX + 3);
		DrawManager::DrawMidText("Turn : ", MAPMAX - 2, MAPMAX + 4);
	}
	else
	{
		DrawManager::DrawMidText("종료 : ESC", MAPMAX, MAPMAX + 2);
		DrawManager::DrawMidText("Player Name : ", MAPMAX - 2, MAPMAX + 3);
		DrawManager::DrawMidText("Turn : ", MAPMAX - 2, MAPMAX + 4);
	}
}


GameManager::~GameManager() { }
