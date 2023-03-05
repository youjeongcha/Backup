#include "GameManager.h"



GameManager::GameManager()
{
	m_iHeight = (int)FIVE_IN_A_ROW_BOARD_SIZE::HEIGHT;
	m_iWidth = (int)FIVE_IN_A_ROW_BOARD_SIZE::WIDTH;
	m_eGameType = GAMETYPE::FIVE_IN_A_ROW;
}

void GameManager::LobbyDraw()
{
	switch (m_eGameType)
	{
	case GAMETYPE::FIVE_IN_A_ROW:
		DrawManager::DrawMidText("★ 오 목 ★", m_iWidth, m_iHeight * 0.3f);
		break;
	case GAMETYPE::OTHELLO:
		DrawManager::DrawMidText("★ 오 델 로 ★", m_iWidth, m_iHeight * 0.3f);
		break;
	default:
		break;
	}
	DrawManager::DrawMidText("1.게임 시작", m_iWidth, m_iHeight * 0.4f);
	DrawManager::DrawMidText("2.게임 변경", m_iWidth, m_iHeight * 0.5f);
	DrawManager::DrawMidText("3.게임 종료", m_iWidth, m_iHeight * 0.6f);
	DrawManager::BoxDraw(m_iWidth, m_iHeight * 0.7, m_iWidth / 2, 3);
	DrawManager::gotoxy(m_iWidth, m_iHeight * 0.7 + 1);
}

void GameManager::InputInfoDraw()
{
	DrawManager::DrawMidText("====조작키====", m_iWidth, m_iHeight);
	DrawManager::DrawMidText("이동 : A,S,W,D 돌놓기 : ENTER", m_iWidth, m_iHeight + 1);
	if(m_eGameType == GAMETYPE::FIVE_IN_A_ROW)
		DrawManager::DrawMidText("무르기 : N 종료 : ESC", m_iWidth, m_iHeight + 2);
	else
		DrawManager::DrawMidText("종료 : ESC", m_iWidth, m_iHeight + 2);
}

void GameManager::CurPlayerInfoDraw()
{
	string Name = m_iTurn % 2 == (int)PLAYERTYPE::BLACK ? "Black" : "While";
	int UndoCount = m_Players[m_iTurn % 2].GetUndoCount();
	string str;
	if (m_eGameType == GAMETYPE::FIVE_IN_A_ROW)
		str = "Player Name : " + Name + "       무르기 : " + to_string(UndoCount) + "  ";
	else
		str = "Player Name : " + Name;
	DrawManager::DrawMidText(str, m_iWidth, m_iHeight + 3);
	DrawManager::DrawMidText("Turn : " + to_string(m_iTurn) + "  ", m_iWidth, m_iHeight + 4);
}

void GameManager::GameMain()
{
	char buf[256];
	sprintf(buf, "mode con: lines=%d cols=%d", m_iHeight + 5, (m_iWidth * 2) + 1);
	system(buf);
	while (1)
	{
		m_iHeight = (int)FIVE_IN_A_ROW_BOARD_SIZE::HEIGHT;
		m_iWidth = (int)FIVE_IN_A_ROW_BOARD_SIZE::WIDTH;
		system("cls");
		DrawManager::DrawPanel(m_iWidth, m_iHeight);
		LobbyDraw();
		int Select;
		cin >> Select;
		switch ((LOBBYMENU)Select)
		{
		case LOBBYMENU::START:
			Play();
			break;
		case LOBBYMENU::OPTION:
			if (m_eGameType == GAMETYPE::FIVE_IN_A_ROW)
				m_eGameType = GAMETYPE::OTHELLO;
			else
				m_eGameType = GAMETYPE::FIVE_IN_A_ROW;
			break;
		case LOBBYMENU::EXIT:
			return;
		}
	}
}


void GameManager::BoardSizeSet()
{
	switch (m_eGameType)
	{
	case GAMETYPE::FIVE_IN_A_ROW:
		m_iHeight = (int)FIVE_IN_A_ROW_BOARD_SIZE::HEIGHT;
		m_iWidth = (int)FIVE_IN_A_ROW_BOARD_SIZE::WIDTH;
		break;
	case GAMETYPE::OTHELLO:
		m_iHeight = (int)OTHELLO_BOARD_SIZE::HEIGHT;
		m_iWidth = (int)OTHELLO_BOARD_SIZE::WIDTH;
		break;
	}
}

void GameManager::Play()
{
	BoardSizeSet();
	system("cls");
	m_iTurn = 1;
	DrawManager::DrawPanel(m_iWidth, m_iHeight);
	InputInfoDraw();
	m_Players[(int)PLAYERTYPE::BLACK].Init(m_iWidth, m_iHeight, PLAYERTYPE::BLACK, this, m_eGameType);
	m_Players[(int)PLAYERTYPE::WHITE].Init(m_iWidth, m_iHeight, PLAYERTYPE::WHITE, this, m_eGameType);

	int PassCount = 0;

	while (true)
	{
		CurPlayerInfoDraw();
		switch (m_Players[m_iTurn % 2].Input(&m_Players[!(m_iTurn % 2)], m_iTurn, m_eGameType))
		{
		case KEY::ESC:
			return;
		case KEY::PASS:
			PassCount++;
			if (PassCount >= 2)
			{
				if (m_Players[(int)PLAYERTYPE::BLACK].GetStoneCount() > m_Players[(int)PLAYERTYPE::WHITE].GetStoneCount())
					DrawManager::DrawMidText("Black Win", m_iWidth, m_iHeight * 0.5f);
				else if (m_Players[(int)PLAYERTYPE::BLACK].GetStoneCount() < m_Players[(int)PLAYERTYPE::WHITE].GetStoneCount())
					DrawManager::DrawMidText("White Win", m_iWidth, m_iHeight * 0.5f);
				else
					DrawManager::DrawMidText("Draw", m_iWidth, m_iHeight * 0.5f);
				getch();
				return;
			}
			else
			{
				m_iTurn++;
				DrawManager::DrawMidText("Pass", m_iWidth, m_iHeight + 3);
				getch();
				DrawManager::DrawMidText("      ", m_iWidth, m_iHeight + 3);
			}
			break;
		case KEY::DROP:
		{
			PassCount = 0;
			m_iTurn++;
			break;
		}
		case KEY::UNDO:
			PassCount = 0;
			if (m_iTurn > 1)
			{
				m_iTurn--;
				m_Players[m_iTurn % 2].UndoSet();
			}
			break;
		case KEY::WIN:
			if (m_eGameType == GAMETYPE::FIVE_IN_A_ROW)
			{
				if (m_iTurn % 2 == (int)PLAYERTYPE::BLACK)
					DrawManager::DrawMidText("Black Win", m_iWidth, m_iHeight * 0.5f);
				else
					DrawManager::DrawMidText("White Win", m_iWidth, m_iHeight * 0.5f);
			}
			getch();
			return;
		}
	}
}

GameManager::~GameManager()
{
}
