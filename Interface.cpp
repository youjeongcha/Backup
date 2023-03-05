#include "Interface.h"

void Interface::EnterNext()
{
	while (true)
	{
		if (getch() == INPUTBOX_ENTER)
			break;
	}
}
//�� const ����Ҷ��� ������ �������� const�� ������ �Ǿ��־�� �Ѵ�.(��)
int Interface::StartInterface(const Player& player)
{ //���� ���� ȭ��
	MapInterface();
	PlayerInfoInterface(player); //�÷��̾� ���� �������̽� ���
	
	SKY_BLUE
	MapDraw::DrawMidText("�� �� �� �� ġ �� �� ��", MAPSIZE_END_X, STARTMENU_Y_GAMENAME);
	MapDraw::DrawMidText("1.Game Start", MAPSIZE_END_X, STARTMENU_Y_START);
	MapDraw::DrawMidText("2.Rank", MAPSIZE_END_X, STARTMENU_Y_RANK);
	MapDraw::DrawMidText("3,Exit", MAPSIZE_END_X, STARTMENU_Y_EXIT);
	ORIGINAL

	return MapDraw::MenuSelectCursor(STARTMENU_EXIT, GAP_4, STARTMENU_SELECT_X, STARTMENU_Y_START);
}

void Interface::MapInterface()
{ //���� �� �׸��� 
	SKY_BLUE
	MapDraw::BoxDraw(MAPSIZE_SART_X, MAPSIZE_SART_Y, MAPSIZE_END_X, MAPSIZE_END_Y);
	ORIGINAL
}

void Interface::SkipBox()
{
	SKY_BLUE //��ŵ �ڽ� �׸���
	MapDraw::BoxDraw(INPUTBOX_START_X, INPUTBOX_START_Y, INPUTBOX_WIDTH, INPUTBOX_HEIGHT);
	MapDraw::DrawMidText("Skip : s", MAPSIZE_END_X, INPUTBOX_PRINT);
	ORIGINAL
}

/*
void Interface::MapInterface(int playerLife)
{ //���� �� �׸��� 
	//�÷��̾� ����� ���� ���ϸ� �� �� �Ӱ� ����
	if (playerLife > MAXLIFE * 0.5f) //f �� ���̸� double���� �Ǵµ� double�� float���� ���� �ӵ� ������.
		SKY_BLUE
	else
		RED

	MapDraw::BoxDraw(MAPSIZE_SART_X, MAPSIZE_SART_Y, MAPSIZE_END_X, MAPSIZE_END_Y);
	ORIGINAL
}*/

//�� const ����Ҷ��� ������ �������� const�� ������ �Ǿ��־�� �Ѵ�.(��)
void Interface::PlayerInfoInterface(const Player& player)
{ //�÷��̾� ���� �������̽� ���
	std::string tmpString;
	
	//��� ǥ��
	MapDraw::DrawPoint("                                    ", PLAYERINTERFACE_X_LIFE, PLAYERINTERFACE_Y);
	tmpString = "Life :";
	//�� word���� �����̴ּ���� �ƿ� maxLife�� string���� �� �޾� �ΰ� �ϳ��� ����� ��������. ������Ҵ� �׷���. (�Ʊ� �װ� ���ڿ����� ������ Ȯ���ʿ�)
	for (int i = 0; player.Get_PlayerLife() > i; i++) //player�� ����� player���� �޾ƿͼ� ó��
		tmpString += " ��";

	RED
	MapDraw::DrawPoint(tmpString, PLAYERINTERFACE_X_LIFE, PLAYERINTERFACE_Y);
	//���� ǥ��
	MapDraw::DrawMidText("  Score : " + std::to_string(player.Get_PlayerScore()) + "  ", MAPSIZE_END_X, PLAYERINTERFACE_Y);
	//�̸� ǥ��
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
	MapDraw::BoxDraw(INPUTBOX_START_X, MAPSIZE_SART_Y + 1, INPUTBOX_WIDTH, INPUTBOX_HEIGHT); //word �Է� �ڽ�
	MapDraw::DrawMidText("Ranking", MAPSIZE_END_X, INPUTBOX_HEIGHT);
	MapDraw::DrawMidText("=================================================================================================================================================== ", MAPSIZE_END_X, INPUTBOX_HEIGHT + 3);
	MapDraw::DrawMidText("Name                    Score                    Stage", MAPSIZE_END_X, playerRank_Y++);


	for (int i = 0; i < rankingList.size(); i++)
	{
		if (i == maxRanking) //�ִ� 10�� ���
			break;

		MapDraw::DrawPoint(rankingList[i].name, RANKINGPRINT_X_NAME, playerRank_Y);
		MapDraw::DrawPoint(std::to_string(rankingList[i].score), RANKINGPRINT_X_SCORE, playerRank_Y);
		MapDraw::DrawPoint(std::to_string(rankingList[i].level), RANKINGPRINT_X_LEVEL, playerRank_Y++);
	}

	ORIGINAL
}

// ���۷����� ���
bool Interface::InputBox(INPUTBOX sMaxCount, std::string& sInput, int failed_OldClock)
{
	int stringTmp = 0;

	if (kbhit())
	{
		//���� �����߿� Input Ʋ������ ��ð� Input ����.
		if ((sMaxCount == INPUTBOX_PRINTWORD_MAXCOUNT) && (clock() - failed_OldClock < INPUTBOX_DELAY)) //3�� ���� ���ƾ� �ϹǷ�
		{
			getch();
			return true;
		}
		
		stringTmp = getch();

		switch (stringTmp)
		{
		case INPUTBOX_SPACE: //�����̽�
			return true;
		case INPUTBOX_BACKSPACE: //�齺���̽�
			if (sInput.empty()) //�ĵ� ���� ���� ���� ����
				return true;
			else if (sInput.size() >= sMaxCount)
				MapDraw::DrawMidText("                      ", MAPSIZE_END_X, INPUTBOX_START_Y - 2);

			//���� ���� üũ
			sInput.pop_back();
			MapDraw::DrawMidText("                      ", MAPSIZE_END_X, INPUTBOX_PRINT);
			MapDraw::DrawMidText(sInput, MAPSIZE_END_X, INPUTBOX_PRINT);
			return true;
		case INPUTBOX_ENTER: //����

			if (sInput.empty()) //�ĵ� ���� ���� ���� ���� ����
				return true; //while�� ��� ����
			else if (sInput.size() >= sMaxCount)
				MapDraw::DrawMidText("                      ", MAPSIZE_END_X, INPUTBOX_START_Y - 2); //�ִ� ���ڼ� ������ ��� ����

			MapDraw::DrawMidText(sInput, MAPSIZE_END_X, INPUTBOX_PRINT);

			return false; //while�� Ż��
		default: //���� �Է� �ޱ�

			if ((stringTmp >= 'a') && (stringTmp <= 'z'))
			{
				if (sInput.size() < sMaxCount)
				{
					sInput += stringTmp; //�Ϲ� ���ڸ� �Է� ���ڿ��� �߰�
					MapDraw::DrawMidText("                      ", MAPSIZE_END_X, INPUTBOX_PRINT); //���� �߰��Ǳ� ���� ����Ʈ �����

				}
				if (sInput.size() >= sMaxCount)
				{
					SKY_BLUE
					MapDraw::DrawMidText(std::to_string(sMaxCount) + "���� �ʰ�!!", MAPSIZE_END_X, INPUTBOX_START_Y - 2);
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
	MapDraw::DrawVerticalLine(); //�� ������

	//��� �׸���
	for (int stage = STAGELEVEL_1, stairs = 0; stage <= STAGELEVEL_6; stage++)
	{
		GRAY
		//and ��Ʈ ������ ���� ���� bit�� ��� 1(true) �̸� 1, �� �߿� �ϳ��� 1�� �ƴϸ� 0�� ��Ÿ����.
		//Ȧ���� true ¦���� false > Ȧ���� 1, ¦���� 0�� ��Ÿ���� �̰��� ��Ʈ �����ڷ� 1�� �� > �Ѵ� 1�̸� 1(true)�� ��ȯ�Ѵ�.
		if (stage & 1)//% ������ �ִ��� ���� �ʴ� ������� ���. ������ �Լ�ȭ �ϱ� ����� �������� �ɰ��ϰ� ������ ���, ���� ��� �̷� ��� �׳� ���
		{//Ȧ���� �ö󰡴� ���
			for (int x = 0; x < 5; x++)
				MapDraw::DrawPoint("  ��", STAGEPRINT_STAIRS_X + x * 3 + 3, MAPSIZE_END_Y - stairs++);
		}
		else
		{//¦���� �ö󰡴� ���
			for (int x = 1; x < 5; x++)
				MapDraw::DrawPoint("��  ", MAPSIZE_END_X - x * 3 - 3, MAPSIZE_END_Y - stairs++);
		}
		
		//������ ��ġ �׸���
		if (stage == STAGELEVEL_6)
			MapDraw::DrawPoint("��", MAPSIZE_END_X - 15, MAPSIZE_END_Y - stairs);
	}


	//���� ������ ���������� ���ϱ� ����. �÷��̾� ���� ��ġ ��ǥ�� �̵���ų��.
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

	//�÷��̾� ���� ��ġ ��ǥ �׸���
	MapDraw::DrawPoint("��", player_X, player_Y);
	oldClock = clock();

	//and ��Ʈ ������ ���� ���� bit�� ��� 1(true) �̸� 1, �� �߿� �ϳ��� 1�� �ƴϸ� 0�� ��Ÿ����.
	//Ȧ���� true ¦���� false > Ȧ���� 1, ¦���� 0�� ��Ÿ���� �̰��� ��Ʈ �����ڷ� 1�� �� > �Ѵ� 1�̸� 1(true)�� ��ȯ�Ѵ�.
	OddCheck = stageLevel & 1;

	//�÷��̾� ���� ��ġ > �������� ���� ��� �̵�
	while (true)
	{
		if (4 == countMove) // == �ƴϸ� ������ �ߴϱ� �Ǽ� ���� �� �ִ�.
			break;

		if (clock() - oldClock >= PRINTDELAY_PLAYER)
		{
			MapDraw::DrawPoint("  ", player_X, player_Y);
			
			//%������ �Ⱦ��� �ߺ� �ڵ� ���Բ� ���� �Ϸ�
			if (OddCheck) //Ȧ�� ����. ������ �̵�
				player_X += 3;
			else //¦�� ����. ������ �̵�
				player_X -= 3;

			MapDraw::DrawPoint("��", player_X, player_Y -= 1);

			countMove++;
			oldClock = clock();
		}
	}
}