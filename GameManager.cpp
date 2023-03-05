#include "GameManager.h"
//static_cast<��ȯ��>(��ȯ��) //�ٿ�ĳ����


GameManager::GameManager()
{
	system("mode con: cols=82 lines=25");

	int seed = time(NULL);
	srand(seed); // �õ尪�� ���忡�� ������ �� �ƴ϶�. srand�� ���Ǵ� �õ尪 �����ؾ� �ϴ� ��(�����Ҷ� ������ �õ尪�� �ýð��� �޶���)
	player.SetSeed(seed);

	mShowContinueMenu = false; //default�� ���� ���� �ϱ�
	battle = new Battle; //�����Ҵ���� ����� ��ü�� �ִ�.
}
GameManager::~GameManager()
{
}

void GameManager::CallMainMenu()
{
	ifstream load;

	load.open("SaveContinueCheck.txt"); //�̾��ϱ� üũ Ȯ�� bool�� �޾ƿ´�.(Player ������ ���� �̿ܿ� �̾��ϱ� �Ǵ� ������ ��� �ʿ�.)
	if (load.is_open())
	{
		load >> mShowContinueMenu;
		load.close();
	}

	while (MainMenu()) {}
}

bool GameManager::MainMenu()
{//default�� �����ϱ�.
	ifstream load;
	PrintXY printXY; 	
	printXY.Print_Y = MENUPRINT_START_Y; //�ݺ� �������� �ʱ�ȭ
	bool bContinueCheck = false; //default�� �����ϱ�.

	//�� ���� �׸���
	MapDraw::BoxDraw(MAP_START, MAP_START, MAP_END_X, MAP_END_Y);
	//�κ� â ����
	MapDraw::DrawMidText("�١� DonGeonRPG �ڡ�", MAP_END_X, printXY.Print_Y);
	MapDraw::DrawMidText("New Game", MAP_END_X, printXY.Print_Y += GAP_3);

	load.open("SavePlayerInfo.txt"); //�̾��ϱ� ���� ������ �ִ��� Ȯ���Ѵ�.
	if (load.is_open() && mShowContinueMenu) //������ ������ �׾ �̾��ϱ� �Ұ��� ��� �ִ�.
	{
		MapDraw::DrawMidText("Continue Game", MAP_END_X, printXY.Print_Y += GAP_3);
		load.close();

		bContinueCheck = true;
	}

	MapDraw::DrawMidText("Help", MAP_END_X, printXY.Print_Y += GAP_3);
	MapDraw::DrawMidText("Game Exit", MAP_END_X, printXY.Print_Y += GAP_3);


	if (bContinueCheck == false) //�����ϱ�
	{
		//ȭ��ǥ
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
	else //�̾��ϱ�
	{
		//ȭ��ǥ
		//  %��/��ȣ�� while���� �ݺ��ؼ� �� �� (ex.���� ������ ���� ����) �Ҹ�Ǵ� ����� ũ�Ƿ� *�� �����Ͽ� ����ϴ� ���� ���� (ex.*0.5)
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
	//�ݺ� �������� �ʱ�ȭ
	PrintXY printXY;
	printXY.Print_Y = MENUPRINT_START_Y;

	//�� ���� �׸���
	MapDraw::BoxDraw(MAP_START, MAP_START, MAP_END_X, MAP_END_Y);
	//�κ� â ����
	GRAY
	MapDraw::DrawMidText("�١� Help �ڡ�", MAP_END_X, printXY.Print_Y);
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
	player.GetMonsterBook()->ResetMonsterBook(); //���� ���� �ʱ�ȭ
	player.GetMonsterBook()->ReadMonsterBook(); //���� ���� �Ҹ��� �迭 �ʱ�ȭ

	monsterManager.CreateMonsterReset(); //�����Ǿ��ִ� ���� ����Ʈ �ʱ�ȭ
	monsterManager.ResetSaveMonstersTxt(); //���� ���� txt ���� ���� �ʱ�ȭ
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
		mSceneCheck = (SCENE)player.PlayeInitialSetting(false); //�ʱ� ���� X : ���� ���� �ʱ�ȭ + ���� ó������ �ϵ� �̸��� �����ǵ��� //�̸� ���� GameOver ���� ���� true�� false��
	else
		mSceneCheck = (SCENE)player.LoadPlayerInfo(); //�� ���� + �÷��̾� ���� ��������

	srand(player.GetSeed()); //���� �õ尪 ��� �´�.
	monsterManager.CreateMonsterReset(); //�����Ǿ��ִ� ���� ����Ʈ �ʱ�ȭ
	monsterManager.LoadMonsters(); //���� ���� ��������(���� ��ü�� ���� ����� �ؽ�Ʈ�� ���� �־��ִ� ���̶� ����Ʈ �ʱ�ȭ ���ϸ� ���� ���� ���� x2)
	player.GetMonsterBook()->ReadMonsterBook(); //���� ���� �Ҹ��� �迭 �ʱ�ȭ
	GameStart(mSceneCheck, MENUSELECT_CONTINUE);
}

void GameManager::GameStart(SCENE scene, MENUSELECT startType)
{
	//int deadMonster = 0;
	int randomScene;
	bool gameOverCheck = false;

	Interface::DrawInterface(player);

	//���� ��(�̺�Ʈ) �߻�
	while (true) 
	{
		switch (scene)
		{
		case SCENE_INTRO:
			Intro(); //�� ���� ����
		case SCENE_PICKUPWEAPON:
			PickUpWeapon(); //���� �ݱ�
		case SCENE_NAME: // �� ���߿� �ϰ�����. Print �Լ����� ������ �ʿ� ���� ������ ���� ���ϴ� Print �Լ��� ��ü
			if ((startType == MENUSELECT_NEW) || (player.Get_Name() == "???")) //�̸� ���� ���� �����ϸ� �̾��ϱ�� �÷��̾� �̸� ���� �ʿ�.
				Name(); //�̸� ���
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

		SavePrint("���ٶ��� ���ִ� ���� �ȱ� �����Ѵ�.");

		randomScene = SCENE(rand() % 10);

		if (randomScene >= 0 && randomScene < 6) //���� Ȯ���� �����ϸ� ���� ������ ����.
			scene = SCENE_MONSTER;
		else if (randomScene >= 6 && randomScene < 8) //���� ���� Ȯ��
			scene = SCENE_WEAPONSHOP;
		else if (randomScene >= 8 && randomScene < 10) //ȸ���� Ȯ��
			scene = SCENE_SPRINGOFRECOVERY;

		//LATER::���Ͱ� 5���� ������ ���� ������.
		////TODO::���� Ŭ���� ���� ���� �ٶ�.
		//if (deadMonster == 5)
		//{
		//	Print("���� ���⼭ ���ᰡ �ȴٰ� �ǽ����̴�.");
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
		//Todo : �����ϰ� ���� ��Ȳ �긮�� (��ȹ �³�Ʈ ����)


		MapDraw::BoxDraw(MAP_START, MAP_START, MAP_END_X, MAP_END_Y);
		MapDraw::DrawMidText("�÷��̾� ����", MAP_END_X, printXY.Print_Y += GAP_6);
		MapDraw::DrawMidText("���� ����", MAP_END_X, printXY.Print_Y += GAP_2);
		MapDraw::DrawMidText("����", MAP_END_X, printXY.Print_Y += GAP_2);
		MapDraw::DrawMidText("���ư���", MAP_END_X, printXY.Print_Y += GAP_2);
		//iMapDraw::DrawMidText("����", MAP_END_X, mPrint_Y += GAP_2);

		//ȭ��ǥ
		//  %��/��ȣ�� while���� �ݺ��ؼ� �� �� (ex.���� ������ ���� ����) �Ҹ�Ǵ� ����� ũ�Ƿ� *�� �����Ͽ� ����ϴ� ���� ���� (ex.*0.5)
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
	//�÷��̾� ���� ���� ���
	player.SavePlayerInfo(mSceneCheck, (mSceneCheck > SCENE_PICKUPWEAPON));//���⸦ ���ϰ� �ִ��� �Ǵ�.
	//������ ���� ���� ���
	monsterManager.SaveMonsters();
	//���� ���� ���� ���
	player.GetMonsterBook()->SaveMonsterBook();
	//���� �̾��ϱ� ������ ����
	mShowContinueMenu = true;
	SaveContinueCheck();
}

void GameManager::Intro()
{
	mSceneCheck = SCENE_INTRO;
	Interface::Print("............");
	Interface::Print("�ճ��� �����ϰ� ������� ������ ��������.");
	Interface::Print("���ڱ����� ���� ������ �� �� ���� å�� ���ƴ�..");
}

void GameManager::PickUpWeapon()
{
	mSceneCheck = SCENE_PICKUPWEAPON;
	Interface::Print("��ü�� ���̿��� �����ٴϴ� ���� �ϳ��� �ֿ���.");
	weaponShop.FirstWeapon(&player);
	Interface::DrawInterface(player);
}

void GameManager::Name()
{
	string _Name;

	mSceneCheck = SCENE_NAME;
	Interface::Print("Made in Dongeon.");
	Interface::Print("�� ���� �Ʒ��� �̸��� �����ִ�.");
	MapDraw::BoxErase(MAP_END_X, MAP_END_Y / GAP_3 * GAP_2);
	YELLOW
	MapDraw::DrawMidText("Player �̸� �Է� : ", MAP_END_X, MENUPRINT_START_Y + GAP_2);
	cin >> _Name;
	ORIGINAL
	player.SetName(_Name);
	Interface::DrawInterface(player); //�Է� â�� ��� ���ڸ� ���ִ� �뵵
	Interface::Print(_Name + "...");
}

void GameManager::WeaponShop()
{
	mSceneCheck = SCENE_WEAPONSHOP;
	SavePrint("������ ���� ������ ���Ű� ȯ���մϴ�.");
	weaponShop.Shop(&player);
	Interface::DrawInterface(player);
	SavePrint("���� �����մϴ�.");
}

void GameManager::SpringOfRecovery()
{
	mSceneCheck = SCENE_SPRINGOFRECOVERY;

	SavePrint("�̾��� �Һ��� ���δ�..");
	SavePrint("������ ���θ���.");
	SavePrint("�����̼� �� �Һ��� ���� �ݵ����̴�.");
	SavePrint("�ٰ������� ���� �������� �Һ��� ���󰡴� ������ ���� ���Դ�.");

	SavePrint("���� ���� ���ô� ���� ����������.");

	SavePrint("HP" + to_string(player.Recover()) + " ȸ��!");
	Interface::DrawInterface(player);

	SavePrint("�ݵ����̰� ��������.");
}

bool GameManager::Monster()
{
	//�÷��̾�� ���� �κ� �Լ�ȭ. �¸� üũ �κп����� Character�� ���Ϳ� �÷��̾�� ��� ���ڰ� ���������� ���� ������ �ֱ�.
	mSceneCheck = SCENE_MONSTER;

	Character* monster;
	WINCHECK whoWin;

	SavePrint("���͸� �����߽��ϴ�.");

	monster = battle->MeetMonster(&player, &monsterManager);
	whoWin = battle->BattleTurn(monster, &player, &monsterManager);

	//string���� ���ϴ� �ͺ��� enum���� �����ϱ�. �ƿ� �����ϰ� �÷��̾ ���� �¸�, �������� (�й�� ����� �¸��̹Ƿ� �й�X) 
	switch (whoWin)  //�¸�üũ
	{
	case WINCHECK_PLAYER_WIN:
	{ //�÷��̾ �¸�
		WinnerReward(WINCHECK_PLAYER_WIN, &player, monster);

		//�й��� ���� ����
		list<Character*>* monsterList = monsterManager.Get_MonsterList();
		for (list<Character*> ::iterator iter = monsterList->begin(); iter != monsterList->end();)
		{
			if (((*iter)->Get_MonsterType() == monster->Get_MonsterType()) && ((*iter)->Get_NowHP() == 0))
			{
				Character* c = (*iter); //list������ pop �ϰ� iter�� �Ҵ�� �޸𸮸� �����ؾ��� ��
				monsterList->erase(iter); //����Ʈ���� pop
				delete c; //iter�� �Ѿ�� ���� �������� �Ҵ�� �޸� ����
				break;
			}
			else
				iter++;
		}
		break;
	}
	case WINCHECK_PLAYER_RUNAWAY: //LATER::���� Ȯ���� ���� ������ ���� ����. ���ͺ�? ������? Ȯ���� ���̸� �д�.
	{ //�÷��̾ ����
		SavePrint("......");
		SavePrint("���Ϳ��Լ� ������ �����ƴ�.");
		break;
	}
	case WINCHECK_MONSTER_WIN: //���Ͱ� �¸�
	{
		WinnerReward(WINCHECK_MONSTER_WIN, monster, &player);

		//GameOver�� �÷��̾�� �̸��� GameOverCheck�� SavePlayerInfo.txt ���Ͽ� �����Ѵ�.
		player.SaveGameOverPlayerInfo();
		//������ ���� ���� ���
		monsterManager.SaveMonsters();
		//���� ���� ���� ���
		player.GetMonsterBook()->SaveMonsterBook();
		//���� �̾��ϱ� ������ ����
		mShowContinueMenu = true;
		SaveContinueCheck();
		return true;
	}
	case WINCHECK_MONSTER_RUNAWAY:
	{ //���Ͱ� ����
		SavePrint("......");
		SavePrint("��� ����� ����...");
		SavePrint("ƴ�� �븮�� �ִ� ���Ͱ� ��������.");
		break;
	}
	default:
		break;
	}

	//����, �ൿ, ����, ������ ��µ� �״�� �����ִ�.
	Interface::DrawInterface(player);
	return false;
}

void GameManager::WinnerReward(WINCHECK whoWin, Character* winner, Character* loser)
{
	if (whoWin == WINCHECK_PLAYER_WIN)
	{ //�÷��̾� �¸�
		SavePrint("WIN!");
		SavePrint("������ ����Ǿ����ϴ�.");
		SavePrint("������ ������ ���޵˴ϴ�.");

		player.GetMonsterBook()->RecodeMonsterBook(SITUATION_WIN, loser->Get_MonsterType()); //���� ���
	}
	else
	{ //���� �¸�
		MapDraw::BoxErase(MAP_END_X, MAP_END_Y / GAP_3 * GAP_2);
		RED
		MapDraw::DrawMidText("GAME OVER", MAP_END_X, MENUPRINT_START_Y + GAP_2);
		ORIGINAL
	}
	
	//���� ���� :: ����
	winner->Set_Gold(winner->Get_Gold() + loser->Get_Gold()); //���
	winner->Set_NowEXP(winner->Get_NowEXP() + loser->Get_GetEXP()); //EXP

	if (whoWin == WINCHECK_PLAYER_WIN)
	{ //�÷��̾� ���� ���
		string sTmp;

		Interface::DrawInterface(player);

		MapDraw::BoxErase(MAP_END_X, MAP_END_Y / GAP_3 * GAP_2);
		GOLD
		sTmp = "ȹ���� ����ġ : " + to_string(loser->Get_GetEXP());
		MapDraw::DrawMidText(sTmp, MAP_END_X, MENUPRINT_START_Y + GAP_2);
		sTmp = "ȹ���� ��� : " + to_string(loser->Get_Gold());
		MapDraw::DrawMidText(sTmp, MAP_END_X, MENUPRINT_START_Y + GAP_3);
		ORIGINAL
		getch();
	}
	
	//������ ���� :: ����
	while (true)
	{
		if (winner->Get_NowEXP() >= winner->Get_MaxEXP())
		{
			winner->LevelUp(PLAYER_PLUS_MAXHP, PLAYER_PLUS_MAXEXP, PLAYER_PLUS_ATTACK);

			if (winner->Get_MonsterType() == MONSTER_NONE) //���Ͱ� �ƴ� ��� == �÷��̾��� ���
			{
				Interface::Print("Level + 1!"); //TODO::������ �ÿ� �ߴ� ���� �ۼ�
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
	case MENU_m:	//������ ���� ��Ȳ �긮�ΰ�,ĳ���Ϳ� ���� ����,���� Ȯ��
	case MENU_M:
		Menu();
		Interface::DrawInterface(player);
		break;
	default:
		break;
	}
}

void GameManager::SaveContinueCheck()
{ //���� �̾��ϱ� ������ ����
	ofstream save;
	save.open("SaveContinueCheck.txt");
	save << mShowContinueMenu;
	save.close();
}