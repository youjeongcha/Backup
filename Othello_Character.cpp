#include "Othello_Character.h"
#include "Map.h"//맵이 인클루드 하는건 .cpp가 이니기 때문에 가능


Othello_Character::Othello_Character()
{
	bMoveStatus = false;
}


void Othello_Character::Move()
{
	while (true)
	{
		char ch = getch();
		Position prevPosition = m_position;//중요

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
			if ((Map::mapLog[m_position.m_ix / 2][m_position.m_iy] == "○") ||
				(Map::mapLog[m_position.m_ix / 2][m_position.m_iy] == "●"))
			{
				bMoveStatus = false;
			}
			else
			{
				bMoveStatus = true;

				//캐릭터(바둑돌)를 맵에 기록
				Map::mapLog[m_position.m_ix / 2][m_position.m_iy] = m_strCharacter;


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

				return;
			}
			break;
		case DIRECTION::ESC:
			bESC = true;
			return;
		}
		if (bMoveStatus)
		{//캐릭터 이동하고 지난 자리 처리
			//switch (ch)
			//{
			//case DIRECTION::LEFT:
			//case DIRECTION::RIGHT:
			//case DIRECTION::UP:
			//case DIRECTION::DOWN:
			//	Mecro::gotoxy(prevPosition.m_ix, prevPosition.m_iy);
			//	break;
			//}
			//Map map; //static 변수 사용불가
			Mecro::gotoxy(prevPosition.m_ix, prevPosition.m_iy);//원인해결 위해 추가
			cout << Map::mapLog[prevPosition.m_ix / 2][prevPosition.m_iy];//원인
			Draw();
		}
	}
}

/////////////////////////////////////////////////////////////////////
void Othello_Character::StoneChange(Position m_CheckCount, int m_X1, int m_Y1, int m_X2, int m_Y2, int m_direction1, int m_direction2)
{//바둑돌 갯수 카운트
	StoneChange(m_CheckCount, m_X1, m_Y1, m_direction1);
	StoneChange(m_CheckCount, m_X2, m_Y2, m_direction2);
}

void Othello_Character::StoneChange(Position m_CheckCount, int m_checkX, int m_checkY, int m_direction)
{//바둑돌 입력받는 방향따라 좌표 판단하고. 해당 방향에 돌 있으면 count++ 
	int m_count = 0; //변환해야 할 돌 갯수 판단
	Position m_temp;

	m_temp.m_ix = m_CheckCount.m_ix;
	m_temp.m_iy = m_CheckCount.m_iy;

	while (true)
	{
		//검은돌 흰돌 반반 일렬로 배치하면 마지막에 한 줄을 채운 색으로 다 변해버리는 상황 방지 (좌표가 -1이 되면 발생)
		if (m_Compare_strCharacter == Map::mapLog[m_CheckCount.m_ix + m_checkX][m_CheckCount.m_iy + m_checkY] &&
			((m_CheckCount.m_ix + m_checkX) >= 0) && ((m_CheckCount.m_iy + m_checkY) >= 0) &&
			((m_CheckCount.m_ix + m_checkX) < 20) && ((m_CheckCount.m_iy + m_checkY) < 20))
		{//현재 턴인 돌과 현재 체크하는 방향에 있는 돌이 다른 돌인지 확인
			//(좌표가 -1이 되는 경우 제외) (돌 표시할때와 m_CheckCount가 달라서 실행하는데 필수는 아님)
		 // Map::mapLog[m_CheckCount.m_ix + m_checkX][m_CheckCount.m_iy + m_checkY] 사라질 돌 좌표

			m_CheckCount.m_ix += m_checkX;
			m_CheckCount.m_iy += m_checkY;

			m_count++;

			if (m_strCharacter == Map::mapLog[m_CheckCount.m_ix + m_checkX][m_CheckCount.m_iy + m_checkY] &&
				((m_CheckCount.m_ix + m_checkX) >= 0) && ((m_CheckCount.m_iy + m_checkY) >= 0) && 
				((m_CheckCount.m_ix + m_checkX) < 20) && ((m_CheckCount.m_iy + m_checkY) < 20))
			{//맞은편에 현재 턴에 둔 바둑돌과 같은 게 있으면 사이의 돌 변환
				//(좌표가 -1이 되는 경우 제외) (필수)

				switch (m_direction)
				{//count 이용
				case C_UP:
					for (int i = 1; i <= m_count; i++)
					{
						Map::mapLog[m_temp.m_ix][m_temp.m_iy - i] = m_strCharacter;
						Mecro::DrawPoint(Map::mapLog[m_temp.m_ix][m_temp.m_iy - i], m_temp.m_ix, m_temp.m_iy - i);
					}
					break;
				case C_DOWN:
					for (int i = 1; i <= m_count; i++)
					{
						Map::mapLog[m_temp.m_ix][m_temp.m_iy + i] = m_strCharacter;
						Mecro::DrawPoint(Map::mapLog[m_temp.m_ix][m_temp.m_iy + i], m_temp.m_ix, m_temp.m_iy + i);
					}
					break;
				case C_LEFT:
					for (int i = 1; i <= m_count; i++)
					{
						Map::mapLog[m_temp.m_ix - i][m_temp.m_iy] = m_strCharacter;
						Mecro::DrawPoint(Map::mapLog[m_temp.m_ix - i][m_temp.m_iy], m_temp.m_ix - i, m_temp.m_iy);
					}
					break;
				case C_RIGHT:
					for (int i = 1; i <= m_count; i++)
					{
						Map::mapLog[m_temp.m_ix + i][m_temp.m_iy] = m_strCharacter;
						Mecro::DrawPoint(Map::mapLog[m_temp.m_ix + i][m_temp.m_iy], m_temp.m_ix + i, m_temp.m_iy);
					}
					break;
				case C_CROSS1:
					for (int i = 1; i <= m_count; i++)
					{
						Map::mapLog[m_temp.m_ix + i][m_temp.m_iy - i] = m_strCharacter;
						Mecro::DrawPoint(Map::mapLog[m_temp.m_ix + i][m_temp.m_iy - i], m_temp.m_ix + i, m_temp.m_iy - i);
					}
					break;
				case C_CROSS2:
					for (int i = 1; i <= m_count; i++)
					{
						Map::mapLog[m_temp.m_ix + i][m_temp.m_iy + i] = m_strCharacter;
						Mecro::DrawPoint(Map::mapLog[m_temp.m_ix + i][m_temp.m_iy + i], m_temp.m_ix + i, m_temp.m_iy + i);
					}
					break;
				case C_CROSS3:
					for (int i = 1; i <= m_count; i++)
					{
						Map::mapLog[m_temp.m_ix - i][m_temp.m_iy + i] = m_strCharacter;
						Mecro::DrawPoint(Map::mapLog[m_temp.m_ix - i][m_temp.m_iy + i], m_temp.m_ix - i, m_temp.m_iy + i);
					}
					break;
				case C_CROSS4:
					for (int i = 1; i <= m_count; i++)
					{
						Map::mapLog[m_temp.m_ix - i][m_temp.m_iy - i] = m_strCharacter;
						Mecro::DrawPoint(Map::mapLog[m_temp.m_ix - i][m_temp.m_iy - i], m_temp.m_ix - i, m_temp.m_iy - i);
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


void Othello_Character::WinCheck_StoneCount(int m_winType)
{
	int m_winCheck;
	int m_blackCount = 0;
	int m_whiteCount = 0;

	for (int x = 0; x < MAPMAX; x++)
	{
		for (int y = 0; y < MAPMAX; y++)
		{
			if (Map::mapLog[x][y] == "○")
				m_blackCount++;
			if (Map::mapLog[x][y] == "●")
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

		bESC =  true;
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

	//승리 출력
	if (bESC == true)
	{
		Mecro::gotoxy(MAPMAX - 4, MAPMAX / 2);
		if (m_winCheck == BLACK)
			cout <<  "Black Win";
		else
			cout <<  "White Win";
		char ch = getch();
	}

}



//-------------------------------------------

/////////////////////////////////////////////////////////////////////
void Othello_Character::ShowInfo()
{
	Mecro::DrawMidText(m_player, MAPMAX + 7, MAPMAX + 3);
}

void Othello_Character::Draw()
{
	Mecro::TextDraw(m_strCharacter, m_position.m_ix, m_position.m_iy);
}


void Othello_Character::Turn()
{
	ShowInfo();
	Draw();
	Move();
}


Othello_Character::~Othello_Character() { }