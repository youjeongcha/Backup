#include "Interface.h"

void Interface::EnterNext()
{
	while (true)
	{
		if (getch() == INPUTBOX_ENTER)
			break;
	}
}
//★ const 사용할때는 가져올 정보들이 const로 선언이 되어있어야 한다.(완)
int Interface::StartInterface(const Player& player)
{ //게임 시작 화면
	MapInterface();
	PlayerInfoInterface(player); //플레이어 정보 인터페이스 출력
	
	SKY_BLUE
	MapDraw::DrawMidText("§ § 베 네 치 아 § §", MAPSIZE_END_X, STARTMENU_Y_GAMENAME);
	MapDraw::DrawMidText("1.Game Start", MAPSIZE_END_X, STARTMENU_Y_START);
	MapDraw::DrawMidText("2.Rank", MAPSIZE_END_X, STARTMENU_Y_RANK);
	MapDraw::DrawMidText("3,Exit", MAPSIZE_END_X, STARTMENU_Y_EXIT);
	ORIGINAL

	return MapDraw::MenuSelectCursor(STARTMENU_EXIT, GAP_4, STARTMENU_SELECT_X, STARTMENU_Y_START);
}

void Interface::MapInterface()
{ //게임 맵 그리기 
	SKY_BLUE
	MapDraw::BoxDraw(MAPSIZE_SART_X, MAPSIZE_SART_Y, MAPSIZE_END_X, MAPSIZE_END_Y);
	ORIGINAL
}

void Interface::SkipBox()
{
	SKY_BLUE //스킵 박스 그리기
	MapDraw::BoxDraw(INPUTBOX_START_X, INPUTBOX_START_Y, INPUTBOX_WIDTH, INPUTBOX_HEIGHT);
	MapDraw::DrawMidText("Skip : s", MAPSIZE_END_X, INPUTBOX_PRINT);
	ORIGINAL
}

/*
void Interface::MapInterface(int playerLife)
{ //게임 맵 그리기 
	//플레이어 목숨이 절반 이하면 맵 색 붉게 변경
	if (playerLife > MAXLIFE * 0.5f) //f 안 붙이면 double형이 되는데 double이 float보다 연산 속도 느리다.
		SKY_BLUE
	else
		RED

	MapDraw::BoxDraw(MAPSIZE_SART_X, MAPSIZE_SART_Y, MAPSIZE_END_X, MAPSIZE_END_Y);
	ORIGINAL
}*/

//★ const 사용할때는 가져올 정보들이 const로 선언이 되어있어야 한다.(완)
void Interface::PlayerInfoInterface(const Player& player)
{ //플레이어 정보 인터페이스 출력
	std::string tmpString;
	
	//목숨 표시
	MapDraw::DrawPoint("                                    ", PLAYERINTERFACE_X_LIFE, PLAYERINTERFACE_Y);
	tmpString = "Life :";
	//★ word에서 보여주셨던대로 아예 maxLife를 string으로 다 받아 두고 하나씩 지우는 방향으로. 목숨감소는 그렇게. (아까 그게 문자열까지 될지는 확인필요)
	for (int i = 0; player.Get_PlayerLife() > i; i++) //player의 목숨은 player에서 받아와서 처리
		tmpString += " ♥";

	RED
	MapDraw::DrawPoint(tmpString, PLAYERINTERFACE_X_LIFE, PLAYERINTERFACE_Y);
	//점수 표시
	MapDraw::DrawMidText("  Score : " + std::to_string(player.Get_PlayerScore()) + "  ", MAPSIZE_END_X, PLAYERINTERFACE_Y);
	//이름 표시
	MapDraw::DrawPoint("                  ", PLAYERINTERFACE_X_NAME, PLAYERINTERFACE_Y);
	MapDraw::DrawPoint("Name : " + player.Get_PlayerName(), PLAYERINTERFACE_X_NAME, PLAYERINTERFACE_Y);
	ORIGINAL
}

void Interface::RankingInterface(const std::vector<Ranking>& rankingList, int maxRanking)
{
	int playerRank_Y = INPUTBOX_HEIGHT + 5;

	system("cls");
	SKY_BLUE
		MapDraw::BoxDraw(MAPSIZE_SART_X, MAPSIZE_SART_Y - 2, MAPSIZE_END_X, MAPSIZE_END_Y);
	MapDraw::BoxDraw(INPUTBOX_START_X, MAPSIZE_SART_Y + 1, INPUTBOX_WIDTH, INPUTBOX_HEIGHT); //word 입력 박스
	MapDraw::DrawMidText("Ranking", MAPSIZE_END_X, INPUTBOX_HEIGHT);
	MapDraw::DrawMidText("=================================================================================================================================================== ", MAPSIZE_END_X, INPUTBOX_HEIGHT + 3);
	MapDraw::DrawMidText("Name                    Score                    Stage", MAPSIZE_END_X, playerRank_Y++);


	for (int i = 0; i < rankingList.size(); i++)
	{
		if (i == maxRanking) //최대 10명 출력
			break;

		MapDraw::DrawPoint(rankingList[i].name, RANKINGPRINT_X_NAME, playerRank_Y);
		MapDraw::DrawPoint(std::to_string(rankingList[i].score), RANKINGPRINT_X_SCORE, playerRank_Y);
		MapDraw::DrawPoint(std::to_string(rankingList[i].level), RANKINGPRINT_X_LEVEL, playerRank_Y++);
	}

	ORIGINAL
}

// 레퍼런스로 사용
bool Interface::InputBox(INPUTBOX sMaxCount, std::string& sInput, int failed_OldClock)
{
	int stringTmp = 0;

	if (kbhit())
	{
		//게임 진행중에 Input 틀렸을시 잠시간 Input 막기.
		if ((sMaxCount == INPUTBOX_PRINTWORD_MAXCOUNT) && (clock() - failed_OldClock < INPUTBOX_DELAY)) //3초 동안 막아야 하므로
		{
			getch();
			return true;
		}
		
		stringTmp = getch();

		switch (stringTmp)
		{
		case INPUTBOX_SPACE: //스페이스
			return true;
		case INPUTBOX_BACKSPACE: //백스페이스
			if (sInput.empty()) //쳐둔 글자 있을 때만 삭제
				return true;
			else if (sInput.size() >= sMaxCount)
				MapDraw::DrawMidText("                      ", MAPSIZE_END_X, INPUTBOX_START_Y - 2);

			//글자 삭제 체크
			sInput.pop_back();
			MapDraw::DrawMidText("                      ", MAPSIZE_END_X, INPUTBOX_PRINT);
			MapDraw::DrawMidText(sInput, MAPSIZE_END_X, INPUTBOX_PRINT);
			return true;
		case INPUTBOX_ENTER: //엔터

			if (sInput.empty()) //쳐둔 글자 있을 때만 엔터 가능
				return true; //while문 계속 돌기
			else if (sInput.size() >= sMaxCount)
				MapDraw::DrawMidText("                      ", MAPSIZE_END_X, INPUTBOX_START_Y - 2); //최대 글자수 넘으면 출력 고정

			MapDraw::DrawMidText(sInput, MAPSIZE_END_X, INPUTBOX_PRINT);

			return false; //while문 탈출
		default: //문자 입력 받기

			if ((stringTmp >= 'a') && (stringTmp <= 'z'))
			{
				if (sInput.size() < sMaxCount)
				{
					sInput += stringTmp; //일반 문자면 입력 문자열에 추가
					MapDraw::DrawMidText("                      ", MAPSIZE_END_X, INPUTBOX_PRINT); //문자 추가되기 전의 프린트 지우기

				}
				if (sInput.size() >= sMaxCount)
				{
					SKY_BLUE
					MapDraw::DrawMidText(std::to_string(sMaxCount) + "글자 초과!!", MAPSIZE_END_X, INPUTBOX_START_Y - 2);
					ORIGINAL
				}

				MapDraw::DrawMidText(sInput, MAPSIZE_END_X, INPUTBOX_PRINT);
			}
			return true;
		}
	}
	return true;
}

void Interface::PrintStageStairs(STAGELEVEL stageLevel)
{
	int player_X, player_Y;
	int oldClock, countMove = 0;
	bool OddCheck = false;

	SKY_BLUE
	MapDraw::DrawVerticalLine(); //맵 나누기

	//계단 그리기
	for (int stage = STAGELEVEL_1, stairs = 0; stage <= STAGELEVEL_6; stage++)
	{
		GRAY
		//and 비트 연산은 양쪽 값의 bit가 모두 1(true) 이면 1, 둘 중에 하나라도 1이 아니면 0을 나타낸다.
		//홀수면 true 짝수면 false > 홀수는 1, 짝수는 0을 나타내고 이것을 비트 연산자로 1과 비교 > 둘다 1이면 1(true)를 반환한다.
		if (stage & 1)//% 연산자 최대한 쓰지 않는 방식으로 고려. 하지만 함수화 하기 힘들고 가독성이 심각하게 떨어질 경우, 예를 들면 이런 경우 그냥 사용
		{//홀수층 올라가는 계단
			for (int x = 0; x < 5; x++)
				MapDraw::DrawPoint("  ─", STAGEPRINT_STAIRS_X + x * 3 + 3, MAPSIZE_END_Y - stairs++);
		}
		else
		{//짝수층 올라가는 계단
			for (int x = 1; x < 5; x++)
				MapDraw::DrawPoint("─  ", MAPSIZE_END_X - x * 3 - 3, MAPSIZE_END_Y - stairs++);
		}
		
		//마법사 위치 그리기
		if (stage == STAGELEVEL_6)
			MapDraw::DrawPoint("★", MAPSIZE_END_X - 15, MAPSIZE_END_Y - stairs);
	}


	//현재 시작할 스테이지로 향하기 위해. 플레이어 현재 위치 좌표를 이동시킬것.
	switch (stageLevel)
	{
	case STAGELEVEL_1:
		player_X = STAGEPRINT_PLAYER_ODD_X;
		player_Y = STAGEPRINT_PLAYER_LEVEL1_Y;
		break;
	case STAGELEVEL_2:
		player_X = STAGEPRINT_PLAYER_EVEN_X;
		player_Y = STAGEPRINT_PLAYER_LEVEL2_Y;
		break;
	case STAGELEVEL_3:
		player_X = STAGEPRINT_PLAYER_ODD_X;
		player_Y = STAGEPRINT_PLAYER_LEVEL3_Y;
		break;
	case STAGELEVEL_4:
		player_X = STAGEPRINT_PLAYER_EVEN_X;
		player_Y = STAGEPRINT_PLAYER_LEVEL4_Y;
		break;
	case STAGELEVEL_5:
		player_X = STAGEPRINT_PLAYER_ODD_X;
		player_Y = STAGEPRINT_PLAYER_LEVEL5_Y;
		break;
	case STAGELEVEL_6:
		player_X = STAGEPRINT_PLAYER_EVEN_X;
		player_Y = STAGEPRINT_PLAYER_LEVEL6_Y;
		break;
	}

	//플레이어 현재 위치 좌표 그리기
	MapDraw::DrawPoint("●", player_X, player_Y);
	oldClock = clock();

	//and 비트 연산은 양쪽 값의 bit가 모두 1(true) 이면 1, 둘 중에 하나라도 1이 아니면 0을 나타낸다.
	//홀수면 true 짝수면 false > 홀수는 1, 짝수는 0을 나타내고 이것을 비트 연산자로 1과 비교 > 둘다 1이면 1(true)를 반환한다.
	OddCheck = stageLevel & 1;

	//플레이어 현재 위치 > 스테이지 진행 장소 이동
	while (true)
	{
		if (4 == countMove) // == 아니면 오류가 뜨니까 실수 줄일 수 있다.
			break;

		if (clock() - oldClock >= PRINTDELAY_PLAYER)
		{
			MapDraw::DrawPoint("  ", player_X, player_Y);
			
			//%연산자 안쓰게 중복 코드 없게끔 수정 완료
			if (OddCheck) //홀수 레벨. 동북쪽 이동
				player_X += 3;
			else //짝수 레벨. 서북쪽 이동
				player_X -= 3;

			MapDraw::DrawPoint("●", player_X, player_Y -= 1);

			countMove++;
			oldClock = clock();
		}
	}
}