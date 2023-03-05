#include "Player.h"
#include "GameManager.h"

Player::Player()
{
	bBackCheck = false;
}

stack <Position> Player::stoneLog;

int Player::Move(int _iGame)
{
	bool bMoveStatus = false;

	while (true)
	{
		char ch = getch();

		Position prevPosition = m_position;//�߿� //�̹� �Ͽ��� ���� �� ó�� ��ġ�� �ڸ�.(������ �ڸ� �����Ҷ� �ַ� �̿��Ѵ�.)


		switch (ch)
		{
		case DIRECTION::LEFT:
			if (m_position.m_ix - 1 >= m_mapSize.m_iLeft) //���ڿ� 2ĭ ���
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
			if ((GameManager::mapLog[m_position.m_iy][m_position.m_ix / 2] == "��") ||
				(GameManager::mapLog[m_position.m_iy][m_position.m_ix / 2] == "��") ||
				(GameManager::mapLog[m_position.m_iy][m_position.m_ix / 2] == "��"))
			{
				bMoveStatus = false;
			}
			else
			{
				bMoveStatus = true;

				//ĳ����(�ٵϵ�)�� �ʿ� ���
				GameManager::mapLog[m_position.m_iy][m_position.m_ix / 2] = m_strCharacter;

				if (_iGame == OMOK)
				{
					Position m_temp;

					//�ش� �Ͽ� ������ �� �Ǿ��ִ� ��Ȳ�̸� ����
					if (bBackCheck == true)
					{
						m_temp = stoneLog.top();
						BackMapDraw(&m_temp);
						//BackMapDraw(&m_lastStone);
						bBackCheck = false;
						stoneLog.pop();
					}

					//�ٵϵ� �α� Ȯ��(���2)
					m_temp.m_ix = m_position.m_ix / 2;
					m_temp.m_iy = m_position.m_iy;
					stoneLog.push(m_temp);
					//������ �� ��ǥ Ȯ��(���3)
					m_lastStone = m_temp;

					//���� Ȯ�� - ����
					if (GameManager::turn >= OMOK_WINJUGE) //����
					{
						//bool m_bCheck;
						Position m_CheckCount;
						m_CheckCount.m_ix = m_position.m_ix / 2;
						m_CheckCount.m_iy = m_position.m_iy;

						if (WinCheck(m_CheckCount, 0, -1, 0, 1) == true) //����
							return WIN;
						if (WinCheck(m_CheckCount, -1, 0, 1, 0) == true) //�¿�
							return WIN;
						if (WinCheck(m_CheckCount, 1, -1, -1, -1) == true) //��1,3
							return WIN;
						if (WinCheck(m_CheckCount, 1, 1, -1, 1) == true) //��2,4
							return WIN;
					}
				}
				else if (_iGame == OTHELLO)
				{
					//�� ���ܿ� �ٸ� �� �ٵ����� ������ �ٵϵ� ����
					Position m_CheckCount;
					m_CheckCount.m_ix = m_position.m_ix / 2;
					m_CheckCount.m_iy = m_position.m_iy;

					StoneChange(m_CheckCount, 0, -1, 0, 1, C_UP, C_DOWN); //����
					StoneChange(m_CheckCount, -1, 0, 1, 0, C_LEFT, C_RIGHT); //�¿�
					StoneChange(m_CheckCount, 1, -1, 1, 1, C_CROSS1, C_CROSS2); //��1,3
					StoneChange(m_CheckCount, -1, 1, -1, -1, C_CROSS3, C_CROSS4); //��2,4


					//�¸� üũ
					if (GameManager::turn == MAXSTONE)
					{//1.�ٵ����� �� ä������ > �� 400�� �Ǹ� �˻�
						if (WinCheck_StoneCount(MAXSTONE) == WIN)
							return WIN;
					}
					else if (GameManager::turn >= OTHELLO_WINJUGE)
					{//2.�ٵϵ��� ȭ��� �Ѱ��� ���� ������ > 10�� �̻����
						if (WinCheck_StoneCount(OTHELLO_WINJUGE) == WIN)
							return WIN;
					}
				}
				return ENTER;
			}
			break;
		case DIRECTION::BACK:
			if ((_iGame == OMOK) &&
				(m_backCount != 0) && (GameManager::turn > 1))
			{
				//���� �ΰ� �ִ� �� ����(������ �� ���� ��)
				DrawManager::gotoxy(m_position.m_ix, m_position.m_iy);
				cout << GameManager::mapLog[prevPosition.m_iy][prevPosition.m_ix / 2];

				if (bBackCheck == true)
				{
					Position m_temp = stoneLog.top();
					BackMapDraw(&m_temp);
					//BackMapDraw(&m_lastStone); //�������� 
					bBackCheck = false;
					stoneLog.pop();
				}

				//���� �� ������ ��û
				bBackCheck = true;

				m_backCount--;
				return BACK;
			}
			break;
		case DIRECTION::ESC:
			//bESC = true;
			return ESC;
		}
		if (bMoveStatus)
		{//ĳ���� �̵��ϰ� ���� �ڸ� ó��
			//if (_iGame == OMOK)
			//{
			//}
			DrawManager::gotoxy(prevPosition.m_ix, prevPosition.m_iy);
			cout << GameManager::mapLog[prevPosition.m_iy][prevPosition.m_ix / 2];
			Draw();
		}
	}
}

/////////////////////////////////////////////////////////////////////
bool Player::WinCheck(Position m_CheckCount, int m_X1, int m_Y1, int m_X2, int m_Y2)
{//�ٵϵ� ���� ī��Ʈ
	int m_count = 1;

	m_count = WinCheck(m_CheckCount, m_count, m_X1, m_Y1);
	m_count = WinCheck(m_CheckCount, m_count, m_X2, m_Y2);

	if (m_count == 5) //���� ����
		return true;
	else
		return false;
}

/////////////////////////////////////////////////////////////////////
int Player::WinCheck(Position m_CheckCount, int m_count, int m_checkX, int m_checkY)
{//�ٵϵ� �Է¹޴� ������� ��ǥ �Ǵ��ϰ�. �ش� ���⿡ �� ������ count++ 
	for (int i = 0; i < 5; i++)
	{
		if (GameManager::mapLog[m_CheckCount.m_iy][m_CheckCount.m_ix] == GameManager::mapLog[m_CheckCount.m_iy + m_checkY][m_CheckCount.m_ix + m_checkX])
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
{//�ٵϵ� ���� ī��Ʈ
	StoneChange(m_CheckCount, m_X1, m_Y1, m_direction1);
	StoneChange(m_CheckCount, m_X2, m_Y2, m_direction2);
}

void Player::StoneChange(Position m_CheckCount, int m_checkX, int m_checkY, int m_direction)
{//�ٵϵ� �Է¹޴� ������� ��ǥ �Ǵ��ϰ�. �ش� ���⿡ �� ������ count++ 
	int m_count = 0; //��ȯ�ؾ� �� �� ���� �Ǵ�
	Position m_temp;

	m_temp.m_ix = m_CheckCount.m_ix;
	m_temp.m_iy = m_CheckCount.m_iy;

	while (true)
	{
		//������ �� �ݹ� �Ϸķ� ��ġ�ϸ� �������� �� ���� ä�� ������ �� ���ع����� ��Ȳ ���� (��ǥ�� -1�� �Ǹ� �߻�)
		if (m_Compare_player_stone == GameManager::mapLog[m_CheckCount.m_iy + m_checkY][m_CheckCount.m_ix + m_checkX] &&
			((m_CheckCount.m_ix + m_checkX) >= 0) && ((m_CheckCount.m_iy + m_checkY) >= 0) &&
			((m_CheckCount.m_ix + m_checkX) < 20) && ((m_CheckCount.m_iy + m_checkY) < 20))
		{//���� ���� ���� ���� üũ�ϴ� ���⿡ �ִ� ���� �ٸ� ������ Ȯ��
			//(��ǥ�� -1�� �Ǵ� ��� ����) (�� ǥ���Ҷ��� m_CheckCount�� �޶� �����ϴµ� �ʼ��� �ƴ�)
		 // Map::mapLog[m_CheckCount.m_ix + m_checkX][m_CheckCount.m_iy + m_checkY] ����� �� ��ǥ

			m_CheckCount.m_ix += m_checkX;
			m_CheckCount.m_iy += m_checkY;

			m_count++;

			if (m_strCharacter == GameManager::mapLog[m_CheckCount.m_iy + m_checkY][m_CheckCount.m_ix + m_checkX] &&
				((m_CheckCount.m_ix + m_checkX) >= 0) && ((m_CheckCount.m_iy + m_checkY) >= 0) &&
				((m_CheckCount.m_ix + m_checkX) < 20) && ((m_CheckCount.m_iy + m_checkY) < 20))
			{//������ ���� �Ͽ� �� �ٵϵ��� ���� �� ������ ������ �� ��ȯ
				//(��ǥ�� -1�� �Ǵ� ��� ����) (�ʼ�)

				switch (m_direction)
				{//count �̿�
				case C_UP:
					for (int i = 1; i <= m_count; i++)
					{
						GameManager::mapLog[m_temp.m_iy - i][m_temp.m_ix] = m_strCharacter;
						DrawManager::DrawPoint(GameManager::mapLog[m_temp.m_iy - i][m_temp.m_ix], m_temp.m_ix, m_temp.m_iy - i);
					}
					break;
				case C_DOWN:
					for (int i = 1; i <= m_count; i++)
					{
						GameManager::mapLog[m_temp.m_iy + i][m_temp.m_ix] = m_strCharacter;
						DrawManager::DrawPoint(GameManager::mapLog[m_temp.m_iy + i][m_temp.m_ix], m_temp.m_ix, m_temp.m_iy + i);
					}
					break;
				case C_LEFT:
					for (int i = 1; i <= m_count; i++)
					{
						GameManager::mapLog[m_temp.m_iy][m_temp.m_ix - i] = m_strCharacter;
						DrawManager::DrawPoint(GameManager::mapLog[m_temp.m_iy][m_temp.m_ix - i], m_temp.m_ix - i, m_temp.m_iy);
					}
					break;
				case C_RIGHT:
					for (int i = 1; i <= m_count; i++)
					{
						GameManager::mapLog[m_temp.m_iy][m_temp.m_ix + i] = m_strCharacter;
						DrawManager::DrawPoint(GameManager::mapLog[m_temp.m_iy][m_temp.m_ix + i], m_temp.m_ix + i, m_temp.m_iy);
					}
					break;
				case C_CROSS1:
					for (int i = 1; i <= m_count; i++)
					{
						GameManager::mapLog[m_temp.m_iy - i][m_temp.m_ix + i] = m_strCharacter;
						DrawManager::DrawPoint(GameManager::mapLog[m_temp.m_iy - i][m_temp.m_ix + i], m_temp.m_ix + i, m_temp.m_iy - i);
					}
					break;
				case C_CROSS2:
					for (int i = 1; i <= m_count; i++)
					{
						GameManager::mapLog[m_temp.m_iy + i][m_temp.m_ix + i] = m_strCharacter;
						DrawManager::DrawPoint(GameManager::mapLog[m_temp.m_iy + i][m_temp.m_ix + i], m_temp.m_ix + i, m_temp.m_iy + i);
					}
					break;
				case C_CROSS3:
					for (int i = 1; i <= m_count; i++)
					{
						GameManager::mapLog[m_temp.m_iy + i][m_temp.m_ix - i] = m_strCharacter;
						DrawManager::DrawPoint(GameManager::mapLog[m_temp.m_iy + i][m_temp.m_ix - i], m_temp.m_ix - i, m_temp.m_iy + i);
					}
					break;
				case C_CROSS4:
					for (int i = 1; i <= m_count; i++)
					{
						GameManager::mapLog[m_temp.m_iy - i][m_temp.m_ix - i] = m_strCharacter;
						DrawManager::DrawPoint(GameManager::mapLog[m_temp.m_iy - i][m_temp.m_ix - i], m_temp.m_ix - i, m_temp.m_iy - i);
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


DIRECTION Player::WinCheck_StoneCount(int m_winType)
{
	int m_winCheck;
	int m_blackCount = 0;
	int m_whiteCount = 0;

	for (int y = 0; y < MAPMAX; y++)
	{
		for (int x = 0; x < MAPMAX; x++)
		{
			if (GameManager::mapLog[y][x] == "��")
				m_blackCount++;
			if (GameManager::mapLog[y][x] == "��")
				m_whiteCount++;
		}
	}


	if (m_winType == MAXSTONE)
	{
		//�ٵϵ� ���� ��
		if (m_blackCount > m_whiteCount)
			m_winCheck = BLACK;
		else if (m_whiteCount > m_blackCount)
			m_winCheck = WHITE;

		return WIN;
	}
	else if ((m_winType == OTHELLO_WINJUGE) && (m_blackCount == 0 || m_whiteCount == 0))
	{
		//ȭ�鿡 �� ���� �ٵϵ��� ���� ���
		if (m_blackCount == 0)
			m_winCheck = WHITE;
		else if (m_whiteCount == 0)
			m_winCheck = BLACK;

		return WIN;
	}

	return YET;
}

//-------------------------------------------

void Player::BackMapDraw(Position* m_temp)
{
	GameManager::mapLog[m_temp->m_iy][m_temp->m_ix] = DrawManager::MapDraw(m_temp->m_ix, m_temp->m_iy);
	DrawManager::gotoxy(m_temp->m_ix * 2, m_temp->m_iy);
	cout << GameManager::mapLog[m_temp->m_iy][m_temp->m_ix];
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


int Player::Turn(int _iGame, int ContinueCheck)
//int Player::Turn(int _iGame)
{
	ShowPlayerInfo(_iGame);


	if ((ContinueCheck == CONTINUE) && (_iGame == OMOK))
	{
		//m_lastStone ������ �Ҷ� �̿� //stomeLog�� �������� top ��ǥ���� ���� �����ȴ� > stack�� static���� ����߱� ����
		//�̾��ϱ� �ÿ� ù��° Ŀ�� ���� //���� �ڵ��� m_position���� �̿��ϱ� ����
		m_position.m_ix = m_lastStone.m_ix * 2;
		m_position.m_iy = m_lastStone.m_iy;


		//�̾��ϱ� �� > �÷��̾ �������� ������ ��û �� ���� Ȯ��. (������,���� ���� ������� Ȯ��)
		if (GameManager::mapLog[m_lastStone.m_iy][m_lastStone.m_ix] == "��")
			bBackCheck = true;
	}

	//m_bBackCheck���� �� �ٵϵ��� �Ͽ��� ������ ��û���� ���(true) 
	//������ ��û�� �� ǥ�� ��
	if ((_iGame == OMOK) &&
		(bBackCheck == true) && (GameManager::turn >= 1))
	{//������ ��û�� ��� && turn 1 ������ ������ ����,ǥ��
		Position m_temp;
		m_temp = stoneLog.top();

		GameManager::mapLog[m_temp.m_iy][m_temp.m_ix] = "��";
		DrawManager::gotoxy(m_temp.m_ix * 2, m_temp.m_iy);
		cout << GameManager::mapLog[m_temp.m_iy][m_temp.m_ix];
	}

	Draw();

	return Move(_iGame);
}


Player::~Player() { }
