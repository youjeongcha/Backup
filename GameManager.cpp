#include "GameManager.h"

GameManager::GameManager()
{
	system("mode con: cols=156 lines=35");
	srand(time(NULL));
	mStoryLineCount = LoadStory();
	StageSettingList();
}
GameManager::~GameManager()
{
}
void GameManager::Menu()
{
	while (true)
	{
		switch (UI.StartInterface(player)) //player 레퍼런스로 참조
		{
		case STARTMENU_START:
			GameStart();
			break;
		case STARTMENU_RANK:
			//rank.RankPrint();
			UI.RankingInterface(rank.Get_RankingList(), (int)MAXRANK);
			UI.EnterNext(); //엔터로 다음 화면 넘어가기 //★ input 클래스 따로 만들어서 거기서 처리
			system("cls");
			break;
		case STARTMENU_EXIT:
			return;
		default:
			break;
		}
	}
}

void GameManager::GameStart()
{
	int stageLevel = 1;
	std::string sInput = "";


	UI.MapInterface(); //맵
	UI.PlayerInfoInterface(player); //플레이어 정보 인터페이스 출력

	//★ 인터페이스에서 처리
	UI.SkipBox();

	//스토리 출력 + 스킵 기능
	SKY_BLUE
	PrintStory(0, 0);
	ORIGINAL

	//<이름 입력 파트>
	//맵
	UI.MapInterface();
	//★ 인풋 클래스
	//이름 입력 박스
	SKY_BLUE
	MapDraw::BoxDraw(INPUTBOX_START_X, INPUTBOX_START_Y, INPUTBOX_WIDTH, INPUTBOX_HEIGHT);
	MapDraw::DrawMidText("이름 입력", MAPSIZE_END_X, INPUTBOX_START_Y - 3);
	ORIGINAL
	//문자열 입력 //★ 인풋에서 입력을 받고 input박스는 그걸 호출해서 사용해야 했다.
	while (UI.InputBox(INPUTBOX_PRINTNAME_MAXCOUNT, sInput, 0)) {}
	//이름 설정
	player.Set_PlayerName(sInput);


	UI.MapInterface(); //맵
	UI.PlayerInfoInterface(player); //플레이어 정보 인터페이스 출력


	//스테이지 (인자값 받는 거 따라 진행 레벨 다르게)
	while (true)
	{
		//Stage에서 목숨이 다하기 전에 일정 이상의 점수 획득하면 true 다음 스테이지로 이동
		if (Stage(stageLevel++))
		{ //Stage가 true면 다음 스테이지

			//stage는 최대 6레벨인데 6레벨은 true를 받지 않는다. 무제한 게임
			//if (stageLevel > STAGELEVEL_6)
			//	break;

			//stage 상승하면 player의 score 초기화
			player.Set_PlayerScore(0);
			//생성된 단어 리스트 초기화
			wordManager.RestList();
			UI.MapInterface(); //맵
			UI.PlayerInfoInterface(player); //플레이어 정보 인터페이스 출력
		}
		else
		{ //Stage가 false면 게임 오버
			int line = 0, maxLine, oldClock = 0;
			std::string gameEndText = "";
			std::vector<std::string> gameOverStoryList = storyList[STORYTYPE_GAMEOVER];

			//★ switch로 처리
			switch (stageLevel - 1)
			{
			case STAGELEVEL_6:
				maxLine = GAMEOVERSTORY_6;
				gameEndText = "§ G A M E  C L E A R §";
				break;
			default:
				maxLine = GAMEOVERSTORY_1_5;
				gameEndText = "§ G A M E  O V E R §";
				break;
			}

			//마지막 스테이지.(무제한 스테이지) 엔딩
			while (line < maxLine)
			{
				if (kbhit())
					getch();

				//엔딩 스토리 한줄씩 출력. 딜레이 시간 이상 기다리고 출력된다.
				if (clock() - oldClock >= PRINTDELAY)
				{
					RED
					if (stageLevel - 1 == STAGELEVEL_6) //보류::점수에 따라 엔딩 차이나게.
					{
						if (line >= GAMEOVERSTORY_6_REALITY)
							ORIGINAL
						MapDraw::DrawMidText(gameOverStoryList[GAMEOVERSTORY_1_5 + line++], MAPSIZE_END_X, STORYLINE_Y + line);
					}
					else
						MapDraw::DrawMidText(gameOverStoryList[line++], MAPSIZE_END_X, STORYLINE_Y + line);
					oldClock = clock();
				}
			}

			MapDraw::DrawMidText(gameEndText, MAPSIZE_END_X, INPUTBOX_PRINT);
			ORIGINAL

			//랭킹 정렬 + 저장
			rank.SaveSortRanking(stageLevel, player.Get_PlayerName(), player.Get_PlayerScore());

			//플레이어 + 생성된 단어 리스트 초기화
			player.InitalSetting();
			wordManager.RestList();

			UI.EnterNext(); //엔터로 다음 화면 넘어가기
			break;
		}
	}
}

void GameManager::PrintStory(int printLineCount, int oldClock)
{//루프문은 돌때마다 메모리가 쌓여서 큰 범위를 돌릴 경우 오버플로우가 터지기도 한다. 
	//범위가 넓지만 느려도 되면 재귀. 범위 좁고 빨라야 하면 루프
	std::vector<std::string> intoStoryList = storyList[STORYTYPE_INTRO];

	//스토리 전부 출력 됐으면 종료
	if (mStoryLineCount == printLineCount)
		return;

	//Sleep(1000); //1초 딜레이 //Slepp 대신 Clock으로 사용. 경과시간 알려줌. //Sleep은 프로그램 자체를 정지시킨다.

	while (clock() - oldClock < PRINTDELAY)
	{//while로 제한 안 걸어두면 다음 재귀 넘어가면서 문제가 생긴다. 조건을 만족하지 못하면 인자값 변동이 없었기 때문.
		//스킵
		if (kbhit())
		{//키보드 입력이 들어오면 스킵 확인
			if (getch() == 's')
				return;
		}
	}

	if (printLineCount < STRORYLINE_MAX) //출력 10줄 못 넘게
		MapDraw::DrawMidText(intoStoryList[printLineCount], MAPSIZE_END_X, STORYLINE_Y + printLineCount);
	else
	{//10줄 넘으면 전체 다시 출력
		for (int i = STRORYLINE_MAX - 1, lineRest = 0; i >= 0; i--, lineRest++)
		{
			MapDraw::DrawMidText("                                                 ", MAPSIZE_END_X, STORYLINE_Y + lineRest);
			MapDraw::DrawMidText(intoStoryList[printLineCount - i], MAPSIZE_END_X, STORYLINE_Y + lineRest);
		}
	}

	oldClock = clock();
	printLineCount++;

	return PrintStory(printLineCount, oldClock);
}

void GameManager::PrintStageStory(int level)
{
	std::vector<std::string> stageStoryList = storyList[STORYTYPE_STAGELEVEL];
	int line = 0, oldClock = 0;
	int storyLine_X[2] = { MAPSIZE_END_X * 0.1f , MAPSIZE_END_X * 0.4f };
	//int maxPrintLine = stageStoryList.size() / 6;
	int maxPrintLine = stageStoryList.size() / 6;
	int startIndex = (level - 1) * STAGESTROY_LINECOUNT;
	int storyLine_Y = STORYLINE_Y + (level - 1) / 2 * STAGESTROY_PRINTGAP_Y;
	int Odd_Or_Even_Level = (level - 1) & 1;

	//이미 쓰여진 스토리 한번에 출력 //2~6레벨 사이에만 적용 //써지는 건 1~5레벨 사이의 글
	if (level != 1)
	{
		for (int writtenPrint = 1; writtenPrint < level; writtenPrint++)
		{ //레벨별 글뭉치 단위

			for (int line = 0; line < STAGESTROY_LINECOUNT; line++)
			{
				MapDraw::DrawPoint(stageStoryList[(writtenPrint - 1) * STAGESTROY_LINECOUNT + line], storyLine_X[(writtenPrint - 1) & 1], 9 + (writtenPrint - 1) / 2 * STAGESTROY_PRINTGAP_Y + line);
			}
		}
	}

	//플레이어가 탑 올라가는 스테이지 확인 가능한 그림 그리기.
	UI.PrintStageStairs((STAGELEVEL)level);

	//해당 층에서 작성하는 스토리 한줄씩 출력
	while (line < maxPrintLine) //★ 굳이 enum 쓰지 말고 배열 size로 자동화
	{
		if (kbhit())
			getch();

		if (clock() - oldClock >= PRINTDELAY)
		{//비트 연산
			MapDraw::DrawPoint(stageStoryList[startIndex + line++], storyLine_X[Odd_Or_Even_Level], storyLine_Y + line);
			oldClock = clock();
		}
	}

	UI.EnterNext(); //엔터로 다음 화면 넘어가기
}

bool GameManager::Stage(int level)
{
	STAGESETTING stageSetting = mStageSetting[level - 1];
	//int createSpeed, dropSpeed, clearStage, usedItem_UsingTime;
	int  usedItem_UsingTime;
	int create_OldClock = 0, drop_OldClock = 0, failed_OldClock = 0, usedItem_OldClock = 0;
	std::string inputWord = "";
	bool returnOriginSpeedCheck = false, hideWordCheck = false; //워드 가리기 아이템 작동
	ITEM usedItem = ITEM_NONE;

	SKY_BLUE
	MapDraw::DrawMidText("§ " + std::to_string(level) + " stage §", MAPSIZE_END_X, STAGE_TEXTPRINT_Y);

	create_OldClock = clock();

	while (true) //stage 표시 뜨고 잠시 뒤에 출력되도록
	{
		if (clock() - create_OldClock > PRINTDELAY)
			break;
	}

	//인터페이스 나누기
	UI.MapInterface(); //맵
	SKY_BLUE
	MapDraw::DrawVerticalLine(); //맵 나누기
	ORIGINAL

	//스토리 띄우기 + 플레이어가 탑 올라가는 스테이지 확인 가능한 그림 그리기.(별도의함수 있음)
	PrintStageStory(level);

	//게임 진행창 띄우기
	UI.MapInterface(); //맵
	SKY_BLUE
	MapDraw::BoxDraw(INPUTBOX_START_X, INPUTBOX_START_Y, INPUTBOX_WIDTH, INPUTBOX_HEIGHT); //word 입력 박스
	ORIGINAL
	

	//게임 시작
	while (true)
	{
		//if (clock() - failed_OldClock >= 3000) //Input 틀렸을시 잠시간 Input 막기.
		//단어 Input 관리 + failed 했을 경우에 대기 시간관리(InputBox())
		if (UI.InputBox(INPUTBOX_PRINTWORD_MAXCOUNT, inputWord, failed_OldClock) == false) //false면 엔터를 눌렀다는 의미
		{
			//Word* deleteWord = NULL;//포인터로 삭제되어야 할 단어 주소 가져와서 쓸 것.

			//단어 맞췄는지 틀렸는지 확인 + 맞췄다면 맞춘 단어의 아이템 타입 반환(일반은 노말). 아니면 ITEM_NONE
			usedItem = wordManager.TypingCheck(&inputWord);

			//단어 맞췄을 경우 점수 증가 + 아이템 작동
			if (usedItem != ITEM_NONE)
			{ 
				player.Set_PlayerScore(player.Get_PlayerScore() + inputWord.size() * 3); //word 한자당 3점 취급
				UI.PlayerInfoInterface(player); //플레이어 정보 인터페이스 출력
				
				//아이템 작동(일반 단어는 안에서 걸러진다.) + 단어 삭제
				wordManager.ItemOperate(usedItem, stageSetting.createSpeed, stageSetting.dropSpeed, usedItem_UsingTime);

				//입력창에 있던 문자 저장해둔 것 비우기
				inputWord.clear();

				//점수가 일정이상 다다르면 다음 스테이지로.
				if ((level != STAGELEVEL_6) && (player.Get_PlayerScore() >= stageSetting.clearStage)) //6스테이지는 마법사 나옴. 랭킹전 하게 클리어 한계 두지 x
					return true;
			}
			else
			{ //단어 틀렸을 경우 failed 출력
				RED
				MapDraw::DrawMidText("     Failed Compare!!     ", MAPSIZE_END_X, INPUTBOX_PRINT);
				ORIGINAL

				inputWord.clear();
				failed_OldClock = clock(); //잠시간 Input 막기.
			}
		}
		//else if (kbhit()) getch();

		//시간 변경하는 아이템 작동 이후 시간 돌려두기 위해
		if ((usedItem != ITEM_NONE) && (usedItem != ITEM_NOMAL) && (usedItem != ITEM_SCREEN_CLEAR))
		{
			usedItem_OldClock = clock();
			returnOriginSpeedCheck = true; //아이템 사용하고 시간 조정 원래대로 돌려두기 한 번만.

			//워드 가리기 아이템 작동
			if (usedItem == ITEM_HIDE)
			{
				hideWordCheck = true;

				//아이템 사용 즉시 "===="으로 변환시키기 위해 (drop에서만 단어를 갱신해주고 있어서. 이렇게 안 하면 한번 떨어지고 아이템 적용된다.)
				//워드 떨어지게 출력하는 함수이지만. y-로 지우고 y로 출력해서 여기서 사용해도 문제 없음.
				wordManager.DropWordPrint(hideWordCheck);
			}

			usedItem = ITEM_NOMAL; //작동 시간 설정 후 if문 들어오지 않도록 초기화
		}

		//★ 위에 구조체 배열로 해결
		//시간 돌리기
		if ((returnOriginSpeedCheck) && (clock() - usedItem_OldClock >= usedItem_UsingTime))
		{
			stageSetting = mStageSetting[level - 1];

			returnOriginSpeedCheck = false;
			hideWordCheck = false;
		}


		//단어 생성
		if (clock() - create_OldClock >= stageSetting.createSpeed)
		{//생성 텀 스테이지별 조정
			wordManager.CreateWord(hideWordCheck);
			create_OldClock = clock();
		}

		//단어 떨어뜨리기
		if (clock() - drop_OldClock > stageSetting.dropSpeed)
		{
			if (wordManager.DropWord(player.Get_PlayerLife())) //워드 XY좌표 옮기기 + 목숨 감소 bool 체크
			{
				wordManager.DropWordPrint(hideWordCheck);//GmaeOver 하고도 단어 뜨도록
				player.DecreasePlayerLife();
				UI.PlayerInfoInterface(player); //플레이어 정보 인터페이스 출력

				SKY_BLUE
				MapDraw::BoxDraw(INPUTBOX_START_X, INPUTBOX_START_Y, INPUTBOX_WIDTH, INPUTBOX_HEIGHT); //word 입력 박스 안 망가지게(공백 X)
				ORIGINAL

				//게임 오버 체크
				if (player.Get_PlayerLife() == 0)
					return false;
			}

			//워드 떨어지게 출력
			wordManager.DropWordPrint(hideWordCheck);

			drop_OldClock = clock();

			SKY_BLUE
			MapDraw::BoxDraw(INPUTBOX_START_X, INPUTBOX_START_Y, INPUTBOX_WIDTH, INPUTBOX_HEIGHT); //word 입력 박스

			//단어에 가려지지 않도록
			if ((usedItem == ITEM_NONE) && (drop_OldClock - failed_OldClock < INPUTBOX_DELAY)) //failed 상태일때는 failed 문구 출력
			{//3초가 지나기 전에는 계속 들어와야 한다. //drop-OldClock을 쓴 이유 > clock() 호출 바로 전에 해서 또 할 필요X
				RED
				MapDraw::DrawMidText("     Failed Compare!!     ", MAPSIZE_END_X, INPUTBOX_PRINT);
				ORIGINAL
			}
			else
			{
				ORIGINAL
				MapDraw::DrawMidText(inputWord, MAPSIZE_END_X, INPUTBOX_PRINT);
			}

			//글자 초과 프린트
			if (inputWord.size() >= INPUTBOX_PRINTWORD_MAXCOUNT)
			{
				SKY_BLUE
				MapDraw::DrawMidText(std::to_string(INPUTBOX_PRINTWORD_MAXCOUNT) + "글자 초과!!", MAPSIZE_END_X, INPUTBOX_START_Y - 2);
				ORIGINAL
			}
		}
	}
}

int GameManager::LoadStory()
{
	int lineCount = 0;
	std::string storyTmp;
	std::vector<std::string> tmpStoryList; //★ into,stage, gameOver를 enum으로 판단해서. 백터 배열로 호출해서 사용 
	//std::vector<std::string> stageStoryList;
	//std::vector<std::string> gameOverStoryList;

	std::ifstream load;

	//★ 이름 변경 Save라고 하면 저장되는 데이터로 이해된다.
	load.open("StageStory.txt");
	if (load.is_open())
	{
		for (int i = 0; i < STAGELEVEL_6; i++)
		{
			//load >> storyTmp; //txt 파일에 구분 위해 작성해둔것. 의미X 사용X
			for (int j = 0; j < STAGESTROY_LINECOUNT; j++)
			{
				getline(load, storyTmp);
				tmpStoryList.push_back(storyTmp);
			}
		}

		storyList.insert({ STORYTYPE_STAGELEVEL, tmpStoryList });
		tmpStoryList.clear();
		load.close();
	}
	//★ 
	load.open("GameOverStory.txt");
	if (load.is_open())
	{
		for (int i = 0; i < 2; i++)
		{
			if (i == 0) //1~5레벨 GameOver 했을 때 스토리 줄 수 
				lineCount = GAMEOVERSTORY_1_5;
			else //6레벨 GameOver 했을 때 스토리 줄 수
				lineCount = GAMEOVERSTORY_6;
			//load >> lineCount; //txt 파일 1~5레벨, 6레벨 글자수 구분 위해 작성해둔것
			for (int j = 0; j < lineCount; j++)
			{
				getline(load, storyTmp);
				tmpStoryList.push_back(storyTmp);
			}
		}

		storyList.insert({ STORYTYPE_GAMEOVER, tmpStoryList });
		tmpStoryList.clear();
		load.close();
	}
	//★ 
	load.open("IntroStory.txt");
	if (load.is_open())
	{
		load >> lineCount;

		for (int i = 0; i < lineCount; i++)
		{
			getline(load, storyTmp);
			tmpStoryList.push_back(storyTmp);
		}

		storyList.insert({ STORYTYPE_INTRO, tmpStoryList });
		load.close();
	}
	return lineCount;
}

void GameManager::StageSettingList()
{
	for (int setLevel = 0; setLevel < STAGELEVEL_6; setLevel++)
	{
		switch (setLevel + 1)
		{
		case STAGELEVEL_1:
			//MapDraw::DrawMidText("마법사가 예고했던 시간이 되자 그가 탑 위에 나타났습니다.", MAPSIZE_END_X, STAGE_TEXTPRINT_Y + 4);
			mStageSetting[setLevel].createSpeed = CREATEWORD_SPEED_STAGE1;
			mStageSetting[setLevel].dropSpeed = DROP_SPEED_STAGE1;
			mStageSetting[setLevel].clearStage = CLEARSTAGE_1;
			break;
		case STAGELEVEL_2:
			//MapDraw::DrawMidText("레벨 2 추후 수정", MAPSIZE_END_X, STAGE_TEXTPRINT_Y + 4);
			mStageSetting[setLevel].createSpeed = CREATEWORD_SPEED_STAGE2;
			mStageSetting[setLevel].dropSpeed = DROP_SPEED_STAGE2;
			mStageSetting[setLevel].clearStage = CLEARSTAGE_2;
			break;
		case STAGELEVEL_3:
			//MapDraw::DrawMidText("레벨 3 추후 수정", MAPSIZE_END_X, STAGE_TEXTPRINT_Y + 4);
			mStageSetting[setLevel].createSpeed = CREATEWORD_SPEED_STAGE3;
			mStageSetting[setLevel].dropSpeed = DROP_SPEED_STAGE3;
			mStageSetting[setLevel].clearStage = CLEARSTAGE_3;
			break;
		case STAGELEVEL_4:
			//MapDraw::DrawMidText("레벨 4 추후 수정", MAPSIZE_END_X, STAGE_TEXTPRINT_Y + 4);
			mStageSetting[setLevel].createSpeed = CREATEWORD_SPEED_STAGE4;
			mStageSetting[setLevel].dropSpeed = DROP_SPEED_STAGE4;
			mStageSetting[setLevel].clearStage = CLEARSTAGE_4;
			break;
		case STAGELEVEL_5:
			//MapDraw::DrawMidText("레벨 5 추후 수정", MAPSIZE_END_X, STAGE_TEXTPRINT_Y + 4);
			mStageSetting[setLevel].createSpeed = CREATEWORD_SPEED_STAGE5;
			mStageSetting[setLevel].dropSpeed = DROP_SPEED_STAGE5;
			mStageSetting[setLevel].clearStage = CLEARSTAGE_5;
			break;
		case STAGELEVEL_6:
			//MapDraw::DrawMidText("레벨 6 추후 수정", MAPSIZE_END_X, STAGE_TEXTPRINT_Y + 4);
			mStageSetting[setLevel].createSpeed = CREATEWORD_SPEED_STAGE6;
			mStageSetting[setLevel].dropSpeed = DROP_SPEED_STAGE6;
			//clearStage = CLEARSTAGE_6;
			break;
		}
	}
}