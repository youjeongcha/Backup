#include "GameManager.h"

GameManager::GameManager()
{
	m_iGame = OMOK;
	CharaterTurn = BLACK;
	m_ContinueCheck = CONTINUE; //직전 게임에서 이긴 전적이 있으면 이어하기 불가. yet이면 가능
}

string GameManager::mapLog[MAPMAX][MAPMAX]; //static은 선언을 .cpp에서 해야 한다.
int GameManager::turn;


void GameManager::BoxSetting(string mapLog[][MAPMAX], int Start_x, int Start_y, int Width, int Height)
{
	for (int y = 0; y < Height; y++)
	{
		int x = 0;
		
		if (y == 0)
		{
			mapLog[y][x] = "┌";
			for (x = 1; x < Width - 1; x++)
				mapLog[y][x] = "┬";
			mapLog[y][x] = "┐";
		}
		else if (y == Height - 1)
		{
			mapLog[y][x] = "└";
			for (x = 1; x < Width - 1; x++)
				mapLog[y][x] = "┴";
			mapLog[y][x] = "┘";
		}
		else
		{
			mapLog[y][x] = "├";
			for (x = 1; x < Width - 1; x++)
				mapLog[y][x] = "┼";
			mapLog[y][x] = "┤";
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
			DrawManager::DrawMidText("★ 오 목 ★", MAPMAX, 6);
			break;
		case OTHELLO:
			DrawManager::DrawMidText("★ 오 델 로 ★", MAPMAX, 6);
			break;
		}


		//-------이어하기 파일이 있는 경우

		ifstream loadMap;
		loadMap.open("SaveMap.txt");

		ifstream loadOption;
		loadOption.open("SaveOption.txt");
		if (loadOption.is_open())
		{
			int iTmp;

			/*게임 종류 받지 않는다.
				무조건 파일 저장된 게임 종류가 있으면.
				Menu실행 직후 m_iGmae에 받아오기 때문에.
				게임 종류를 변경하더라도 소용이 없어진다.*/
			loadOption >> iTmp;
			//m_iGame = iTmp;

			//직전 게임에서 승리한 전적이 있으면 이어하기 이용 불가능하게
			loadOption >> iTmp;
			m_ContinueCheck = iTmp;

			loadOption.close();
		}

		if (loadMap.is_open() && m_ContinueCheck != NEW)
		{
			DrawManager::DrawMidText("1.게임 시작", MAPMAX, m_menuLine);
			DrawManager::DrawMidText("2.이어 하기", MAPMAX, m_menuLine += 2);
			DrawManager::DrawMidText("3.게임 변경", MAPMAX, m_menuLine += 2);
			DrawManager::DrawMidText("4.게임 종료", MAPMAX, m_menuLine += 2);
			DrawManager::DrawMidText("┌────────┐", MAPMAX, m_menuLine += 2);
			DrawManager::DrawMidText("│                │", MAPMAX, m_menuLine += 1);
			DrawManager::DrawMidText("└────────┘", MAPMAX, m_menuLine += 1);
			DrawManager::gotoxy(MAPMAX, m_menuLine - 1);
			cin >> iSelect;


			switch (iSelect)
			{
			case 1:
				Play(NEW);
				break;
			case 2://이어하기
			{
				//맵 이어하기
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

				//옵션 가져오기
				ifstream loadOption;
				loadOption.open("SaveOption.txt");
				if (loadOption.is_open())
				{
					int iTmp;

					//게임 종류
					loadOption >> iTmp;
					m_iGame = iTmp;

					//직전 게임에서 승리한 전적이 있으면 이어하기 이용 불가능하게
					loadOption >> iTmp;
					m_ContinueCheck = iTmp;

					//CharaterTurn 플레이어 턴
					loadOption >> iTmp;
					CharaterTurn = iTmp;

					//turn 수
					loadOption >> iTmp;
					turn = iTmp;
					//반드시 필요한가? //lastStone을 m_position에 받으면서 필요없어진 코드
					//m_BlackPlayer.Set_bContinueCursor(true);//첫번째 커서 위치 잡는 용
					//m_WhitePlayer.Set_bContinueCursor(true);

					if (m_iGame == OMOK)
					{
						//각 무르기 횟수
						loadOption >> iTmp;
						m_BlackPlayer.Set_backCount(iTmp);
						loadOption >> iTmp;
						m_WhitePlayer.Set_backCount(iTmp);


						//각 스택
						Position Position_temp;
						stack <Position> Stack_Temp;

						int oneOff = 1;
						bool backCheck = false;
						int iTmp_CharaterTurn = CharaterTurn; //0(B) 또는 1(W)


						//stack <Position> m_BlackTemp;
						//stack <Position> m_WhiteTemp;

						////lifstream으로 실패
						//ContinueLoad(loadOption, iTmp, m_BlackTemp);

						while (!loadOption.eof())//파일 끝에 도달했는지 확인
						{//파일에서 스텍에 데이터 받는다

							loadOption >> iTmp;
							Position_temp.m_ix = iTmp;
							loadOption >> iTmp;
							Position_temp.m_iy = iTmp;

							//파일 맨 처음에 저장 된 게 최근에 둔 돌(두번만)
							//스택을 static으로 쓰는 이상 필요하다고 판단
							if ((oneOff == 1) || (oneOff == 2))
							{

								if (GameManager::mapLog[Position_temp.m_iy][Position_temp.m_ix] == "※")
									backCheck = true;
								//파일에 마지막으로 저장된 돌은 현재 플레이어가 아니다. (반대)
								//하지만 무르기를 하고 저장했을 경우 현재 플레이어.

								if (backCheck == true)
								{
									if (iTmp_CharaterTurn == BLACK)//무르기 표시도 돌 취급 한다
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
									if (iTmp_CharaterTurn == BLACK)//무르기 표시도 돌 취급 한다
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
						{//임시 스텍에서. 기존 이용하는 스택에 전달. //그대로 사용하면 스택 순서 뒤집힘

							Player::stoneLog.push(Stack_Temp.top());
							Stack_Temp.pop();
						}
					}

					loadOption.close();

					//while (true)
					//{//파일에서 임시 스택에 데이터 받는다
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
					//{//임시 스텍에서. 기존 이용하는 스택에 전달.
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
			DrawManager::DrawMidText("1.게임 시작", MAPMAX, m_menuLine);
			DrawManager::DrawMidText("2.게임 변경", MAPMAX, m_menuLine += 2);
			DrawManager::DrawMidText("3.게임 종료", MAPMAX, m_menuLine += 2);
			DrawManager::DrawMidText("┌────────┐", MAPMAX, m_menuLine += 2);
			DrawManager::DrawMidText("│                │", MAPMAX, m_menuLine += 1);
			DrawManager::DrawMidText("└────────┘", MAPMAX, m_menuLine += 1);
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
	{//이어하기. 이전 데이터 스텍이 받기
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

	//캐릭터 정해주고
	m_BlackPlayer.SetCharater("○", "●", "Black", ContinueCheck); //"○" define으로 설정도 가능
	m_WhitePlayer.SetCharater("●", "○", "White", ContinueCheck);

	if (m_iGame == OMOK)
	{
		if (ContinueCheck == NEW)
		{
			//2회차 이상 플레이 시 - 스택 초기화
			Reset_stoneLog();
			/*m_WhitePlayer.Reset_m_backXY();
			m_BlackPlayer.Reset_m_backXY();*/

			//2회차 이상 플레이 > 무르기 신청 : 기본 false로 유지
			//무르기 상태로 종료 > bool이 계속 ture로 남아있다.
			//이어하기 > 스택 초기화 X
			m_BlackPlayer.SetBack(false);
			m_WhitePlayer.SetBack(false);
		}
	}

	////2회차 이상 플레이 시 - ESC 초기화
	//m_WhitePlayer.SetESC(false);
	//m_BlackPlayer.SetESC(false);

	while (true)
	{
		DrawManager::gotoxy(MAPMAX + 2, MAPMAX + 4);
		cout << turn;

		if (CharaterTurn == BLACK)
		{//코드 중복
			CharaterTurn = WHITE;
			ESC_Check = PlayerTurn(&m_BlackPlayer, &m_WhitePlayer, BLACK, ContinueCheck); //깊은복사 > 얕은복사
		}
		else if (CharaterTurn == WHITE)
		{
			CharaterTurn = BLACK;
			ESC_Check = PlayerTurn(&m_WhitePlayer, &m_BlackPlayer, WHITE, ContinueCheck);
		}
		turn++;

		if (ESC_Check == true)
		{//------이어하기 저장

			//맵 저장
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

			//옵션 저장
			ofstream saveOption;
			saveOption.open("SaveOption.txt");
			if (saveOption.is_open())
			{
				//게임 종류
				saveOption << m_iGame << endl;

				//직전 게임에서 승리한 전적이 있으면 이어하기 이용 불가능하게
				saveOption << m_ContinueCheck << endl;

				//CharaterTurn 플레이어 턴
				if (turn % 2 == BLACK) //BLACK이 0으로 설정되어 있음
					saveOption << BLACK << endl;
				else
					saveOption << WHITE << endl;

				//turn 수
				saveOption << turn - 1 << endl;

				if (m_iGame == OMOK)
				{
					//무르기 수
					saveOption << m_BlackPlayer.Get_backCount() << endl;
					saveOption << m_WhitePlayer.Get_backCount() << endl << endl;

					//각 스택
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
	switch ((DIRECTION)m_NowTurn_Player->Turn(m_iGame, ContinueCheck)) //게임 진행
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
			turn -= 2;
		}
		return false;
	case ENTER:
		return false;
	case ESC:
		DrawManager::ErasePoint(0, MAPMAX); //하단 정보창 지움
		return true;
	case WIN:
		DrawManager::gotoxy(MAPMAX - 4, MAPMAX / 2);
		if (player == BLACK)
			cout << "Black Win";
		else
			cout << "White Win";

		char ch = getch();
		DrawManager::ErasePoint(0, MAPMAX); //하단 정보창 지움

		//승리 기록
		m_ContinueCheck = NEW;
		return true;
	}
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
