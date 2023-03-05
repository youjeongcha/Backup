#include "GameManager.h"



GameManager::GameManager()
{//������ �ʱⰪ
	m_iTurn = 1;
	m_iHeight = HEIGHT;
	m_iWidth = WIDTH;
	m_eGameType = GAMETYPE::FIVE_IN_A_ROW; //�̷� ������
}

void GameManager::LobbyDraw()
{
	switch (m_eGameType)
	{
	case GAMETYPE::FIVE_IN_A_ROW:
		DrawManager::DrawMidText("�� �� �� ��", m_iWidth, m_iHeight * 0.3f);
		break;
	case GAMETYPE::OTHELLO:
		DrawManager::DrawMidText("�� �� �� �� ��", m_iWidth, m_iHeight * 0.3f);
		break;
	default:
		break;
	}
	DrawManager::DrawMidText("1.���� ����", m_iWidth, m_iHeight * 0.4f);
	DrawManager::DrawMidText("2.���� ����", m_iWidth, m_iHeight * 0.5f);
	DrawManager::DrawMidText("3.���� ����", m_iWidth, m_iHeight * 0.6f);
	DrawManager::BoxDraw(m_iWidth, m_iHeight * 0.7, m_iWidth / 2, 3);
	DrawManager::gotoxy(m_iWidth, m_iHeight * 0.7 + 1);
}

void GameManager::InputInfoDraw()
{// �ϴ� ����â ������
	DrawManager::DrawMidText("====����Ű====", m_iWidth, m_iHeight); //m_iWidth �̿�
	DrawManager::DrawMidText("�̵� : A,S,W,D ������ : ENTER", m_iWidth, m_iHeight + 1);
	if(m_eGameType == GAMETYPE::FIVE_IN_A_ROW)
		DrawManager::DrawMidText("������ : N ���� : ESC", m_iWidth, m_iHeight + 2);
	else
		DrawManager::DrawMidText("���� : ESC", m_iWidth, m_iHeight + 2);
}

void GameManager::CurPlayerInfoDraw()
{//���� �÷��̾��� ����. �ϴ��� Ű ������ ���� ����
	string Name = m_iTurn % 2 == (int)PLAYERTYPE::BLACK ? "Black" : "While"; 
	//���׿�����. ture�� ù��° ��ȯ false�� �ι�° ��ȯ
	//�����ǡ� ? ��A�� : ��B��
	int UndoCount = m_Players[m_iTurn % 2].GetUndoCount(); //UndoCount ������ Ƚ�� //m_iTurn % 2�� ������ ������ �Ǵ�
	string str;
	if (m_eGameType == GAMETYPE::FIVE_IN_A_ROW) //to_string�� int���� string������ ��ȯ
		str = "Player Name : " + Name + "       ������ : " + to_string(UndoCount) + "  ";
	else
		str = "Player Name : " + Name;
	DrawManager::DrawMidText(str, m_iWidth, m_iHeight + 3); //str�̿��ؼ� ���� ������� ��� �����ϰ�
	DrawManager::DrawMidText("Turn : " + to_string(m_iTurn) + "  ", m_iWidth, m_iHeight + 4);
}

void GameManager::GameMain()
{
	char buf[256];
	sprintf(buf, "mode con: lines=%d cols=%d", m_iHeight + 5, (m_iWidth * 2) + 1); //sprintf�� ���ۿ� ���� ������ ��µȴٰ� �� //sprintf�� ������ ���ڿ� ����
	system(buf); //"mode con: lines=%d, ���� cols=%d, ����" �ܼ�â ũ�� ���� ����, ����
	//�� �������� �Ͱ�, �̷ο��� �����
	while (1)
	{
		system("cls");
		DrawManager::DrawPanel(m_iWidth, m_iHeight);//�� �ϴ� �׸��� ��
		LobbyDraw(); //���� ������ ���� �޴�â ���� ��
		int Select;
		cin >> Select;
		switch ((LOBBYMENU)Select)//int���� enum���� ����ȯ
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


void GameManager::Play()
{
	system("cls");
	m_iTurn = 1;
	m_Players[(int)PLAYERTYPE::BLACK].Init(m_iWidth, m_iHeight, PLAYERTYPE::BLACK, this);
	m_Players[(int)PLAYERTYPE::WHITE].Init(m_iWidth, m_iHeight, PLAYERTYPE::WHITE, this);
	//init�� �� �� setting�� ����
	//this ������. ������ ��ü�� CameManager. player���� ������ �ʿ��� ���� ����.

	DrawManager::DrawPanel(m_iWidth, m_iHeight); //�� �ϴ� �׸���
	InputInfoDraw(); //�ϴ� ����â 
	while (true)
	{
		CurPlayerInfoDraw();//���� �÷��̾��� ����
		switch (m_Players[m_iTurn % 2].Input(&m_Players[!(m_iTurn % 2)], m_iTurn, m_eGameType))
		{
			//Input�� Key enum�� ����
			//&m_Players[!(m_iTurn % 2)] �� �÷��̾��� �ּ�
		case KEY::ESC:
			return;
		case KEY::DROP:
			m_iTurn++;
			break;
		case KEY::UNDO:
			if (m_iTurn > 1)
			{
				m_iTurn--;
				m_Players[m_iTurn % 2].UndoSet();
			}
			break;
		case KEY::WIN:
			if (m_eGameType == GAMETYPE::FIVE_IN_A_ROW)
			{//����Ű return�޾Ƽ� enum �̿�+ Win���� enum�� ���� �̿��ؼ� ��츦 ���� ���� ����
				if (m_iTurn % 2 == (int)PLAYERTYPE::BLACK)
					DrawManager::DrawMidText("Black Win", m_iWidth, m_iHeight * 0.5f);
				else
					DrawManager::DrawMidText("White Win", m_iWidth, m_iHeight * 0.5f);
			}
			else
			{
				if(m_Players[(int)PLAYERTYPE::BLACK].GetStoneCount() > m_Players[(int)PLAYERTYPE::WHITE].GetStoneCount())
					DrawManager::DrawMidText("Black Win", m_iWidth, m_iHeight * 0.5f);
				else
					DrawManager::DrawMidText("White Win", m_iWidth, m_iHeight * 0.5f);
			}
			getch(); //�� ȭ�� ��� ����δ� �뵵
			return;
		}
	}
}

GameManager::~GameManager()
{
}
