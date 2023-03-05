#include "GameManager.h"



GameManager::GameManager()
{//생성자 초기값
	m_iTurn = 1;
	m_iHeight = HEIGHT;
	m_iWidth = WIDTH;
	m_eGameType = GAMETYPE::FIVE_IN_A_ROW; //이런 식으로
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
{// 하단 정보창 변곡점
	DrawManager::DrawMidText("====조작키====", m_iWidth, m_iHeight); //m_iWidth 이용
	DrawManager::DrawMidText("이동 : A,S,W,D 돌놓기 : ENTER", m_iWidth, m_iHeight + 1);
	if(m_eGameType == GAMETYPE::FIVE_IN_A_ROW)
		DrawManager::DrawMidText("무르기 : N 종료 : ESC", m_iWidth, m_iHeight + 2);
	else
		DrawManager::DrawMidText("종료 : ESC", m_iWidth, m_iHeight + 2);
}

void GameManager::CurPlayerInfoDraw()
{//현재 플레이어의 정보. 하단의 키 정보와 따로 관리
	string Name = m_iTurn % 2 == (int)PLAYERTYPE::BLACK ? "Black" : "While"; 
	//삼항연산자. ture면 첫번째 반환 false면 두번째 반환
	//‘조건’ ? ‘A’ : ‘B’
	int UndoCount = m_Players[m_iTurn % 2].GetUndoCount(); //UndoCount 무르기 횟수 //m_iTurn % 2로 누구의 턴인지 판단
	string str;
	if (m_eGameType == GAMETYPE::FIVE_IN_A_ROW) //to_string은 int형을 string형으로 변환
		str = "Player Name : " + Name + "       무르기 : " + to_string(UndoCount) + "  ";
	else
		str = "Player Name : " + Name;
	DrawManager::DrawMidText(str, m_iWidth, m_iHeight + 3); //str이용해서 같은 방법으로 출력 가능하게
	DrawManager::DrawMidText("Turn : " + to_string(m_iTurn) + "  ", m_iWidth, m_iHeight + 4);
}

void GameManager::GameMain()
{
	char buf[256];
	sprintf(buf, "mode con: lines=%d cols=%d", m_iHeight + 5, (m_iWidth * 2) + 1); //sprintf가 버퍼에 사용될 변수로 출력된다고 함 //sprintf는 조합후 문자열 저장
	system(buf); //"mode con: lines=%d, 세로 cols=%d, 가로" 콘솔창 크기 조절 세로, 가로
	//별 떨어지는 것과, 미로에서 사용함
	while (1)
	{
		system("cls");
		DrawManager::DrawPanel(m_iWidth, m_iHeight);//판 싹다 그리는 거
		LobbyDraw(); //오목 오델로 시작 메뉴창 띄우는 거
		int Select;
		cin >> Select;
		switch ((LOBBYMENU)Select)//int형을 enum으로 형변환
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
	//init은 내 돌 setting과 유사
	//this 포인터. 현재의 객체는 CameManager. player에서 참조가 필요할 때를 위해.

	DrawManager::DrawPanel(m_iWidth, m_iHeight); //판 싹다 그리기
	InputInfoDraw(); //하단 정보창 
	while (true)
	{
		CurPlayerInfoDraw();//현재 플레이어의 정보
		switch (m_Players[m_iTurn % 2].Input(&m_Players[!(m_iTurn % 2)], m_iTurn, m_eGameType))
		{
			//Input은 Key enum을 리턴
			//&m_Players[!(m_iTurn % 2)] 적 플레이어의 주소
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
			{//방향키 return받아서 enum 이용+ Win까지 enum의 리턴 이용해서 경우를 보기 쉽게 관리
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
			getch(); //윈 화면 잠시 띄워두는 용도
			return;
		}
	}
}

GameManager::~GameManager()
{
}
