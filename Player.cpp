#include "Player.h"
#include "GameManager.h"

Player::Player()
{
	bMoveStatus = false;
	bBackCheck = false;
}


int Player::Move(int _iGame)
{
	while (true)
	{
		char ch = getch();
		Position prevPosition = m_position;//중요 //이번 턴에서 돌이 맨 처음 위치한 자리.(지나간 자리 복구할때 주로 이용한다.)
		switch (ch)
		{
		case DIRECTION::LEFT:
			if (m_position.m_ix - 1 >= m_mapSize.m_iLeft) //문자열 2칸 고려
			{
				m_position.m_ix -= 2;
				bMoveStatus = true;
			}
			break;
		case DIRECTION::RIGHT:
			if (m_position.m_ix + 1 < m_mapSize.m_iRight - 2)
			{
				m_position.m_ix += 2;
				bMoveStatus = true;
			}
			break;
		case DIRECTION::UP:
			if (m_position.m_iy - 1 >= m_mapSize.m_iUp)
			{
				m_position.m_iy--;
				bMoveStatus = true;
			}
			break;
		case DIRECTION::DOWN:
			if (m_position.m_iy + 1 <= m_mapSize.m_iDown - 1)
			{
				m_position.m_iy++;
				bMoveStatus = true;
			}
			break;
		case DIRECTION::ENTER:
			if ((GameManager::mapLog[m_position.m_ix / 2][m_position.m_iy] == "○") ||
				(GameManager::mapLog[m_position.m_ix / 2][m_position.m_iy] == "●") ||
				(GameManager::mapLog[m_position.m_ix / 2][m_position.m_iy] == "※"))
			{
				bMoveStatus = false;
			}
			else
			{
				bMoveStatus = true;

				//캐릭터(바둑돌)를 맵에 기록
				GameManager::mapLog[m_position.m_ix / 2][m_position.m_iy] = m_strCharacter;

				if (_iGame == OMOK)
				{
					Position m_temp;

					//해당 턴에 무르기 ※ 되어있는 상황이면 복구
					if (bBackCheck == true)
					{
						m_temp = m_backXY.top();
						BackMapDraw(&m_temp);
						bBackCheck = false;
						m_backXY.pop();
					}

					//무르기 할 좌표 확보(상시2)
					m_temp.m_ix = m_position.m_ix / 2;
					m_temp.m_iy = m_position.m_iy;
					m_backXY.push(m_temp);

					//승패 확인 - 오목
					if (m_turn >= OMOK_WINJUGE)
					{
						//bool m_bCheck;
						Position m_CheckCount;
						m_CheckCount.m_ix = m_position.m_ix / 2;
						m_CheckCount.m_iy = m_position.m_iy;

						if (WinCheck(m_CheckCount, 0, -1, 0, 1) == true) //상하
							bESC = true;
						if (WinCheck(m_CheckCount, -1, 0, 1, 0) == true) //좌우
							bESC = true;
						if (WinCheck(m_CheckCount, 1, -1, -1, -1) == true) //대1,3
							bESC = true;
						if (WinCheck(m_CheckCount, 1, 1, -1, 1) == true) //대2,4
							bESC = true;

						//if (bESC == true)
						//{
						//	DrawManager::gotoxy(MAPMAX - 4, MAPMAX / 2);
						//	cout << m_player_stone << " Win";
						//	char ch = getch();
						//}
					}
				}
				else if (_iGame == OTHELLO)
				{
					//양 끝단에 다른 색 바둑으로 막히면 바둑돌 먹힘
					Position m_CheckCount;
					m_CheckCount.m_ix = m_position.m_ix / 2;
					m_CheckCount.m_iy = m_position.m_iy;

					StoneChange(m_CheckCount, 0, -1, 0, 1, C_UP, C_DOWN); //상하
					StoneChange(m_CheckCount, -1, 0, 1, 0, C_LEFT, C_RIGHT); //좌우
					StoneChange(m_CheckCount, 1, -1, 1, 1, C_CROSS1, C_CROSS2); //대1,3
					StoneChange(m_CheckCount, -1, 1, -1, -1, C_CROSS3, C_CROSS4); //대2,4


					//승리 체크
					if (m_turn == MAXSTONE)
					{//1.바둑판이 다 채워지면 > 턴 400이 되면 검사
						WinCheck_StoneCount(MAXSTONE);
					}
					else if (m_turn >= OTHELLO_WINJUGE)
					{//2.바둑돌이 화면상에 한가지 돌만 남으면 > 10턴 이상부터
						WinCheck_StoneCount(OTHELLO_WINJUGE);
					}
				}	
				return ENTER;
			}
			break;
		case DIRECTION::BACK:
			if ((_iGame == OMOK) &&
				(m_backCount != 0) && (m_turn > 1))
			{
				Position m_temp;
				//현재 두고 있는 돌 지움(무르기 한 턴의 돌)
				DrawManager::gotoxy(m_position.m_ix, m_position.m_iy);
				cout << GameManager::mapLog[prevPosition.m_ix / 2][prevPosition.m_iy];

				if (bBackCheck == true)
				{
					m_temp = m_backXY.top();
					BackMapDraw(&m_temp);
					bBackCheck = false;
					m_backXY.pop();
				}

				//이전 돌 무르기 신청
				bBackCheck = true;

				m_backCount--;
				return BACK;
			}
			break;
		case DIRECTION::ESC:
			bESC = true;
			return ESC;
		}
		if (bMoveStatus)
		{//캐릭터 이동하고 지난 자리 처리
			DrawManager::gotoxy(prevPosition.m_ix, prevPosition.m_iy);//원인해결 위해 추가
			cout << GameManager::mapLog[prevPosition.m_ix / 2][prevPosition.m_iy];//원인
			Draw();
		}
	}
}

/////////////////////////////////////////////////////////////////////
bool Player::WinCheck(Position m_CheckCount, int m_X1, int m_Y1, int m_X2, int m_Y2)
{//바둑돌 갯수 카운트
	int m_count = 1;

	m_count = WinCheck(m_CheckCount, m_count, m_X1, m_Y1);
	m_count = WinCheck(m_CheckCount, m_count, m_X2, m_Y2);

	if (m_count == 5) //오목 성공
		return true;
	else
		return false;
}

/////////////////////////////////////////////////////////////////////
int Player::WinCheck(Position m_CheckCount, int m_count, int m_checkX, int m_checkY)
{//바둑돌 입력받는 방향따라 좌표 판단하고. 해당 방향에 돌 있으면 count++ 
	for (int i = 0; i < 5; i++)
	{
		if (GameManager::mapLog[m_CheckCount.m_ix][m_CheckCount.m_iy] == GameManager::mapLog[m_CheckCount.m_ix + m_checkX][m_CheckCount.m_iy + m_checkY])
		{
			m_CheckCount.m_ix = m_CheckCount.m_ix + m_checkX;
			m_CheckCount.m_iy = m_CheckCount.m_iy + m_checkY;

			m_count++;
		}
		else
			break;
	}
	return m_count;
}


void Player::StoneChange(Position m_CheckCount, int m_X1, int m_Y1, int m_X2, int m_Y2, int m_direction1, int m_direction2)
{//바둑돌 갯수 카운트
	StoneChange(m_CheckCount, m_X1, m_Y1, m_direction1);
	StoneChange(m_CheckCount, m_X2, m_Y2, m_direction2);
}

void Player::StoneChange(Position m_CheckCount, int m_checkX, int m_checkY, int m_direction)
{//바둑돌 입력받는 방향따라 좌표 판단하고. 해당 방향에 돌 있으면 count++ 
	int m_count = 0; //변환해야 할 돌 갯수 판단
	Position m_temp;

	m_temp.m_ix = m_CheckCount.m_ix;
	m_temp.m_iy = m_CheckCount.m_iy;

	while (true)
	{
		//검은돌 흰돌 반반 일렬로 배치하면 마지막에 한 줄을 채운 색으로 다 변해버리는 상황 방지 (좌표가 -1이 되면 발생)
		if (m_Compare_player_stone == GameManager::mapLog[m_CheckCount.m_ix + m_checkX][m_CheckCount.m_iy + m_checkY] &&
			((m_CheckCount.m_ix + m_checkX) >= 0) && ((m_CheckCount.m_iy + m_checkY) >= 0) &&
			((m_CheckCount.m_ix + m_checkX) < 20) && ((m_CheckCount.m_iy + m_checkY) < 20))
		{//현재 턴인 돌과 현재 체크하는 방향에 있는 돌이 다른 돌인지 확인
			//(좌표가 -1이 되는 경우 제외) (돌 표시할때와 m_CheckCount가 달라서 실행하는데 필수는 아님)
		 // Map::mapLog[m_CheckCount.m_ix + m_checkX][m_CheckCount.m_iy + m_checkY] 사라질 돌 좌표

			m_CheckCount.m_ix += m_checkX;
			m_CheckCount.m_iy += m_checkY;

			m_count++;

			if (m_strCharacter == GameManager::mapLog[m_CheckCount.m_ix + m_checkX][m_CheckCount.m_iy + m_checkY] &&
				((m_CheckCount.m_ix + m_checkX) >= 0) && ((m_CheckCount.m_iy + m_checkY) >= 0) &&
				((m_CheckCount.m_ix + m_checkX) < 20) && ((m_CheckCount.m_iy + m_checkY) < 20))
			{//맞은편에 현재 턴에 둔 바둑돌과 같은 게 있으면 사이의 돌 변환
				//(좌표가 -1이 되는 경우 제외) (필수)

				switch (m_direction)
				{//count 이용
				case C_UP:
					for (int i = 1; i <= m_count; i++)
					{
						GameManager::mapLog[m_temp.m_ix][m_temp.m_iy - i] = m_strCharacter;
						DrawManager::DrawPoint(GameManager::mapLog[m_temp.m_ix][m_temp.m_iy - i], m_temp.m_ix, m_temp.m_iy - i);
					}
					break;
				case C_DOWN:
					for (int i = 1; i <= m_count; i++)
					{
						GameManager::mapLog[m_temp.m_ix][m_temp.m_iy + i] = m_strCharacter;
						DrawManager::DrawPoint(GameManager::mapLog[m_temp.m_ix][m_temp.m_iy + i], m_temp.m_ix, m_temp.m_iy + i);
					}
					break;
				case C_LEFT:
					for (int i = 1; i <= m_count; i++)
					{
						GameManager::mapLog[m_temp.m_ix - i][m_temp.m_iy] = m_strCharacter;
						DrawManager::DrawPoint(GameManager::mapLog[m_temp.m_ix - i][m_temp.m_iy], m_temp.m_ix - i, m_temp.m_iy);
					}
					break;
				case C_RIGHT:
					for (int i = 1; i <= m_count; i++)
					{
						GameManager::mapLog[m_temp.m_ix + i][m_temp.m_iy] = m_strCharacter;
						DrawManager::DrawPoint(GameManager::mapLog[m_temp.m_ix + i][m_temp.m_iy], m_temp.m_ix + i, m_temp.m_iy);
					}
					break;
				case C_CROSS1:
					for (int i = 1; i <= m_count; i++)
					{
						GameManager::mapLog[m_temp.m_ix + i][m_temp.m_iy - i] = m_strCharacter;
						DrawManager::DrawPoint(GameManager::mapLog[m_temp.m_ix + i][m_temp.m_iy - i], m_temp.m_ix + i, m_temp.m_iy - i);
					}
					break;
				case C_CROSS2:
					for (int i = 1; i <= m_count; i++)
					{
						GameManager::mapLog[m_temp.m_ix + i][m_temp.m_iy + i] = m_strCharacter;
						DrawManager::DrawPoint(GameManager::mapLog[m_temp.m_ix + i][m_temp.m_iy + i], m_temp.m_ix + i, m_temp.m_iy + i);
					}
					break;
				case C_CROSS3:
					for (int i = 1; i <= m_count; i++)
					{
						GameManager::mapLog[m_temp.m_ix - i][m_temp.m_iy + i] = m_strCharacter;
						DrawManager::DrawPoint(GameManager::mapLog[m_temp.m_ix - i][m_temp.m_iy + i], m_temp.m_ix - i, m_temp.m_iy + i);
					}
					break;
				case C_CROSS4:
					for (int i = 1; i <= m_count; i++)
					{
						GameManager::mapLog[m_temp.m_ix - i][m_temp.m_iy - i] = m_strCharacter;
						DrawManager::DrawPoint(GameManager::mapLog[m_temp.m_ix - i][m_temp.m_iy - i], m_temp.m_ix - i, m_temp.m_iy - i);
					}
					break;
				}
			}
		}
		else
			break;
	}
}


//-------------------------------------------


void Player::WinCheck_StoneCount(int m_winType)
{
	int m_winCheck;
	int m_blackCount = 0;
	int m_whiteCount = 0;

	for (int x = 0; x < MAPMAX; x++)
	{
		for (int y = 0; y < MAPMAX; y++)
		{
			if (GameManager::mapLog[x][y] == "○")
				m_blackCount++;
			if (GameManager::mapLog[x][y] == "●")
				m_whiteCount++;
		}
	}


	if (m_winType == MAXSTONE)
	{
		//바둑돌 수량 비교
		if (m_blackCount > m_whiteCount)
			m_winCheck = BLACK;
		else if (m_whiteCount > m_blackCount)
			m_winCheck = WHITE;

		bESC = true;
	}
	else if ((m_winType == OTHELLO_WINJUGE) && (m_blackCount == 0 || m_whiteCount == 0))
	{
		//화면에 한 색의 바둑돌만 남는 경우
		if (m_blackCount == 0)
			m_winCheck = WHITE;
		else if (m_whiteCount == 0)
			m_winCheck = BLACK;

		bESC = true;
	}

	////승리 출력
	//if (bESC == true)
	//{
	//	DrawManager::gotoxy(MAPMAX - 4, MAPMAX / 2);
	//	if (m_winCheck == BLACK)
	//		cout << "Black Win";
	//	else
	//		cout << "White Win";
	//	char ch = getch();
	//}

}

//-------------------------------------------

void Player::BackMapDraw(Position* m_temp)
{
	GameManager::mapLog[m_temp->m_ix][m_temp->m_iy] = DrawManager::MapDraw(m_temp->m_ix, m_temp->m_iy);//m_temp가 쓰레기값
	DrawManager::gotoxy(m_temp->m_ix * 2, m_temp->m_iy);
	cout << GameManager::mapLog[m_temp->m_ix][m_temp->m_iy];
}

//-------------------------------------------


void Player::ShowPlayerInfo(int _iGame)
{
	if (_iGame == OMOK)
	{
		DrawManager::DrawMidText(m_player_stone, 17, MAPMAX + 3);
		DrawManager::gotoxy(MAPMAX + 16, MAPMAX + 3);
		cout << m_backCount;
	}
	else if (_iGame == OTHELLO)
	{
		DrawManager::DrawMidText(m_player_stone, MAPMAX + 7, MAPMAX + 3);
	}
}

void Player::Draw()
{
	DrawManager::TextDraw(m_strCharacter, m_position.m_ix, m_position.m_iy);
}


int Player::Turn(int _iGame)
{
	ShowPlayerInfo(_iGame);
	Draw();

	/////////////////////////////////////////////////////////////////////
	//m_bBackCheck으로 앞 바둑돌의 턴에서 무르기 신청했을 경우(true) 
	//무르기 신청된 돌 표시 ※
	if ((_iGame == OMOK) &&
		(bBackCheck == true) && (m_turn >= 1))
	{//무르기 신청된 경우 && turn 1 까지만 무르기 가능,표시
		Position m_temp;
		m_temp = m_backXY.top();

		GameManager::mapLog[m_temp.m_ix][m_temp.m_iy] = "※";
		DrawManager::gotoxy(m_temp.m_ix * 2, m_temp.m_iy);
		cout << GameManager::mapLog[m_temp.m_ix][m_temp.m_iy];
	}

	return Move(_iGame);
}


Player::~Player() { }
