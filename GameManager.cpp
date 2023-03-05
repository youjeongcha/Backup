#include "GameManager.h"

GameManager::GameManager()
{
	m_iGame = OMOK;
	CharaterTurn = BLACK;
	m_ContinueCheck = CONTINUE; //���� ���ӿ��� �̱� ������ ������ �̾��ϱ� �Ұ�. yet�̸� ����
}

string GameManager::mapLog[MAPMAX][MAPMAX]; //static�� ������ .cpp���� �ؾ� �Ѵ�.
int GameManager::turn;


void GameManager::BoxSetting(string mapLog[][MAPMAX], int Start_x, int Start_y, int Width, int Height)
{
	for (int y = 0; y < Height; y++)
	{
		int x = 0;
		
		if (y == 0)
		{
			mapLog[y][x] = "��";
			for (x = 1; x < Width - 1; x++)
				mapLog[y][x] = "��";
			mapLog[y][x] = "��";
		}
		else if (y == Height - 1)
		{
			mapLog[y][x] = "��";
			for (x = 1; x < Width - 1; x++)
				mapLog[y][x] = "��";
			mapLog[y][x] = "��";
		}
		else
		{
			mapLog[y][x] = "��";
			for (x = 1; x < Width - 1; x++)
				mapLog[y][x] = "��";
			mapLog[y][x] = "��";
		}
	}
	return;
}


//----------------------------------------------------------------


void GameManager::Menu()
{
	int iSelect;
	int m_menuLine;

	while (true)
	{
		m_menuLine = 8;

		Setting();
		DrawManager::BoxDraw(m_mapSize.m_iWidth, m_mapSize.m_iHeight);

		switch (m_iGame)
		{
		case OMOK:
			DrawManager::DrawMidText("�� �� �� ��", MAPMAX, 6);
			break;
		case OTHELLO:
			DrawManager::DrawMidText("�� �� �� �� ��", MAPMAX, 6);
			break;
		}


		//-------�̾��ϱ� ������ �ִ� ���

		ifstream loadMap;
		loadMap.open("SaveMap.txt");

		ifstream loadOption;
		loadOption.open("SaveOption.txt");
		if (loadOption.is_open())
		{
			int iTmp;

			/*���� ���� ���� �ʴ´�.
				������ ���� ����� ���� ������ ������.
				Menu���� ���� m_iGmae�� �޾ƿ��� ������.
				���� ������ �����ϴ��� �ҿ��� ��������.*/
			loadOption >> iTmp;
			//m_iGame = iTmp;

			//���� ���ӿ��� �¸��� ������ ������ �̾��ϱ� �̿� �Ұ����ϰ�
			loadOption >> iTmp;
			m_ContinueCheck = iTmp;

			loadOption.close();
		}

		if (loadMap.is_open() && m_ContinueCheck != NEW)
		{
			DrawManager::DrawMidText("1.���� ����", MAPMAX, m_menuLine);
			DrawManager::DrawMidText("2.�̾� �ϱ�", MAPMAX, m_menuLine += 2);
			DrawManager::DrawMidText("3.���� ����", MAPMAX, m_menuLine += 2);
			DrawManager::DrawMidText("4.���� ����", MAPMAX, m_menuLine += 2);
			DrawManager::DrawMidText("��������������������", MAPMAX, m_menuLine += 2);
			DrawManager::DrawMidText("��                ��", MAPMAX, m_menuLine += 1);
			DrawManager::DrawMidText("��������������������", MAPMAX, m_menuLine += 1);
			DrawManager::gotoxy(MAPMAX, m_menuLine - 1);
			cin >> iSelect;


			switch (iSelect)
			{
			case 1:
				Play(NEW);
				break;
			case 2://�̾��ϱ�
			{
				//�� �̾��ϱ�
				int x = 0, y = 0;
				string tmp;

				while (!loadMap.eof())
				{
					loadMap >> tmp;
					mapLog[y][x] = tmp;

					if (x == MAPMAX - 1)
					{
						y++;
						x = 0;
					}
					else
					{
						x++;
					}
				}

				//�ɼ� ��������
				ifstream loadOption;
				loadOption.open("SaveOption.txt");
				if (loadOption.is_open())
				{
					int iTmp;

					//���� ����
					loadOption >> iTmp;
					m_iGame = iTmp;

					//���� ���ӿ��� �¸��� ������ ������ �̾��ϱ� �̿� �Ұ����ϰ�
					loadOption >> iTmp;
					m_ContinueCheck = iTmp;

					//CharaterTurn �÷��̾� ��
					loadOption >> iTmp;
					CharaterTurn = iTmp;

					//turn ��
					loadOption >> iTmp;
					turn = iTmp;
					//�ݵ�� �ʿ��Ѱ�? //lastStone�� m_position�� �����鼭 �ʿ������ �ڵ�
					//m_BlackPlayer.Set_bContinueCursor(true);//ù��° Ŀ�� ��ġ ��� ��
					//m_WhitePlayer.Set_bContinueCursor(true);

					if (m_iGame == OMOK)
					{
						//�� ������ Ƚ��
						loadOption >> iTmp;
						m_BlackPlayer.Set_backCount(iTmp);
						loadOption >> iTmp;
						m_WhitePlayer.Set_backCount(iTmp);


						//�� ����
						Position Position_temp;
						stack <Position> Stack_Temp;

						int oneOff = 1;
						bool backCheck = false;
						int iTmp_CharaterTurn = CharaterTurn; //0(B) �Ǵ� 1(W)


						//stack <Position> m_BlackTemp;
						//stack <Position> m_WhiteTemp;

						////lifstream���� ����
						//ContinueLoad(loadOption, iTmp, m_BlackTemp);

						while (!loadOption.eof())//���� ���� �����ߴ��� Ȯ��
						{//���Ͽ��� ���ؿ� ������ �޴´�

							loadOption >> iTmp;
							Position_temp.m_ix = iTmp;
							loadOption >> iTmp;
							Position_temp.m_iy = iTmp;

							//���� �� ó���� ���� �� �� �ֱٿ� �� ��(�ι���)
							//������ static���� ���� �̻� �ʿ��ϴٰ� �Ǵ�
							if ((oneOff == 1) || (oneOff == 2))
							{

								if (GameManager::mapLog[Position_temp.m_iy][Position_temp.m_ix] == "��")
									backCheck = true;
								//���Ͽ� ���������� ����� ���� ���� �÷��̾ �ƴϴ�. (�ݴ�)
								//������ �����⸦ �ϰ� �������� ��� ���� �÷��̾�.

								if (backCheck == true)
								{
									if (iTmp_CharaterTurn == BLACK)//������ ǥ�õ� �� ��� �Ѵ�
									{
										m_BlackPlayer.Set_lastStone(Position_temp);
										iTmp_CharaterTurn++;
									}
									else if (iTmp_CharaterTurn == WHITE)
									{
										m_WhitePlayer.Set_lastStone(Position_temp);
										iTmp_CharaterTurn--;
									}
								}
								else
								{
									if (iTmp_CharaterTurn == BLACK)//������ ǥ�õ� �� ��� �Ѵ�
									{
										m_WhitePlayer.Set_lastStone(Position_temp);
										iTmp_CharaterTurn++;
									}
									else if (iTmp_CharaterTurn == WHITE)
									{
										m_BlackPlayer.Set_lastStone(Position_temp);
										iTmp_CharaterTurn--;
									}
								}
							}
							oneOff++;

							Stack_Temp.push(Position_temp);
						}
						while (!Stack_Temp.empty())
						{//�ӽ� ���ؿ���. ���� �̿��ϴ� ���ÿ� ����. //�״�� ����ϸ� ���� ���� ������

							Player::stoneLog.push(Stack_Temp.top());
							Stack_Temp.pop();
						}
					}

					loadOption.close();

					//while (true)
					//{//���Ͽ��� �ӽ� ���ÿ� ������ �޴´�
					//	loadOption >> iTmp;
					//	m_temp.m_ix = iTmp;
					//	if (m_temp.m_ix != -1)
					//	{
					//		loadOption >> iTmp;
					//		m_temp.m_iy = iTmp;
					//	}
					//	if (m_temp.m_ix != -1 && m_temp.m_iy != -1)
					//		m_BlackTemp.push(m_temp);
					//	else
					//		break;
					//}
					//while (true)
					//{
					//	loadOption >> iTmp;
					//	m_temp.m_ix = iTmp;
					//	if (m_temp.m_ix != -1)
					//	{
					//		loadOption >> iTmp;
					//		m_temp.m_iy = iTmp;
					//	}
					//	if (m_temp.m_ix != -1 && m_temp.m_iy != -1)
					//		m_WhiteTemp.push(m_temp);
					//	else
					//		break;
					//}
					//while ((!m_BlackTemp.empty()) || (!m_WhiteTemp.empty()))
					//{//�ӽ� ���ؿ���. ���� �̿��ϴ� ���ÿ� ����.
					//	
					//	if (!m_BlackTemp.empty())
					//	{
					//		m_BlackPlayer.Set_backXY(m_BlackTemp.top());
					//		m_BlackTemp.pop();
					//	}
					//	if (!m_WhiteTemp.empty())
					//	{
					//		m_WhitePlayer.Set_backXY(m_WhiteTemp.top());
					//		m_WhiteTemp.pop();
					//	}
					//}
				}
				Play(CONTINUE);
				break;
			}
			case 3:
				if (m_iGame == OMOK)
					m_iGame = OTHELLO;
				else
					m_iGame = OMOK;
				break;
			case 4:
				return;
			}
		}
		else
		{
			DrawManager::DrawMidText("1.���� ����", MAPMAX, m_menuLine);
			DrawManager::DrawMidText("2.���� ����", MAPMAX, m_menuLine += 2);
			DrawManager::DrawMidText("3.���� ����", MAPMAX, m_menuLine += 2);
			DrawManager::DrawMidText("��������������������", MAPMAX, m_menuLine += 2);
			DrawManager::DrawMidText("��                ��", MAPMAX, m_menuLine += 1);
			DrawManager::DrawMidText("��������������������", MAPMAX, m_menuLine += 1);
			DrawManager::gotoxy(MAPMAX, m_menuLine - 1);
			cin >> iSelect;


			switch (iSelect)
			{
			case 1:
				m_ContinueCheck = CONTINUE;
				Play(NEW);
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
}

//-------------------------------------------------------------------


void GameManager::Play(int ContinueCheck)
{
	bool ESC_Check;

	if (ContinueCheck == CONTINUE)
	{//�̾��ϱ�. ���� ������ ������ �ޱ�
		for (int y = 0; y < MAPMAX; y++)
		{
			DrawManager::gotoxy(0, 0 + y);
			for (int x = 0; x < MAPMAX; x++)
				cout << mapLog[y][x];
		}
	}
	else
	{
		CharaterTurn = BLACK;
		turn = 1;
		DrawManager::BoxDraw(m_mapSize.m_iWidth, m_mapSize.m_iHeight);
	}
	ShowInfo();

	//ĳ���� �����ְ�
	m_BlackPlayer.SetCharater("��", "��", "Black", ContinueCheck); //"��" define���� ������ ����
	m_WhitePlayer.SetCharater("��", "��", "White", ContinueCheck);

	if (m_iGame == OMOK)
	{
		if (ContinueCheck == NEW)
		{
			//2ȸ�� �̻� �÷��� �� - ���� �ʱ�ȭ
			Reset_stoneLog();
			/*m_WhitePlayer.Reset_m_backXY();
			m_BlackPlayer.Reset_m_backXY();*/

			//2ȸ�� �̻� �÷��� > ������ ��û : �⺻ false�� ����
			//������ ���·� ���� > bool�� ��� ture�� �����ִ�.
			//�̾��ϱ� > ���� �ʱ�ȭ X
			m_BlackPlayer.SetBack(false);
			m_WhitePlayer.SetBack(false);
		}
	}

	////2ȸ�� �̻� �÷��� �� - ESC �ʱ�ȭ
	//m_WhitePlayer.SetESC(false);
	//m_BlackPlayer.SetESC(false);

	while (true)
	{
		DrawManager::gotoxy(MAPMAX + 2, MAPMAX + 4);
		cout << turn;

		if (CharaterTurn == BLACK)
		{//�ڵ� �ߺ�
			CharaterTurn = WHITE;
			ESC_Check = PlayerTurn(&m_BlackPlayer, &m_WhitePlayer, BLACK, ContinueCheck); //�������� > ��������
		}
		else if (CharaterTurn == WHITE)
		{
			CharaterTurn = BLACK;
			ESC_Check = PlayerTurn(&m_WhitePlayer, &m_BlackPlayer, WHITE, ContinueCheck);
		}
		turn++;

		if (ESC_Check == true)
		{//------�̾��ϱ� ����

			//�� ����
			ofstream saveMap;
			saveMap.open("SaveMap.txt");
			if (saveMap.is_open())
			{
				for (int y = 0; y < MAPMAX; y++)
				{
					for (int x = 0; x < MAPMAX; x++)
						saveMap << mapLog[y][x] << " ";
					saveMap << endl;
				}
				saveMap.close();
			}

			//�ɼ� ����
			ofstream saveOption;
			saveOption.open("SaveOption.txt");
			if (saveOption.is_open())
			{
				//���� ����
				saveOption << m_iGame << endl;

				//���� ���ӿ��� �¸��� ������ ������ �̾��ϱ� �̿� �Ұ����ϰ�
				saveOption << m_ContinueCheck << endl;

				//CharaterTurn �÷��̾� ��
				if (turn % 2 == BLACK) //BLACK�� 0���� �����Ǿ� ����
					saveOption << BLACK << endl;
				else
					saveOption << WHITE << endl;

				//turn ��
				saveOption << turn - 1 << endl;

				if (m_iGame == OMOK)
				{
					//������ ��
					saveOption << m_BlackPlayer.Get_backCount() << endl;
					saveOption << m_WhitePlayer.Get_backCount() << endl << endl;

					//�� ����
					Position m_temp;

					while (!Player::stoneLog.empty())
					{
						m_temp = Player::stoneLog.top();
						saveOption << m_temp.m_ix << " " << m_temp.m_iy << " ";

						Player::stoneLog.pop();
					}
				}

				saveOption.close();
			}

			return;
		}
	}
}

bool GameManager::PlayerTurn(Player* m_NowTurn_Player, Player* m_NextTurn_Player, CHARATER player, int ContinueCheck)
{
	switch ((DIRECTION)m_NowTurn_Player->Turn(m_iGame, ContinueCheck)) //���� ����
	{
	case BACK:
		//������ ��û Ȯ��
		if (m_iGame == OMOK &&
			(m_NowTurn_Player->GetBack() == true))
		{
			//black���� ������ ��û�� �޾� white���� ������ ���
			m_NextTurn_Player->SetBack(true);
			m_NowTurn_Player->SetBack(false);

			//m_turn�� 10�� ���� ��� �����ڸ��� �������� �ʾƼ�
			DrawManager::gotoxy(MAPMAX + 2, MAPMAX + 4);
			cout << "       ";
			turn -= 2;
		}
		return false;
	case ENTER:
		return false;
	case ESC:
		DrawManager::ErasePoint(0, MAPMAX); //�ϴ� ����â ����
		return true;
	case WIN:
		DrawManager::gotoxy(MAPMAX - 4, MAPMAX / 2);
		if (player == BLACK)
			cout << "Black Win";
		else
			cout << "White Win";

		char ch = getch();
		DrawManager::ErasePoint(0, MAPMAX); //�ϴ� ����â ����

		//�¸� ���
		m_ContinueCheck = NEW;
		return true;
	}
}

void GameManager::ShowInfo()
{
	DrawManager::DrawMidText("====����Ű====", MAPMAX, MAPMAX);
	DrawManager::DrawMidText("�̵� : A,S,W,D  ������ : ENTER", MAPMAX, MAPMAX + 1);

	if (m_iGame == OMOK)
	{
		DrawManager::DrawMidText("������ : N  ���� : ESC", MAPMAX, MAPMAX + 2);
		DrawManager::DrawMidText("Player Name : ", 1, MAPMAX + 3);
		DrawManager::DrawMidText("������ : ", MAPMAX + 11, MAPMAX + 3);
		DrawManager::DrawMidText("Turn : ", MAPMAX - 2, MAPMAX + 4);
	}
	else
	{
		DrawManager::DrawMidText("���� : ESC", MAPMAX, MAPMAX + 2);
		DrawManager::DrawMidText("Player Name : ", MAPMAX - 2, MAPMAX + 3);
		DrawManager::DrawMidText("Turn : ", MAPMAX - 2, MAPMAX + 4);
	}
}


GameManager::~GameManager() { }
