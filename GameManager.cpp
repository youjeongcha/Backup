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
		switch (UI.StartInterface(player)) //player ���۷����� ����
		{
		case STARTMENU_START:
			GameStart();
			break;
		case STARTMENU_RANK:
			//rank.RankPrint();
			UI.RankingInterface(rank.Get_RankingList(), (int)MAXRANK);
			UI.EnterNext(); //���ͷ� ���� ȭ�� �Ѿ�� //�� input Ŭ���� ���� ���� �ű⼭ ó��
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


	UI.MapInterface(); //��
	UI.PlayerInfoInterface(player); //�÷��̾� ���� �������̽� ���

	//�� �������̽����� ó��
	UI.SkipBox();

	//���丮 ��� + ��ŵ ���
	SKY_BLUE
	PrintStory(0, 0);
	ORIGINAL

	//<�̸� �Է� ��Ʈ>
	//��
	UI.MapInterface();
	//�� ��ǲ Ŭ����
	//�̸� �Է� �ڽ�
	SKY_BLUE
	MapDraw::BoxDraw(INPUTBOX_START_X, INPUTBOX_START_Y, INPUTBOX_WIDTH, INPUTBOX_HEIGHT);
	MapDraw::DrawMidText("�̸� �Է�", MAPSIZE_END_X, INPUTBOX_START_Y - 3);
	ORIGINAL
	//���ڿ� �Է� //�� ��ǲ���� �Է��� �ް� input�ڽ��� �װ� ȣ���ؼ� ����ؾ� �ߴ�.
	while (UI.InputBox(INPUTBOX_PRINTNAME_MAXCOUNT, sInput, 0)) {}
	//�̸� ����
	player.Set_PlayerName(sInput);


	UI.MapInterface(); //��
	UI.PlayerInfoInterface(player); //�÷��̾� ���� �������̽� ���


	//�������� (���ڰ� �޴� �� ���� ���� ���� �ٸ���)
	while (true)
	{
		//Stage���� ����� ���ϱ� ���� ���� �̻��� ���� ȹ���ϸ� true ���� ���������� �̵�
		if (Stage(stageLevel++))
		{ //Stage�� true�� ���� ��������

			//stage�� �ִ� 6�����ε� 6������ true�� ���� �ʴ´�. ������ ����
			//if (stageLevel > STAGELEVEL_6)
			//	break;

			//stage ����ϸ� player�� score �ʱ�ȭ
			player.Set_PlayerScore(0);
			//������ �ܾ� ����Ʈ �ʱ�ȭ
			wordManager.RestList();
			UI.MapInterface(); //��
			UI.PlayerInfoInterface(player); //�÷��̾� ���� �������̽� ���
		}
		else
		{ //Stage�� false�� ���� ����
			int line = 0, maxLine, oldClock = 0;
			std::string gameEndText = "";
			std::vector<std::string> gameOverStoryList = storyList[STORYTYPE_GAMEOVER];

			//�� switch�� ó��
			switch (stageLevel - 1)
			{
			case STAGELEVEL_6:
				maxLine = GAMEOVERSTORY_6;
				gameEndText = "�� G A M E  C L E A R ��";
				break;
			default:
				maxLine = GAMEOVERSTORY_1_5;
				gameEndText = "�� G A M E  O V E R ��";
				break;
			}

			//������ ��������.(������ ��������) ����
			while (line < maxLine)
			{
				if (kbhit())
					getch();

				//���� ���丮 ���پ� ���. ������ �ð� �̻� ��ٸ��� ��µȴ�.
				if (clock() - oldClock >= PRINTDELAY)
				{
					RED
					if (stageLevel - 1 == STAGELEVEL_6) //����::������ ���� ���� ���̳���.
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

			//��ŷ ���� + ����
			rank.SaveSortRanking(stageLevel, player.Get_PlayerName(), player.Get_PlayerScore());

			//�÷��̾� + ������ �ܾ� ����Ʈ �ʱ�ȭ
			player.InitalSetting();
			wordManager.RestList();

			UI.EnterNext(); //���ͷ� ���� ȭ�� �Ѿ��
			break;
		}
	}
}

void GameManager::PrintStory(int printLineCount, int oldClock)
{//�������� �������� �޸𸮰� �׿��� ū ������ ���� ��� �����÷ο찡 �����⵵ �Ѵ�. 
	//������ ������ ������ �Ǹ� ���. ���� ���� ����� �ϸ� ����
	std::vector<std::string> intoStoryList = storyList[STORYTYPE_INTRO];

	//���丮 ���� ��� ������ ����
	if (mStoryLineCount == printLineCount)
		return;

	//Sleep(1000); //1�� ������ //Slepp ��� Clock���� ���. ����ð� �˷���. //Sleep�� ���α׷� ��ü�� ������Ų��.

	while (clock() - oldClock < PRINTDELAY)
	{//while�� ���� �� �ɾ�θ� ���� ��� �Ѿ�鼭 ������ �����. ������ �������� ���ϸ� ���ڰ� ������ ������ ����.
		//��ŵ
		if (kbhit())
		{//Ű���� �Է��� ������ ��ŵ Ȯ��
			if (getch() == 's')
				return;
		}
	}

	if (printLineCount < STRORYLINE_MAX) //��� 10�� �� �Ѱ�
		MapDraw::DrawMidText(intoStoryList[printLineCount], MAPSIZE_END_X, STORYLINE_Y + printLineCount);
	else
	{//10�� ������ ��ü �ٽ� ���
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

	//�̹� ������ ���丮 �ѹ��� ��� //2~6���� ���̿��� ���� //������ �� 1~5���� ������ ��
	if (level != 1)
	{
		for (int writtenPrint = 1; writtenPrint < level; writtenPrint++)
		{ //������ �۹�ġ ����

			for (int line = 0; line < STAGESTROY_LINECOUNT; line++)
			{
				MapDraw::DrawPoint(stageStoryList[(writtenPrint - 1) * STAGESTROY_LINECOUNT + line], storyLine_X[(writtenPrint - 1) & 1], 9 + (writtenPrint - 1) / 2 * STAGESTROY_PRINTGAP_Y + line);
			}
		}
	}

	//�÷��̾ ž �ö󰡴� �������� Ȯ�� ������ �׸� �׸���.
	UI.PrintStageStairs((STAGELEVEL)level);

	//�ش� ������ �ۼ��ϴ� ���丮 ���پ� ���
	while (line < maxPrintLine) //�� ���� enum ���� ���� �迭 size�� �ڵ�ȭ
	{
		if (kbhit())
			getch();

		if (clock() - oldClock >= PRINTDELAY)
		{//��Ʈ ����
			MapDraw::DrawPoint(stageStoryList[startIndex + line++], storyLine_X[Odd_Or_Even_Level], storyLine_Y + line);
			oldClock = clock();
		}
	}

	UI.EnterNext(); //���ͷ� ���� ȭ�� �Ѿ��
}

bool GameManager::Stage(int level)
{
	STAGESETTING stageSetting = mStageSetting[level - 1];
	//int createSpeed, dropSpeed, clearStage, usedItem_UsingTime;
	int  usedItem_UsingTime;
	int create_OldClock = 0, drop_OldClock = 0, failed_OldClock = 0, usedItem_OldClock = 0;
	std::string inputWord = "";
	bool returnOriginSpeedCheck = false, hideWordCheck = false; //���� ������ ������ �۵�
	ITEM usedItem = ITEM_NONE;

	SKY_BLUE
	MapDraw::DrawMidText("�� " + std::to_string(level) + " stage ��", MAPSIZE_END_X, STAGE_TEXTPRINT_Y);

	create_OldClock = clock();

	while (true) //stage ǥ�� �߰� ��� �ڿ� ��µǵ���
	{
		if (clock() - create_OldClock > PRINTDELAY)
			break;
	}

	//�������̽� ������
	UI.MapInterface(); //��
	SKY_BLUE
	MapDraw::DrawVerticalLine(); //�� ������
	ORIGINAL

	//���丮 ���� + �÷��̾ ž �ö󰡴� �������� Ȯ�� ������ �׸� �׸���.(�������Լ� ����)
	PrintStageStory(level);

	//���� ����â ����
	UI.MapInterface(); //��
	SKY_BLUE
	MapDraw::BoxDraw(INPUTBOX_START_X, INPUTBOX_START_Y, INPUTBOX_WIDTH, INPUTBOX_HEIGHT); //word �Է� �ڽ�
	ORIGINAL
	

	//���� ����
	while (true)
	{
		//if (clock() - failed_OldClock >= 3000) //Input Ʋ������ ��ð� Input ����.
		//�ܾ� Input ���� + failed ���� ��쿡 ��� �ð�����(InputBox())
		if (UI.InputBox(INPUTBOX_PRINTWORD_MAXCOUNT, inputWord, failed_OldClock) == false) //false�� ���͸� �����ٴ� �ǹ�
		{
			//Word* deleteWord = NULL;//�����ͷ� �����Ǿ�� �� �ܾ� �ּ� �����ͼ� �� ��.

			//�ܾ� ������� Ʋ�ȴ��� Ȯ�� + ����ٸ� ���� �ܾ��� ������ Ÿ�� ��ȯ(�Ϲ��� �븻). �ƴϸ� ITEM_NONE
			usedItem = wordManager.TypingCheck(&inputWord);

			//�ܾ� ������ ��� ���� ���� + ������ �۵�
			if (usedItem != ITEM_NONE)
			{ 
				player.Set_PlayerScore(player.Get_PlayerScore() + inputWord.size() * 3); //word ���ڴ� 3�� ���
				UI.PlayerInfoInterface(player); //�÷��̾� ���� �������̽� ���
				
				//������ �۵�(�Ϲ� �ܾ�� �ȿ��� �ɷ�����.) + �ܾ� ����
				wordManager.ItemOperate(usedItem, stageSetting.createSpeed, stageSetting.dropSpeed, usedItem_UsingTime);

				//�Է�â�� �ִ� ���� �����ص� �� ����
				inputWord.clear();

				//������ �����̻� �ٴٸ��� ���� ����������.
				if ((level != STAGELEVEL_6) && (player.Get_PlayerScore() >= stageSetting.clearStage)) //6���������� ������ ����. ��ŷ�� �ϰ� Ŭ���� �Ѱ� ���� x
					return true;
			}
			else
			{ //�ܾ� Ʋ���� ��� failed ���
				RED
				MapDraw::DrawMidText("     Failed Compare!!     ", MAPSIZE_END_X, INPUTBOX_PRINT);
				ORIGINAL

				inputWord.clear();
				failed_OldClock = clock(); //��ð� Input ����.
			}
		}
		//else if (kbhit()) getch();

		//�ð� �����ϴ� ������ �۵� ���� �ð� �����α� ����
		if ((usedItem != ITEM_NONE) && (usedItem != ITEM_NOMAL) && (usedItem != ITEM_SCREEN_CLEAR))
		{
			usedItem_OldClock = clock();
			returnOriginSpeedCheck = true; //������ ����ϰ� �ð� ���� ������� �����α� �� ����.

			//���� ������ ������ �۵�
			if (usedItem == ITEM_HIDE)
			{
				hideWordCheck = true;

				//������ ��� ��� "===="���� ��ȯ��Ű�� ���� (drop������ �ܾ �������ְ� �־. �̷��� �� �ϸ� �ѹ� �������� ������ ����ȴ�.)
				//���� �������� ����ϴ� �Լ�������. y-�� ����� y�� ����ؼ� ���⼭ ����ص� ���� ����.
				wordManager.DropWordPrint(hideWordCheck);
			}

			usedItem = ITEM_NOMAL; //�۵� �ð� ���� �� if�� ������ �ʵ��� �ʱ�ȭ
		}

		//�� ���� ����ü �迭�� �ذ�
		//�ð� ������
		if ((returnOriginSpeedCheck) && (clock() - usedItem_OldClock >= usedItem_UsingTime))
		{
			stageSetting = mStageSetting[level - 1];

			returnOriginSpeedCheck = false;
			hideWordCheck = false;
		}


		//�ܾ� ����
		if (clock() - create_OldClock >= stageSetting.createSpeed)
		{//���� �� ���������� ����
			wordManager.CreateWord(hideWordCheck);
			create_OldClock = clock();
		}

		//�ܾ� ����߸���
		if (clock() - drop_OldClock > stageSetting.dropSpeed)
		{
			if (wordManager.DropWord(player.Get_PlayerLife())) //���� XY��ǥ �ű�� + ��� ���� bool üũ
			{
				wordManager.DropWordPrint(hideWordCheck);//GmaeOver �ϰ� �ܾ� �ߵ���
				player.DecreasePlayerLife();
				UI.PlayerInfoInterface(player); //�÷��̾� ���� �������̽� ���

				SKY_BLUE
				MapDraw::BoxDraw(INPUTBOX_START_X, INPUTBOX_START_Y, INPUTBOX_WIDTH, INPUTBOX_HEIGHT); //word �Է� �ڽ� �� ��������(���� X)
				ORIGINAL

				//���� ���� üũ
				if (player.Get_PlayerLife() == 0)
					return false;
			}

			//���� �������� ���
			wordManager.DropWordPrint(hideWordCheck);

			drop_OldClock = clock();

			SKY_BLUE
			MapDraw::BoxDraw(INPUTBOX_START_X, INPUTBOX_START_Y, INPUTBOX_WIDTH, INPUTBOX_HEIGHT); //word �Է� �ڽ�

			//�ܾ �������� �ʵ���
			if ((usedItem == ITEM_NONE) && (drop_OldClock - failed_OldClock < INPUTBOX_DELAY)) //failed �����϶��� failed ���� ���
			{//3�ʰ� ������ ������ ��� ���;� �Ѵ�. //drop-OldClock�� �� ���� > clock() ȣ�� �ٷ� ���� �ؼ� �� �� �ʿ�X
				RED
				MapDraw::DrawMidText("     Failed Compare!!     ", MAPSIZE_END_X, INPUTBOX_PRINT);
				ORIGINAL
			}
			else
			{
				ORIGINAL
				MapDraw::DrawMidText(inputWord, MAPSIZE_END_X, INPUTBOX_PRINT);
			}

			//���� �ʰ� ����Ʈ
			if (inputWord.size() >= INPUTBOX_PRINTWORD_MAXCOUNT)
			{
				SKY_BLUE
				MapDraw::DrawMidText(std::to_string(INPUTBOX_PRINTWORD_MAXCOUNT) + "���� �ʰ�!!", MAPSIZE_END_X, INPUTBOX_START_Y - 2);
				ORIGINAL
			}
		}
	}
}

int GameManager::LoadStory()
{
	int lineCount = 0;
	std::string storyTmp;
	std::vector<std::string> tmpStoryList; //�� into,stage, gameOver�� enum���� �Ǵ��ؼ�. ���� �迭�� ȣ���ؼ� ��� 
	//std::vector<std::string> stageStoryList;
	//std::vector<std::string> gameOverStoryList;

	std::ifstream load;

	//�� �̸� ���� Save��� �ϸ� ����Ǵ� �����ͷ� ���صȴ�.
	load.open("StageStory.txt");
	if (load.is_open())
	{
		for (int i = 0; i < STAGELEVEL_6; i++)
		{
			//load >> storyTmp; //txt ���Ͽ� ���� ���� �ۼ��صа�. �ǹ�X ���X
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
	//�� 
	load.open("GameOverStory.txt");
	if (load.is_open())
	{
		for (int i = 0; i < 2; i++)
		{
			if (i == 0) //1~5���� GameOver ���� �� ���丮 �� �� 
				lineCount = GAMEOVERSTORY_1_5;
			else //6���� GameOver ���� �� ���丮 �� ��
				lineCount = GAMEOVERSTORY_6;
			//load >> lineCount; //txt ���� 1~5����, 6���� ���ڼ� ���� ���� �ۼ��صа�
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
	//�� 
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
			//MapDraw::DrawMidText("�����簡 �����ߴ� �ð��� ���� �װ� ž ���� ��Ÿ�����ϴ�.", MAPSIZE_END_X, STAGE_TEXTPRINT_Y + 4);
			mStageSetting[setLevel].createSpeed = CREATEWORD_SPEED_STAGE1;
			mStageSetting[setLevel].dropSpeed = DROP_SPEED_STAGE1;
			mStageSetting[setLevel].clearStage = CLEARSTAGE_1;
			break;
		case STAGELEVEL_2:
			//MapDraw::DrawMidText("���� 2 ���� ����", MAPSIZE_END_X, STAGE_TEXTPRINT_Y + 4);
			mStageSetting[setLevel].createSpeed = CREATEWORD_SPEED_STAGE2;
			mStageSetting[setLevel].dropSpeed = DROP_SPEED_STAGE2;
			mStageSetting[setLevel].clearStage = CLEARSTAGE_2;
			break;
		case STAGELEVEL_3:
			//MapDraw::DrawMidText("���� 3 ���� ����", MAPSIZE_END_X, STAGE_TEXTPRINT_Y + 4);
			mStageSetting[setLevel].createSpeed = CREATEWORD_SPEED_STAGE3;
			mStageSetting[setLevel].dropSpeed = DROP_SPEED_STAGE3;
			mStageSetting[setLevel].clearStage = CLEARSTAGE_3;
			break;
		case STAGELEVEL_4:
			//MapDraw::DrawMidText("���� 4 ���� ����", MAPSIZE_END_X, STAGE_TEXTPRINT_Y + 4);
			mStageSetting[setLevel].createSpeed = CREATEWORD_SPEED_STAGE4;
			mStageSetting[setLevel].dropSpeed = DROP_SPEED_STAGE4;
			mStageSetting[setLevel].clearStage = CLEARSTAGE_4;
			break;
		case STAGELEVEL_5:
			//MapDraw::DrawMidText("���� 5 ���� ����", MAPSIZE_END_X, STAGE_TEXTPRINT_Y + 4);
			mStageSetting[setLevel].createSpeed = CREATEWORD_SPEED_STAGE5;
			mStageSetting[setLevel].dropSpeed = DROP_SPEED_STAGE5;
			mStageSetting[setLevel].clearStage = CLEARSTAGE_5;
			break;
		case STAGELEVEL_6:
			//MapDraw::DrawMidText("���� 6 ���� ����", MAPSIZE_END_X, STAGE_TEXTPRINT_Y + 4);
			mStageSetting[setLevel].createSpeed = CREATEWORD_SPEED_STAGE6;
			mStageSetting[setLevel].dropSpeed = DROP_SPEED_STAGE6;
			//clearStage = CLEARSTAGE_6;
			break;
		}
	}
}