#include "Omok_Character.h"
#include "Map.h"//���� ��Ŭ��� �ϴ°� .cpp�� �ƴϱ� ������ ����


Omok_Character::Omok_Character()
{
	bMoveStatus = false;
	bBackCheck = false;
}


void Omok_Character::Move()
{
	while (true)
	{
		char ch = getch();
		Position prevPosition = m_position;//�߿� //�̹� �Ͽ��� ���� �� ó�� ��ġ�� �ڸ�.(������ �ڸ� �����Ҷ� �ַ� �̿��Ѵ�.)
		switch (ch)
		{
		case DIRECTION::LEFT:
			if (m_position.m_ix - 1 >= m_mapSize.m_iLeft) //���ڿ� 2ĭ ���
			{
				m_position.m_ix-=2;
				bMoveStatus = true;
			}
			break;
		case DIRECTION::RIGHT:
			if (m_position.m_ix + 1 < m_mapSize.m_iRight - 2)
			{
				m_position.m_ix+=2;
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
				(Map::mapLog[m_position.m_ix / 2][m_position.m_iy] == "��") ||
				(Map::mapLog[m_position.m_ix / 2][m_position.m_iy] == "��"))
			{
				bMoveStatus = false;
			}
			else
			{
				bMoveStatus = true;
				Position m_temp;

				//ĳ����(�ٵϵ�)�� �ʿ� ���
				Map::mapLog[m_position.m_ix / 2][m_position.m_iy] = m_strCharacter;

				/////////////////////////////////////////////////////////////////////
				//�ش� �Ͽ� ������ �� �Ǿ��ִ� ��Ȳ�̸� ����
				if (bBackCheck == true)
				{
					BackMapDraw(&m_temp);
					bBackCheck = false;
				}

				/////////////////////////////////////////////////////////////////////
				//������ �� ��ǥ Ȯ��(���2)
				m_temp.m_ix = m_position.m_ix / 2;
				m_temp.m_iy = m_position.m_iy;
				m_backXY.push(m_temp);

				/////////////////////////////////////////////////////////////////////
				//���� Ȯ�� - ����
				if (m_turn >= OMOK_WINJUGE)
				{
					//bool m_bCheck;
					Position m_CheckCount;
					m_CheckCount.m_ix = m_position.m_ix / 2;
					m_CheckCount.m_iy = m_position.m_iy;

					if (WinCheck(m_CheckCount, 0, -1, 0, 1) == true) //����
						bESC = true;
					if (WinCheck(m_CheckCount, -1, 0, 1, 0) == true) //�¿�
						bESC = true;
					if (WinCheck(m_CheckCount, 1, -1, -1, -1) == true) //��1,3
						bESC = true;
					if (WinCheck(m_CheckCount, 1, 1, -1, 1) == true) //��2,4
						bESC = true;

					if (bESC == true)
					{
						Mecro::gotoxy(MAPMAX - 4, MAPMAX / 2);
						cout << m_player << " Win";
						char ch = getch();
					}
				}
				return;
			}
			break;
			/////////////////////////////////////////////////////////////////////
		case DIRECTION::BACK:
			if ((m_backCount != 0) && (m_turn > 1))
			{
				Position m_temp;
				//���� �ΰ� �ִ� �� ����(������ �� ���� ��)
				Mecro::gotoxy(m_position.m_ix, m_position.m_iy);
				cout << Map::mapLog[prevPosition.m_ix / 2][prevPosition.m_iy];

				//�ش� �Ͽ� ������ �� �Ǿ��ִ� ��Ȳ�̸� ���� //���� �� �� - ���� ������
				if (bBackCheck == true)
				{
					BackMapDraw(&m_temp);
				}

				//���� �� ������ ��û
				bBackCheck = true;
		
				m_backCount--;
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
			//case DIRECTION::BACK:
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
bool Omok_Character::WinCheck(Position m_CheckCount, int m_X1, int m_Y1, int m_X2, int m_Y2)
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
int Omok_Character::WinCheck(Position m_CheckCount, int m_count, int m_checkX, int m_checkY)
{//�ٵϵ� �Է¹޴� ������� ��ǥ �Ǵ��ϰ�. �ش� ���⿡ �� ������ count++ 
	for (int i = 0; i < 5; i++)
	{
		if (Map::mapLog[m_CheckCount.m_ix][m_CheckCount.m_iy] == Map::mapLog[m_CheckCount.m_ix + m_checkX][m_CheckCount.m_iy + m_checkY])
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

/////////////////////////////////////////////////////////////////////
void Omok_Character::BackMapDraw(Position* m_temp)
{
	*m_temp = m_backXY.top();

	Map::mapLog[m_temp->m_ix][m_temp->m_iy] = MapDraw(m_temp->m_ix, m_temp->m_iy);
	Mecro::gotoxy(m_temp->m_ix * 2, m_temp->m_iy);
	cout << Map::mapLog[m_temp->m_ix][m_temp->m_iy];

	m_backXY.pop();
}

/////////////////////////////////////////////////////////////////////
string Omok_Character::MapDraw(int m_x, int m_y)
{

	if (m_y == 0)
		return MapDrawPart(m_x, "��", "��", "��");
	else if (m_y == MAPMAX - 1)
		return MapDrawPart(m_x, "��", "��", "��");
	else
		return MapDrawPart(m_x, "��", "��", "��");
}

/////////////////////////////////////////////////////////////////////
string Omok_Character::MapDrawPart(int m_x, string part1, string part2, string part3)
{
	if (m_x == 0)
		return part1;
	else if (m_x == MAPMAX - 1)
		return part2;
	else
		return part3;
}


//-------------------------------------------

/////////////////////////////////////////////////////////////////////
void Omok_Character::ShowInfo()
{
	Mecro::DrawMidText(m_player, 17, MAPMAX + 3);
	Mecro::gotoxy(MAPMAX + 16, MAPMAX + 3);
	cout << m_backCount;
}

void Omok_Character::Draw()
{
	Mecro::TextDraw(m_strCharacter, m_position.m_ix, m_position.m_iy);
}


void Omok_Character::Turn()
{
	ShowInfo();
	Draw();
	
	/////////////////////////////////////////////////////////////////////
	//m_bBackCheck���� �� �ٵϵ��� �Ͽ��� ������ ��û���� ���(true) 
	//������ ��û�� �� ǥ�� ��
	if ((bBackCheck == true) && (m_turn >= 1))
	{//������ ��û�� ��� && turn 1 ������ ������ ����,ǥ��
		Position m_temp;
		m_temp = m_backXY.top();

		Map::mapLog[m_temp.m_ix][m_temp.m_iy] = "��";
		Mecro::gotoxy(m_temp.m_ix * 2, m_temp.m_iy);
		cout << Map::Map::mapLog[m_temp.m_ix][m_temp.m_iy];
	}

	Move();
}


Omok_Character::~Omok_Character() { }
