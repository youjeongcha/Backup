#include "Battle.h"
//#include "GameManager.h" //Print�� DrawInterface ���
#include "MonsterBook.h"

Battle::Battle()
{
	entityBody.CreateEntityBody();
}
Battle::~Battle(){}



Character* Battle::MeetMonster(Player* player, MonsterManager* monsterManager)
{
	MONSTER monsterEnum = RandomMonsterEnum();
	list<Character*> monsterList = *monsterManager->Get_MonsterList(); //����Ʈ�� ������ ���� �������� ����

	//monsterList �Ź� ã�� �ʾƵ� �ǵ��� �̸� ã�Ƶд�.
	for (list<Character*> ::iterator iter = monsterList.begin(); iter != monsterList.end(); iter++)
	{
		if (monsterEnum == (*iter)->Get_MonsterType())
		{
			MapDraw::BoxErase(MAP_END_X, MAP_END_Y / GAP_3 * GAP_2);

			BattleMonsterInfo(player, (*iter)->Get_MonsterType(), SITUATION_MEET, *(*iter)); //���� ����, ��¸�.
			//TODO::���ͺ� ���� �ൿ �ٸ���
			PrintDescription("���� ����ġ�� �ִ�.");// ��ȭ�� ã�� �ִ�.");

			return (*iter);
		}
	}

	//���Ͱ� ����Ʈ�� �������� ������
	monsterManager->MonsterCreate(monsterEnum); //���� ���� ����Ʈ�� ����
	monsterList = *monsterManager->Get_MonsterList(); //���� ����Ʈ ����

	MapDraw::BoxErase(MAP_END_X, MAP_END_Y / GAP_3 * GAP_2);
	BattleMonsterInfo(player, monsterEnum, SITUATION_MEET, *monsterList.back()); //���� ����, ��¸�.
	PrintDescription("���� ����ġ�� �ִ�."); //��ȭ�� ã�� �ִ�.");

	return monsterList.back();
}

MONSTER Battle::RandomMonsterEnum()
{
	int randomMonster = rand() % MONSTER_COUNT;
	return (MONSTER)randomMonster;
}

WINCHECK Battle::BattleTurn(Character* monster, Player* player, MonsterManager* monsterManager)
{ //�������� ���� ����. ���� Ȯ�α��� ���ѷ��� �Լ�.
	WINCHECK whoWin;
	
	while (true)
	{
		//�÷��̾� ��
		//���� : �÷��̾� -> ���(�ΰ���)
		whoWin = PlayerTurn(player, monster->Get_EntityType(), monster, monsterManager->Get_MonsterInfoList());
		BattleMonsterInfo(player, monster->Get_MonsterType(), SITUATION_MEET, *monster); //���� ����, ��¸�.
		getch();

		//���� Ȯ��
		if ((whoWin == WINCHECK_PLAYER_WIN) || (whoWin == WINCHECK_PLAYER_RUNAWAY))
			return whoWin;


		//���� ��
		//���� : ��� -> �÷��̾�(�ΰ���)
		whoWin = MonsterTurn(player, monster->Get_EntityType(), monster);

		//�÷��̾� �ϴ�â ���� ����
		//TODO::���� �۵� Ȯ���ϰ� ���� �ڵ� �÷��̾� â ����� �� ���� player�� ���̸� ���ܵα�.
		MapDraw::BoxDraw(MAP_START, MAP_START, MAP_END_X, MAP_END_Y);
		MapDraw::BoxSectorDraw(MAP_END_X, MAP_END_Y, MAP_END_X, MAP_END_Y);
		Interface::UnderInfo(*player);
		BattleMonsterInfo(player, monster->Get_MonsterType(), SITUATION_FIGHT, *monster);
		///�������///

		//���� Ȯ��
		if ((whoWin == WINCHECK_MONSTER_WIN) || (whoWin == WINCHECK_MONSTER_RUNAWAY))
			return whoWin;
	}

	//whoWin.name = " ";
	return WINCHECK_NOTHING;
}

WINCHECK Battle::PlayerTurn(Player* player, ENTITYTYPE entityType, Character* monster, vector<Character*> monsterBook)
{ //�÷��̾� -> ���(�ΰ���)
	WINCHECK whoWin;

	//whoWin.name = player->Get_Name();

	switch (SelectAction()) //����, �ൿ, ����, ���� ����
	{
	case BATTLEOPTIONS_ATTACK:
		BattleMonsterInfo(player, monster->Get_MonsterType(), SITUATION_FIGHT, *monster); //���� â ���� ����
		whoWin = PlayerAttack(player, entityType, monster);
		break;
	case BATTLEOPTIONS_ACTION: //LATER::�ൿ�� �پ�ȭ �ʿ�.
		PrintDescription("���濡 ������ �ɸ��� �� ������...!"); getch();
		PrintDescription("���ʹ� ����� ��ٷ����� �ʴ´�.");
		whoWin = WINCHECK_NOTHING;
		break;
	case BATTLEOPTIONS_BAG: //LATER::�κ��丮 ��� ����
		PrintDescription("���濡�� �����ۿ� ����."); getch();
		PrintDescription("�� �� �ִ� �� ���� ���� �Źۿ� ����."); getch();
		MapDraw::DrawMidText("                                                                        ", MAP_END_X, MENUPRINT_START_Y + GAP_3);
		//player->GetMonsterBook()->ReadMonsterBook(); //"SaveMonsterBook.txt"�� �ִ� bool�� �о�´�.
		player->PrintMonsterBook(monsterBook); //���� �����߿� ���� ���� ���
		getch();
		MapDraw::BoxErase(MAP_END_X, MAP_END_Y / GAP_3 * GAP_2);
		/*MapDraw::BoxDraw(MAP_START, MAP_START, MAP_END_X, MAP_END_Y);
		MapDraw::BoxSectorDraw(MAP_END_X, MAP_END_Y, MAP_END_X, MAP_END_Y);
		player->UnderInfo();*/
		whoWin = WINCHECK_NOTHING;
		break;
	case BATTLEOPTIONS_ESCAPE:
		PrintDescription("����� �� ������? ���Ͱ� �� ������?");
		whoWin = WINCHECK_PLAYER_RUNAWAY;
		break;
	}
	return whoWin;
}

int Battle::SelectAction()
{
	int select;

	MapDraw::DrawMidText("����", (MAP_END_X - GAP_9) * 2, MAP_END_Y - GAP_6);
	MapDraw::DrawMidText("�ൿ", (MAP_END_X - GAP_4) * 2, MAP_END_Y - GAP_6);
	MapDraw::DrawMidText("����", (MAP_END_X - GAP_9) * 2, MAP_END_Y - GAP_4);
	MapDraw::DrawMidText("����", (MAP_END_X - GAP_4) * 2, MAP_END_Y - GAP_4);

	select = MapDraw::MenuSelectCursor_XY((BATTLEOPTIONS_END - 1) / 2, (BATTLEOPTIONS_END - 1) / 2, GAP_5, GAP_2, MAP_END_X - GAP_12, MAP_END_Y - GAP_6);

	return select;
}

WINCHECK Battle::PlayerAttack(Player* player, ENTITYTYPE entityType, Character* monster)
{ //�÷��̾� -> ���� ����
	int attackSelect;

	//4������ ���� Ȯ�� ������ ����
	RandomBodyPartsSetting(entityType);
	MapDraw::DrawMidText(m_AttackSelect[0], (MAP_END_X - GAP_9) * 2, MAP_END_Y - GAP_6);
	MapDraw::DrawMidText(m_AttackSelect[1], (MAP_END_X - GAP_4) * 2, MAP_END_Y - GAP_6);
	MapDraw::DrawMidText(m_AttackSelect[2], (MAP_END_X - GAP_9) * 2, MAP_END_Y - GAP_4);
	MapDraw::DrawMidText(m_AttackSelect[3], (MAP_END_X - GAP_4) * 2, MAP_END_Y - GAP_4);

	attackSelect = MapDraw::MenuSelectCursor_XY((BATTLEOPTIONS_END - 1) / 2, (BATTLEOPTIONS_END - 1) / 2, GAP_5, GAP_2, MAP_END_X - GAP_12, MAP_END_Y - GAP_6);


	if (monster->Get_EntityType() == entityType)
	{
		Weapon* weapon = player->GetWeapon();
		float monsterHP;
		float weaponCriticalAttack = 0;
		float bodyPartsCriticalAttack = 0;
		float basicAttack = player->Get_Attack() + weapon->GetAttack();

		//������ ũ��Ƽ�� Ȯ�� �ٸ��� ����
		if (m_CriticalBodyParts[HIGHTEST_PERCENTAGE - 1] == m_AttackSelect[attackSelect - 1])
		{ //�ְ� ��� ũ��Ƽ��
			bodyPartsCriticalAttack = basicAttack * entityBody.GetRisingPercentage(CRITICALBODYPARTS - 1);
			PrintDescription(entityBody.GetCriticalWords());
			getch();
			MapDraw::DrawMidText("                                                                        ", MAP_END_X, MENUPRINT_START_Y + GAP_3);
		}
		else if (m_CriticalBodyParts[LOW_PERCENTAGE - 1] == m_AttackSelect[attackSelect - 1])
		{ //ũ��Ƽ��
			bodyPartsCriticalAttack = basicAttack * entityBody.GetRisingPercentage(CRITICALBODYPARTS);
			PrintDescription(entityBody.GetCriticalWords());
			getch();
			MapDraw::DrawMidText("                                                                        ", MAP_END_X, MENUPRINT_START_Y + GAP_3);
		}

		//���⺰ ũ��Ƽ�� Ȯ�� ���
		if (WeaponProbability(weapon->GetCriticalRate()))
		{
			weaponCriticalAttack = basicAttack * weapon->GetRisingPercentage();
			PrintDescription(weapon->GetCriticalWords());
			getch();
		}			
		
		//TODO::���Ͱ� ȸ���� Ȯ��(����)

		//�÷��̾� HP ���
		monsterHP = monster->Get_NowHP() - basicAttack - weaponCriticalAttack - bodyPartsCriticalAttack;

		//HP�� 0 �Ʒ��� �������� �ʰ�
		if (monsterHP < 0)
			monster->Set_NowHP(0);
		else
			monster->Set_NowHP(monsterHP);

		PrintDescription(player->Get_Name() + "��/�� " + monster->Get_Name() + " �� [" + m_AttackSelect[attackSelect - 1] + "]�� " + to_string(int(basicAttack + weaponCriticalAttack + bodyPartsCriticalAttack)) + "��/�� ����");

		if (monster->Get_NowHP() <= 0)
			return WINCHECK_PLAYER_WIN;
		else
			return WINCHECK_NOTHING;
	}
}

WINCHECK Battle::MonsterTurn(Player* player, ENTITYTYPE entityType, Character* monster)
{
	WINCHECK whoWin;
	int random;

	//whoWin.name = monster->Get_Name();
	random = rand() % 100 + 1;

	if (random > 0 && random <= 70)
		whoWin = MonsterAttack(player, entityType, monster);
	if (random > 70 && random <= 80)
		whoWin = MonsterHeal(entityType, monster);
	if (random > 80 && random <= 100)
		whoWin = WINCHECK_MONSTER_RUNAWAY;

	return whoWin;
}

WINCHECK Battle::MonsterAttack(Player* player, ENTITYTYPE entityType, Character* monster)
{ //���� -> �÷��̾� ����
	float playerHP;
	int attackSelect;
	float weaponCriticalAttack = 0;
	float bodyPartsCriticalAttack = 0;
	float basicAttack = monster->Get_Attack();
	
	RandomBodyPartsSetting(entityType); //4������ ���� Ȯ�� ������ ����

	attackSelect = rand() % 4;
	BLOOD
	MapDraw::DrawMidText("                                                                        ", MAP_END_X, MENUPRINT_START_Y + GAP_3);
	MapDraw::DrawMidText("���Ͱ� ������ �غ��Ѵ�.", MAP_END_X, MENUPRINT_START_Y + GAP_3); getch();
	//ORIGINAL

	if (monster->Get_EntityType() == entityType)
	{
		//������ ũ��Ƽ�� Ȯ�� �ٸ��� ���� //ũ��Ƽ�� ���� ������ 10������ 2����
		if (m_CriticalBodyParts[HIGHTEST_PERCENTAGE - 1] == m_AttackSelect[attackSelect])
		{ //�ְ� ��� ũ��Ƽ��
			bodyPartsCriticalAttack = basicAttack * entityBody.GetRisingPercentage(HIGHTEST_PERCENTAGE - 1);
			PrintDescription(entityBody.GetCriticalWords());
			getch();
		}
		else if (m_CriticalBodyParts[LOW_PERCENTAGE - 1] == m_AttackSelect[attackSelect])
		{ //ũ��Ƽ��
			bodyPartsCriticalAttack = basicAttack * entityBody.GetRisingPercentage(LOW_PERCENTAGE - 1);
			PrintDescription(entityBody.GetCriticalWords());
			getch();
		}

		//LATER::���Ͱ� ȸ���� Ȯ��(����)

		//�÷��̾� HP ���
		playerHP = player->Get_NowHP() - monster->Get_Attack() - bodyPartsCriticalAttack;

		//HP�� 0 �Ʒ��� �������� �ʰ�
		if (playerHP < 0)
			player->Set_NowHP(0);
		else
			player->Set_NowHP(playerHP);
		
		//BLOOD
			MapDraw::DrawMidText("                                                                        ", MAP_END_X, MENUPRINT_START_Y + GAP_3);
			MapDraw::DrawMidText(monster->Get_Name() + "��/�� " + player->Get_Name() + "�� [" + m_AttackSelect[attackSelect] + "] �� " + to_string(int(monster->Get_Attack() + bodyPartsCriticalAttack)) + "��/�� ����", MAP_END_X, MENUPRINT_START_Y + GAP_3);
		ORIGINAL
		getch();

		if (player->Get_NowHP() <= 0)
			return WINCHECK_MONSTER_WIN;
		else
			return WINCHECK_NOTHING;
	}
}

WINCHECK Battle::MonsterHeal(ENTITYTYPE entityType, Character* monster)
{
	int RecoveryHP = 10;

	PrintDescription("���Ͱ� �ּ��ּ� �����ΰ��� ������."); getch();
	PrintDescription("�� ���� ���� ���Ŵ�."); getch();
	PrintDescription("���Ͱ� ���Ÿ� �Դ´�."); getch();

	//HP�� ������ ���� �ʰ�
	if (monster->Get_MaxHP() < monster->Get_NowHP() + RecoveryHP)
		monster->Set_NowHP(monster->Get_MaxHP());
	else
		monster->Set_NowHP(monster->Get_NowHP() + RecoveryHP);

	BLOOD
		PrintDescription(monster->Get_Name() + "��/�� HP" + to_string(RecoveryHP) + " ȸ��!");
	ORIGINAL
	getch();

	return WINCHECK_NOTHING;
}



//���ͺϿ� �ִ� ������ ���� �Ǻ�
void Battle::BattleMonsterInfo(Player* player, MONSTER enumMonster, SITUATION situatioin, Character monster)
{
	int y = GAP_2;
	MonsterBook* monsterBook = player->GetMonsterBook();

	monsterBook->RecodeMonsterBook(situatioin, enumMonster); //��Ȳ�� �°� ���� SaveMonsterBook.txt �� bool�� 1�� ��ȯ 
	//monsterBook->ReadMonsterBook(); //bSituation[][]�� bool�� �޾ƿ´�.
	//bool(*bSituation)[MONSTER_END] = monsterBook->RecodeMonsterBook(situatioin, enumMonster);

	PLUM
		monster.PrintMonsterBookInfo(enumMonster, monsterBook->GetSituation(), y);
	ORIGINAL
}



void Battle::PrintDescription(string _string)
{
	MapDraw::DrawMidText("                                                                        ", MAP_END_X, MENUPRINT_START_Y + GAP_3);
	GRAY
		MapDraw::DrawMidText(_string, MAP_END_X, MENUPRINT_START_Y + GAP_3);
	ORIGINAL
}

void Battle::RandomBodyPartsSetting(ENTITYTYPE entityType)
{ //TODO::���� �պ���
	int iTmp, i = 0;
	int iRandom[FOUR];
	string(*sEntityBody)[TEN] = entityBody.GetEntityBody();

	iRandom[i++] = rand() % 10 + 1;

	while (i < FOUR)
	{
		iTmp = rand() % 10 + 1;

		for (int j = 0; j < i; j++)
		{
			if (iRandom[j] == iTmp)
			{
				iTmp = rand() % 10 + 1;
				j = 0;
			}
		}
		iRandom[i++] = iTmp;
	}

	for (int i = 0; i < FOUR; i++)
		m_AttackSelect[i] = sEntityBody[entityType][iRandom[i]];

	//���� ���� ����
	m_CriticalBodyParts[CRITICALBODYPARTS - 2] = sEntityBody[entityType][HIGHTEST_PERCENTAGE - 1]; 
	m_CriticalBodyParts[CRITICALBODYPARTS - 1] = sEntityBody[entityType][LOW_PERCENTAGE - 1];
}

bool Battle::WeaponProbability(int rate)
{ //ex)Ȯ�� rate�� 20�� ��� rand() % 100�� 0~19�Ͻÿ� true�� ����
	if (rand() % 100 < rate)
		return true;
	return false;
}