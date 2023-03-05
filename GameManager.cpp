#include "GameManager.h"
//static_cast<변환할>(변환될) //다운캐스팅


GameManager::GameManager()
{
	system("mode con: cols=82 lines=25");

	int seed = time(NULL);
	srand(seed); // 시드값을 저장에서 저장할 게 아니라. srand에 사용되는 시드값 저장해야 하는 것(저장할때 빼오면 시드값이 시시각각 달라짐)
	player.SetSeed(seed);

	mShowContinueMenu = false; //default값 게임 새로 하기
	battle = new Battle; //동적할당까지 해줘야 실체가 있다.
}
GameManager::~GameManager()
{
}

void GameManager::CallMainMenu()
{
	ifstream load;

	load.open("SaveContinueCheck.txt"); //이어하기 체크 확인 bool값 받아온다.(Player 파일이 존재 이외에 이어하기 판단 가능한 요소 필요.)
	if (load.is_open())
	{
		load >> mShowContinueMenu;
		load.close();
	}

	while (MainMenu()) {}
}

bool GameManager::MainMenu()
{//default값 새로하기.
	ifstream load;
	PrintXY printXY; 	
	printXY.Print_Y = MENUPRINT_START_Y; //반복 돌때마다 초기화
	bool bContinueCheck = false; //default값 새로하기.

	//맵 범위 그리기
	MapDraw::BoxDraw(MAP_START, MAP_START, MAP_END_X, MAP_END_Y);
	//로비 창 띄우기
	MapDraw::DrawMidText("☆★ DonGeonRPG ★☆", MAP_END_X, printXY.Print_Y);
	MapDraw::DrawMidText("New Game", MAP_END_X, printXY.Print_Y += GAP_3);

	load.open("SavePlayerInfo.txt"); //이어하기 파일 내용이 있는지 확인한다.
	if (load.is_open() && mShowContinueMenu) //파일이 있지만 죽어서 이어하기 불가한 경우 있다.
	{
		MapDraw::DrawMidText("Continue Game", MAP_END_X, printXY.Print_Y += GAP_3);
		load.close();

		bContinueCheck = true;
	}

	MapDraw::DrawMidText("Help", MAP_END_X, printXY.Print_Y += GAP_3);
	MapDraw::DrawMidText("Game Exit", MAP_END_X, printXY.Print_Y += GAP_3);


	if (bContinueCheck == false) //새로하기
	{
		//화살표
		switch (MapDraw::MenuSelectCursor(MENUSELECT_EXIT - 1, GAP_3, MAP_END_X * 0.5 - GAP_6, printXY.Print_Y - GAP_6))
		{
		case MENUSELECT_NEW:
			NewGame();
			break;
		case MENUSELECT_HELP - 1:
			Help();
			break;
		case MENUSELECT_EXIT - 1:
			return false;
		}
	}
	else //이어하기
	{
		//화살표
		//  %와/부호는 while문을 반복해서 돌 때 (ex.게임 프레임 단위 갱신) 소모되는 비용이 크므로 *로 변형하여 사용하는 것을 권장 (ex.*0.5)
		switch (MapDraw::MenuSelectCursor(MENUSELECT_EXIT, GAP_3, MAP_END_X * 0.5 - GAP_6, printXY.Print_Y - GAP_9))
		{
		case MENUSELECT_NEW:
			NewGame();
			break;
		case MENUSELECT_CONTINUE:
			ContinueGame();
			break;
		case MENUSELECT_HELP:
			Help();
			break;
		case MENUSELECT_EXIT:
			return false;
		}
	}
	return true;
}

void GameManager::Help()
{
	//반복 돌때마다 초기화
	PrintXY printXY;
	printXY.Print_Y = MENUPRINT_START_Y;

	//맵 범위 그리기
	MapDraw::BoxDraw(MAP_START, MAP_START, MAP_END_X, MAP_END_Y);
	//로비 창 띄우기
	GRAY
	MapDraw::DrawMidText("☆★ Help ★☆", MAP_END_X, printXY.Print_Y);
	ORIGINAL
	MapDraw::DrawMidText("Next : alphabets, numbers, space, enter", MAP_END_X, printXY.Print_Y += GAP_2);
	MapDraw::DrawMidText("Move : a(A), d(D), w(W), s(S)", MAP_END_X, printXY.Print_Y += GAP_2);
	MapDraw::DrawMidText("Select : enter", MAP_END_X, printXY.Print_Y += GAP_2);
	MapDraw::DrawMidText("Menu : m(M)", MAP_END_X, printXY.Print_Y += GAP_2);
	getch();
}



void GameManager::NewGame()
{
	mShowContinueMenu = false;
	SaveContinueCheck();

	player.PlayeInitialSetting();
	player.GetMonsterBook()->ResetMonsterBook(); //몬스터 도감 초기화
	player.GetMonsterBook()->ReadMonsterBook(); //몬스터 도감 불리안 배열 초기화

	monsterManager.CreateMonsterReset(); //생성되어있는 몬스터 리스트 초기화
	monsterManager.ResetSaveMonstersTxt(); //생성 몬스터 txt 저장 파일 초기화
	GameStart();
}

void GameManager::ContinueGame()
{
	bool bPlayerGameOverCheck;
	ifstream load;
	load.open("SavePlayerInfo.txt");
	load >> bPlayerGameOverCheck;
	load.close();

	if (bPlayerGameOverCheck == true)
		mSceneCheck = (SCENE)player.PlayeInitialSetting(false); //초기 세팅 X : 스텟 설정 초기화 + 씬을 처음부터 하되 이름은 유지되도록 //이름 유지 GameOver 여부 따라 true와 false로
	else
		mSceneCheck = (SCENE)player.LoadPlayerInfo(); //씬 정보 + 플레이어 정보 가져오기

	srand(player.GetSeed()); //쓰던 시드값 들고 온다.
	monsterManager.CreateMonsterReset(); //생성되어있는 몬스터 리스트 초기화
	monsterManager.LoadMonsters(); //몬스터 정보 가져오기(몬스터 객체를 새로 만들고 텍스트의 값을 넣어주는 식이라 리스트 초기화 안하면 같은 스텟 몬스터 x2)
	player.GetMonsterBook()->ReadMonsterBook(); //몬스터 도감 불리안 배열 초기화
	GameStart(mSceneCheck, MENUSELECT_CONTINUE);
}

void GameManager::GameStart(SCENE scene, MENUSELECT startType)
{
	//int deadMonster = 0;
	int randomScene;
	bool gameOverCheck = false;

	Interface::DrawInterface(player);

	//랜덤 씬(이벤트) 발생
	while (true) 
	{
		switch (scene)
		{
		case SCENE_INTRO:
			Intro(); //새 게임 시작
		case SCENE_PICKUPWEAPON:
			PickUpWeapon(); //무기 줍기
		case SCENE_NAME: // ★ 나중에 하겠지만. Print 함수에서 저장할 필요 없는 구문은 저장 못하는 Print 함수로 대체
			if ((startType == MENUSELECT_NEW) || (player.Get_Name() == "???")) //이름 설정 전에 저장하면 이어하기로 플레이어 이름 설정 필요.
				Name(); //이름 기록
			break;
		case SCENE_WEAPONSHOP:
			WeaponShop();
			break;
		case SCENE_SPRINGOFRECOVERY:
			SpringOfRecovery();
			break;
		case SCENE_MONSTER:
			gameOverCheck = Monster();
			if (gameOverCheck == true)
			{
				getch();
				return;
			}
			break;
		}

		SavePrint("좁다랗게 나있는 길을 걷기 시작한다.");

		randomScene = SCENE(rand() % 10);

		if (randomScene >= 0 && randomScene < 6) //몬스터 확률에 대응하면 다음 씬으로 몬스터.
			scene = SCENE_MONSTER;
		else if (randomScene >= 6 && randomScene < 8) //무기 상점 확률
			scene = SCENE_WEAPONSHOP;
		else if (randomScene >= 8 && randomScene < 10) //회복샘 확률
			scene = SCENE_SPRINGOFRECOVERY;

		//LATER::몬스터가 5마리 죽으면 길이 열린다.
		////TODO::게임 클리어 조건 설정 바람.
		//if (deadMonster == 5)
		//{
		//	Print("나는 여기서 종료가 된다고 의심중이다.");
		//	system("pause");
		//	break;
		//}
	}
}



void GameManager::Menu()
{
	PrintXY printXY;

	while (true)
	{
		printXY.Print_Y = MENUPRINT_START_Y;

		system("cls");
		//Todo : 간단하게 현재 상황 브리핑 (기획 굿노트 참고)


		MapDraw::BoxDraw(MAP_START, MAP_START, MAP_END_X, MAP_END_Y);
		MapDraw::DrawMidText("플레이어 정보", MAP_END_X, printXY.Print_Y += GAP_6);
		MapDraw::DrawMidText("몬스터 도감", MAP_END_X, printXY.Print_Y += GAP_2);
		MapDraw::DrawMidText("저장", MAP_END_X, printXY.Print_Y += GAP_2);
		MapDraw::DrawMidText("돌아가기", MAP_END_X, printXY.Print_Y += GAP_2);
		//iMapDraw::DrawMidText("종료", MAP_END_X, mPrint_Y += GAP_2);

		//화살표
		//  %와/부호는 while문을 반복해서 돌 때 (ex.게임 프레임 단위 갱신) 소모되는 비용이 크므로 *로 변형하여 사용하는 것을 권장 (ex.*0.5)
		switch (MapDraw::MenuSelectCursor(MENU_END, GAP_2, MAP_END_X * 0.5 - GAP_6, MENUPRINT_START_Y + GAP_6))
		{
		case MENU_PLAYER:
			player.PrintInfo();
			getch();
			break;
		case MENU_MONSTER:
			Interface::DrawInterface(player);
			player.PrintMonsterBook(monsterManager.Get_MonsterInfoList());
			getch();
			break;
		case MENU_SAVE:
			Save();
			break;
		case MENU_END:
			return;
		//case MENU_GAMEEXIT:
		//	return;
		}
	}
}

void GameManager::Save()
{
	//플레이어 정보 저장 기능
	player.SavePlayerInfo(mSceneCheck, (mSceneCheck > SCENE_PICKUPWEAPON));//무기를 지니고 있는지 판단.
	//생존한 몬스터 저장 기능
	monsterManager.SaveMonsters();
	//몬스터 도감 저장 기능
	player.GetMonsterBook()->SaveMonsterBook();
	//게임 이어하기 선택지 개방
	mShowContinueMenu = true;
	SaveContinueCheck();
}

void GameManager::Intro()
{
	mSceneCheck = SCENE_INTRO;
	Interface::Print("............");
	Interface::Print("손끝에 딱딱하게 말라붙은 감촉이 느껴졌다.");
	Interface::Print("핏자국으로 인해 제목을 알 수 없는 책을 펼쳤다..");
}

void GameManager::PickUpWeapon()
{
	mSceneCheck = SCENE_PICKUPWEAPON;
	Interface::Print("시체들 사이에서 굴러다니는 무기 하나를 주웠다.");
	weaponShop.FirstWeapon(&player);
	Interface::DrawInterface(player);
}

void GameManager::Name()
{
	string _Name;

	mSceneCheck = SCENE_NAME;
	Interface::Print("Made in Dongeon.");
	Interface::Print("그 문구 아래에 이름이 적혀있다.");
	MapDraw::BoxErase(MAP_END_X, MAP_END_Y / GAP_3 * GAP_2);
	YELLOW
	MapDraw::DrawMidText("Player 이름 입력 : ", MAP_END_X, MENUPRINT_START_Y + GAP_2);
	cin >> _Name;
	ORIGINAL
	player.SetName(_Name);
	Interface::DrawInterface(player); //입력 창을 벗어난 문자를 없애는 용도
	Interface::Print(_Name + "...");
}

void GameManager::WeaponShop()
{
	mSceneCheck = SCENE_WEAPONSHOP;
	SavePrint("던전의 무기 상점에 오신걸 환영합니다.");
	weaponShop.Shop(&player);
	Interface::DrawInterface(player);
	SavePrint("구매 감사합니다.");
}

void GameManager::SpringOfRecovery()
{
	mSceneCheck = SCENE_SPRINGOFRECOVERY;

	SavePrint("미약한 불빛이 보인다..");
	SavePrint("걸음을 서두른다.");
	SavePrint("가까이서 본 불빛은 작은 반딧불이다.");
	SavePrint("다가갈수록 수가 많아지는 불빛을 따라가니 빛나는 샘이 나왔다.");

	SavePrint("샘의 물을 마시니 몸이 가벼워진다.");

	SavePrint("HP" + to_string(player.Recover()) + " 회복!");
	Interface::DrawInterface(player);

	SavePrint("반딧불이가 떠나간다.");
}

bool GameManager::Monster()
{
	//플레이어와 몬스터 부분 함수화. 승리 체크 부분에서는 Character로 몬스터와 플레이어어 어느 인자가 들어오는지에 따라 차별점 주기.
	mSceneCheck = SCENE_MONSTER;

	Character* monster;
	WINCHECK whoWin;

	SavePrint("몬스터를 조우했습니다.");

	monster = battle->MeetMonster(&player, &monsterManager);
	whoWin = battle->BattleTurn(monster, &player, &monsterManager);

	//string으로 비교하는 것보다 enum으로 구분하기. 아예 세세하게 플레이어나 몬스터 승리, 도망까지 (패배는 상대의 승리이므로 패배X) 
	switch (whoWin)  //승리체크
	{
	case WINCHECK_PLAYER_WIN:
	{ //플레이어가 승리
		WinnerReward(WINCHECK_PLAYER_WIN, &player, monster);

		//패배한 몬스터 삭제
		list<Character*>* monsterList = monsterManager.Get_MonsterList();
		for (list<Character*> ::iterator iter = monsterList->begin(); iter != monsterList->end();)
		{
			if (((*iter)->Get_MonsterType() == monster->Get_MonsterType()) && ((*iter)->Get_NowHP() == 0))
			{
				Character* c = (*iter); //list에서도 pop 하고 iter의 할당된 메모리를 해제해야할 때
				monsterList->erase(iter); //리스트에서 pop
				delete c; //iter가 넘어가지 않은 시점에서 할당된 메모리 해제
				break;
			}
			else
				iter++;
		}
		break;
	}
	case WINCHECK_PLAYER_RUNAWAY: //LATER::도망 확률에 따라 성공과 실패 구현. 몬스터별? 레벨별? 확률에 차이를 둔다.
	{ //플레이어가 도망
		SavePrint("......");
		SavePrint("몬스터에게서 무사히 도망쳤다.");
		break;
	}
	case WINCHECK_MONSTER_WIN: //몬스터가 승리
	{
		WinnerReward(WINCHECK_MONSTER_WIN, monster, &player);

		//GameOver한 플레이어는 이름과 GameOverCheck만 SavePlayerInfo.txt 파일에 저장한다.
		player.SaveGameOverPlayerInfo();
		//생존한 몬스터 저장 기능
		monsterManager.SaveMonsters();
		//몬스터 도감 저장 기능
		player.GetMonsterBook()->SaveMonsterBook();
		//게임 이어하기 선택지 개방
		mShowContinueMenu = true;
		SaveContinueCheck();
		return true;
	}
	case WINCHECK_MONSTER_RUNAWAY:
	{ //몬스터가 도망
		SavePrint("......");
		SavePrint("잠시 방심한 사이...");
		SavePrint("틈을 노리고 있던 몬스터가 도망갔다.");
		break;
	}
	default:
		break;
	}

	//공격, 행동, 가방, 도망이 출력된 그대로 남아있다.
	Interface::DrawInterface(player);
	return false;
}

void GameManager::WinnerReward(WINCHECK whoWin, Character* winner, Character* loser)
{
	if (whoWin == WINCHECK_PLAYER_WIN)
	{ //플레이어 승리
		SavePrint("WIN!");
		SavePrint("전투가 종료되었습니다.");
		SavePrint("적절한 보상이 지급됩니다.");

		player.GetMonsterBook()->RecodeMonsterBook(SITUATION_WIN, loser->Get_MonsterType()); //도감 기록
	}
	else
	{ //몬스터 승리
		MapDraw::BoxErase(MAP_END_X, MAP_END_Y / GAP_3 * GAP_2);
		RED
		MapDraw::DrawMidText("GAME OVER", MAP_END_X, MENUPRINT_START_Y + GAP_2);
		ORIGINAL
	}
	
	//보상 수령 :: 공통
	winner->Set_Gold(winner->Get_Gold() + loser->Get_Gold()); //골드
	winner->Set_NowEXP(winner->Get_NowEXP() + loser->Get_GetEXP()); //EXP

	if (whoWin == WINCHECK_PLAYER_WIN)
	{ //플레이어 보상 출력
		string sTmp;

		Interface::DrawInterface(player);

		MapDraw::BoxErase(MAP_END_X, MAP_END_Y / GAP_3 * GAP_2);
		GOLD
		sTmp = "획득한 경험치 : " + to_string(loser->Get_GetEXP());
		MapDraw::DrawMidText(sTmp, MAP_END_X, MENUPRINT_START_Y + GAP_2);
		sTmp = "획득한 골드 : " + to_string(loser->Get_Gold());
		MapDraw::DrawMidText(sTmp, MAP_END_X, MENUPRINT_START_Y + GAP_3);
		ORIGINAL
		getch();
	}
	
	//레벨업 진행 :: 공통
	while (true)
	{
		if (winner->Get_NowEXP() >= winner->Get_MaxEXP())
		{
			winner->LevelUp(PLAYER_PLUS_MAXHP, PLAYER_PLUS_MAXEXP, PLAYER_PLUS_ATTACK);

			if (winner->Get_MonsterType() == MONSTER_NONE) //몬스터가 아닌 경우 == 플레이어인 경우
			{
				Interface::Print("Level + 1!"); //TODO::레벨업 시에 뜨는 문구 작성
				Interface::DrawInterface(player);
			}
		}
		else
			break;
	}
}



void GameManager::SavePrint(string _string)
{
	int Start_y = MAP_END_Y / GAP_3 * GAP_2;

	MapDraw::BoxErase(MAP_END_X, Start_y);
	GRAY
	MapDraw::DrawMidText(_string, MAP_END_X, MENUPRINT_START_Y + GAP_2);
	ORIGINAL

	switch (getch())
	{
	case MENU_m:	//간단한 현재 상황 브리핑과,캐릭터와 몬스터 정보,도감 확인
	case MENU_M:
		Menu();
		Interface::DrawInterface(player);
		break;
	default:
		break;
	}
}

void GameManager::SaveContinueCheck()
{ //게임 이어하기 선택지 개방
	ofstream save;
	save.open("SaveContinueCheck.txt");
	save << mShowContinueMenu;
	save.close();
}