#include "Othello_Character.h"
#include "Map.h"//���� ��Ŭ��� �ϴ°� .cpp�� �̴ϱ� ������ ����


Othello_Character::Othello_Character()
{
	bMoveStatus = false;
}


void Othello_Character::Move()
{
	while (true)
	{
		char ch = getch();
		Position prevPosition = m_position;//�߿�

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
			if ((Map::mapLog[m_position.m_ix / 2][m_position.m_iy] == "��") ||
				(Map::mapLog[m_position.m_ix / 2][m_position.m_iy] == "��"))
			{
				bMoveStatus = false;
			}
			else
			{
				bMoveStatus = true;

				//ĳ����(�ٵϵ�)�� �ʿ� ���
				Map::mapLog[m_position.m_ix / 2][m_position.m_iy] = m_strCharacter;


				//�� ���ܿ� �ٸ� �� �ٵ����� ������ �ٵϵ� ����
				Position m_CheckCount;
				m_CheckCount.m_ix = m_position.m_ix / 2;
				m_CheckCount.m_iy = m_position.m_iy;

				StoneChange(m_CheckCount, 0, -1, 0, 1, C_UP, C_DOWN); //����
				StoneChange(m_CheckCount, -1, 0, 1, 0, C_LEFT, C_RIGHT); //�¿�
				StoneChange(m_CheckCount, 1, -1, 1, 1, C_CROSS1, C_CROSS2); //��1,3
				StoneChange(m_CheckCount, -1, 1, -1, -1, C_CROSS3, C_CROSS4); //��2,4


				//�¸� üũ
				
				if (m_turn == MAXSTONE)
				{//1.�ٵ����� �� ä������ > �� 400�� �Ǹ� �˻�
					WinCheck_StoneCount(MAXSTONE);
				}
				else if (m_turn >= OTHELLO_WINJUGE)
				{//2.�ٵϵ��� ȭ��� �Ѱ��� ���� ������ > 10�� �̻����
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
		{//ĳ���� �̵��ϰ� ���� �ڸ� ó��
			//switch (ch)
			//{
			//case DIRECTION::LEFT:
			//case DIRECTION::RIGHT:
			//case DIRECTION::UP:
			//case DIRECTION::DOWN:
			//	Mecro::gotoxy(prevPosition.m_ix, prevPosition.m_iy);
			//	break;
			//}
			//Map map; //static ���� ���Ұ�
			Mecro::gotoxy(prevPosition.m_ix, prevPosition.m_iy);//�����ذ� ���� �߰�
			cout << Map::mapLog[prevPosition.m_ix / 2][prevPosition.m_iy];//����
			Draw();
		}
	}
}

/////////////////////////////////////////////////////////////////////
void Othello_Character::StoneChange(Position m_CheckCount, int m_X1, int m_Y1, int m_X2, int m_Y2, int m_direction1, int m_direction2)
{//�ٵϵ� ���� ī��Ʈ
	StoneChange(m_CheckCount, m_X1, m_Y1, m_direction1);
	StoneChange(m_CheckCount, m_X2, m_Y2, m_direction2);
}

void Othello_Character::StoneChange(Position m_CheckCount, int m_checkX, int m_checkY, int m_direction)
{//�ٵϵ� �Է¹޴� ������� ��ǥ �Ǵ��ϰ�. �ش� ���⿡ �� ������ count++ 
	int m_count = 0; //��ȯ�ؾ� �� �� ���� �Ǵ�
	Position m_temp;

	m_temp.m_ix = m_CheckCount.m_ix;
	m_temp.m_iy = m_CheckCount.m_iy;

	while (true)
	{
		//������ �� �ݹ� �Ϸķ� ��ġ�ϸ� �������� �� ���� ä�� ������ �� ���ع����� ��Ȳ ���� (��ǥ�� -1�� �Ǹ� �߻�)
		if (m_Compare_strCharacter == Map::mapLog[m_CheckCount.m_ix + m_checkX][m_CheckCount.m_iy + m_checkY] &&
			((m_CheckCount.m_ix + m_checkX) >= 0) && ((m_CheckCount.m_iy + m_checkY) >= 0) &&
			((m_CheckCount.m_ix + m_checkX) < 20) && ((m_CheckCount.m_iy + m_checkY) < 20))
		{//���� ���� ���� ���� üũ�ϴ� ���⿡ �ִ� ���� �ٸ� ������ Ȯ��
			//(��ǥ�� -1�� �Ǵ� ��� ����) (�� ǥ���Ҷ��� m_CheckCount�� �޶� �����ϴµ� �ʼ��� �ƴ�)
		 // Map::mapLog[m_CheckCount.m_ix + m_checkX][m_CheckCount.m_iy + m_checkY] ����� �� ��ǥ

			m_CheckCount.m_ix += m_checkX;
			m_CheckCount.m_iy += m_checkY;

			m_count++;

			if (m_strCharacter == Map::mapLog[m_CheckCount.m_ix + m_checkX][m_CheckCount.m_iy + m_checkY] &&
				((m_CheckCount.m_ix + m_checkX) >= 0) && ((m_CheckCount.m_iy + m_checkY) >= 0) && 
				((m_CheckCount.m_ix + m_checkX) < 20) && ((m_CheckCount.m_iy + m_checkY) < 20))
			{//������ ���� �Ͽ� �� �ٵϵ��� ���� �� ������ ������ �� ��ȯ
				//(��ǥ�� -1�� �Ǵ� ��� ����) (�ʼ�)

				switch (m_direction)
				{//count �̿�
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
			if (Map::mapLog[x][y] == "��")
				m_blackCount++;
			if (Map::mapLog[x][y] == "��")
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

		bESC =  true;
	}
	else if ((m_winType == OTHELLO_WINJUGE) && (m_blackCount == 0 || m_whiteCount == 0))
	{
		//ȭ�鿡 �� ���� �ٵϵ��� ���� ���
		if (m_blackCount == 0)
			m_winCheck = WHITE;
		else if (m_whiteCount == 0)
			m_winCheck = BLACK;

		bESC = true;
	}

	//�¸� ���
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