#include "Battle.h"
//#include "GameManager.h" //Print와 DrawInterface 사용
#include "MonsterBook.h"

Battle::Battle()
{
	entityBody.CreateEntityBody();
}
Battle::~Battle(){}



Character* Battle::MeetMonster(Player* player, MonsterManager* monsterManager)
{
	MONSTER monsterEnum = RandomMonsterEnum();
	list<Character*> monsterList = *monsterManager->Get_MonsterList(); //리스트에 생성된 몬스터 가져오기 위해

	//monsterList 매번 찾지 않아도 되도록 미리 찾아둔다.
	for (list<Character*> ::iterator iter = monsterList.begin(); iter != monsterList.end(); iter++)
	{
		if (monsterEnum == (*iter)->Get_MonsterType())
		{
			MapDraw::BoxErase(MAP_END_X, MAP_END_Y / GAP_3 * GAP_2);

			BattleMonsterInfo(player, (*iter)->Get_MonsterType(), SITUATION_MEET, *(*iter)); //몬스터 등장, 출력만.
			//TODO::몬스터별 등장 행동 다르게
			PrintDescription("땅을 파헤치고 있다.");// 금화를 찾고 있다.");

			return (*iter);
		}
	}

	//몬스터가 리스트에 존재하지 않으면
	monsterManager->MonsterCreate(monsterEnum); //랜덤 몬스터 리스트에 생성
	monsterList = *monsterManager->Get_MonsterList(); //몬스터 리스트 갱신

	MapDraw::BoxErase(MAP_END_X, MAP_END_Y / GAP_3 * GAP_2);
	BattleMonsterInfo(player, monsterEnum, SITUATION_MEET, *monsterList.back()); //몬스터 등장, 출력만.
	PrintDescription("땅을 파헤치고 있다."); //금화를 찾고 있다.");

	return monsterList.back();
}

MONSTER Battle::RandomMonsterEnum()
{
	int randomMonster = rand() % MONSTER_COUNT;
	return (MONSTER)randomMonster;
}

WINCHECK Battle::BattleTurn(Character* monster, Player* player, MonsterManager* monsterManager)
{ //본격적인 전투 시작. 승패 확인까지 무한루프 함수.
	WINCHECK whoWin;
	
	while (true)
	{
		//플레이어 턴
		//공격 : 플레이어 -> 고블린(인간형)
		whoWin = PlayerTurn(player, monster->Get_EntityType(), monster, monsterManager->Get_MonsterInfoList());
		BattleMonsterInfo(player, monster->Get_MonsterType(), SITUATION_MEET, *monster); //몬스터 등장, 출력만.
		getch();

		//승패 확인
		if ((whoWin == WINCHECK_PLAYER_WIN) || (whoWin == WINCHECK_PLAYER_RUNAWAY))
			return whoWin;


		//몬스터 턴
		//공격 : 고블린 -> 플레이어(인간형)
		whoWin = MonsterTurn(player, monster->Get_EntityType(), monster);

		//플레이어 하단창 갱신 위해
		//TODO::정상 작동 확인하고 여기 코드 플레이어 창 지우는 거 만들어서 player랑 둘이만 남겨두기.
		MapDraw::BoxDraw(MAP_START, MAP_START, MAP_END_X, MAP_END_Y);
		MapDraw::BoxSectorDraw(MAP_END_X, MAP_END_Y, MAP_END_X, MAP_END_Y);
		Interface::UnderInfo(*player);
		BattleMonsterInfo(player, monster->Get_MonsterType(), SITUATION_FIGHT, *monster);
		///여기까지///

		//승패 확인
		if ((whoWin == WINCHECK_MONSTER_WIN) || (whoWin == WINCHECK_MONSTER_RUNAWAY))
			return whoWin;
	}

	//whoWin.name = " ";
	return WINCHECK_NOTHING;
}

WINCHECK Battle::PlayerTurn(Player* player, ENTITYTYPE entityType, Character* monster, vector<Character*> monsterBook)
{ //플레이어 -> 고블린(인간형)
	WINCHECK whoWin;

	//whoWin.name = player->Get_Name();

	switch (SelectAction()) //공격, 행동, 가방, 도망 선택
	{
	case BATTLEOPTIONS_ATTACK:
		BattleMonsterInfo(player, monster->Get_MonsterType(), SITUATION_FIGHT, *monster); //몬스터 창 갱신 위해
		whoWin = PlayerAttack(player, entityType, monster);
		break;
	case BATTLEOPTIONS_ACTION: //LATER::행동의 다양화 필요.
		PrintDescription("가방에 도움이 될만한 게 있을까...!"); getch();
		PrintDescription("몬스터는 당신을 기다려주지 않는다.");
		whoWin = WINCHECK_NOTHING;
		break;
	case BATTLEOPTIONS_BAG: //LATER::인벤토리 기능 구현
		PrintDescription("가방에는 도감밖에 없다."); getch();
		PrintDescription("할 수 있는 건 도감 보는 거밖에 없다."); getch();
		MapDraw::DrawMidText("                                                                        ", MAP_END_X, MENUPRINT_START_Y + GAP_3);
		//player->GetMonsterBook()->ReadMonsterBook(); //"SaveMonsterBook.txt"에 있는 bool값 읽어온다.
		player->PrintMonsterBook(monsterBook); //전투 진행중에 몬스터 도감 출력
		getch();
		MapDraw::BoxErase(MAP_END_X, MAP_END_Y / GAP_3 * GAP_2);
		/*MapDraw::BoxDraw(MAP_START, MAP_START, MAP_END_X, MAP_END_Y);
		MapDraw::BoxSectorDraw(MAP_END_X, MAP_END_Y, MAP_END_X, MAP_END_Y);
		player->UnderInfo();*/
		whoWin = WINCHECK_NOTHING;
		break;
	case BATTLEOPTIONS_ESCAPE:
		PrintDescription("당신이 더 빠를까? 몬스터가 더 빠를까?");
		whoWin = WINCHECK_PLAYER_RUNAWAY;
		break;
	}
	return whoWin;
}

int Battle::SelectAction()
{
	int select;

	MapDraw::DrawMidText("공격", (MAP_END_X - GAP_9) * 2, MAP_END_Y - GAP_6);
	MapDraw::DrawMidText("행동", (MAP_END_X - GAP_4) * 2, MAP_END_Y - GAP_6);
	MapDraw::DrawMidText("가방", (MAP_END_X - GAP_9) * 2, MAP_END_Y - GAP_4);
	MapDraw::DrawMidText("도망", (MAP_END_X - GAP_4) * 2, MAP_END_Y - GAP_4);

	select = MapDraw::MenuSelectCursor_XY((BATTLEOPTIONS_END - 1) / 2, (BATTLEOPTIONS_END - 1) / 2, GAP_5, GAP_2, MAP_END_X - GAP_12, MAP_END_Y - GAP_6);

	return select;
}

WINCHECK Battle::PlayerAttack(Player* player, ENTITYTYPE entityType, Character* monster)
{ //플레이어 -> 몬스터 공격
	int attackSelect;

	//4지선다 랜덤 확률 데미지 설정
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

		//부위별 크리티컬 확률 다르게 설정
		if (m_CriticalBodyParts[HIGHTEST_PERCENTAGE - 1] == m_AttackSelect[attackSelect - 1])
		{ //최고 계수 크리티컬
			bodyPartsCriticalAttack = basicAttack * entityBody.GetRisingPercentage(CRITICALBODYPARTS - 1);
			PrintDescription(entityBody.GetCriticalWords());
			getch();
			MapDraw::DrawMidText("                                                                        ", MAP_END_X, MENUPRINT_START_Y + GAP_3);
		}
		else if (m_CriticalBodyParts[LOW_PERCENTAGE - 1] == m_AttackSelect[attackSelect - 1])
		{ //크리티컬
			bodyPartsCriticalAttack = basicAttack * entityBody.GetRisingPercentage(CRITICALBODYPARTS);
			PrintDescription(entityBody.GetCriticalWords());
			getch();
			MapDraw::DrawMidText("                                                                        ", MAP_END_X, MENUPRINT_START_Y + GAP_3);
		}

		//무기별 크리티컬 확률 고려
		if (WeaponProbability(weapon->GetCriticalRate()))
		{
			weaponCriticalAttack = basicAttack * weapon->GetRisingPercentage();
			PrintDescription(weapon->GetCriticalWords());
			getch();
		}			
		
		//TODO::몬스터가 회피할 확률(보류)

		//플레이어 HP 계산
		monsterHP = monster->Get_NowHP() - basicAttack - weaponCriticalAttack - bodyPartsCriticalAttack;

		//HP가 0 아래로 떨어지지 않게
		if (monsterHP < 0)
			monster->Set_NowHP(0);
		else
			monster->Set_NowHP(monsterHP);

		PrintDescription(player->Get_Name() + "이/가 " + monster->Get_Name() + " 의 [" + m_AttackSelect[attackSelect - 1] + "]을 " + to_string(int(basicAttack + weaponCriticalAttack + bodyPartsCriticalAttack)) + "으/로 공격");

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
{ //몬스터 -> 플레이어 공격
	float playerHP;
	int attackSelect;
	float weaponCriticalAttack = 0;
	float bodyPartsCriticalAttack = 0;
	float basicAttack = monster->Get_Attack();
	
	RandomBodyPartsSetting(entityType); //4지선다 랜덤 확률 데미지 설정

	attackSelect = rand() % 4;
	BLOOD
	MapDraw::DrawMidText("                                                                        ", MAP_END_X, MENUPRINT_START_Y + GAP_3);
	MapDraw::DrawMidText("몬스터가 공격을 준비한다.", MAP_END_X, MENUPRINT_START_Y + GAP_3); getch();
	//ORIGINAL

	if (monster->Get_EntityType() == entityType)
	{
		//부위별 크리티컬 확률 다르게 설정 //크리티컬 가능 부위는 10부위중 2부위
		if (m_CriticalBodyParts[HIGHTEST_PERCENTAGE - 1] == m_AttackSelect[attackSelect])
		{ //최고 계수 크리티컬
			bodyPartsCriticalAttack = basicAttack * entityBody.GetRisingPercentage(HIGHTEST_PERCENTAGE - 1);
			PrintDescription(entityBody.GetCriticalWords());
			getch();
		}
		else if (m_CriticalBodyParts[LOW_PERCENTAGE - 1] == m_AttackSelect[attackSelect])
		{ //크리티컬
			bodyPartsCriticalAttack = basicAttack * entityBody.GetRisingPercentage(LOW_PERCENTAGE - 1);
			PrintDescription(entityBody.GetCriticalWords());
			getch();
		}

		//LATER::몬스터가 회피할 확률(보류)

		//플레이어 HP 계산
		playerHP = player->Get_NowHP() - monster->Get_Attack() - bodyPartsCriticalAttack;

		//HP가 0 아래로 떨어지지 않게
		if (playerHP < 0)
			player->Set_NowHP(0);
		else
			player->Set_NowHP(playerHP);
		
		//BLOOD
			MapDraw::DrawMidText("                                                                        ", MAP_END_X, MENUPRINT_START_Y + GAP_3);
			MapDraw::DrawMidText(monster->Get_Name() + "이/가 " + player->Get_Name() + "의 [" + m_AttackSelect[attackSelect] + "] 을 " + to_string(int(monster->Get_Attack() + bodyPartsCriticalAttack)) + "으/로 공격", MAP_END_X, MENUPRINT_START_Y + GAP_3);
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

	PrintDescription("몬스터가 주섬주섬 무엇인가를 꺼낸다."); getch();
	PrintDescription("잘 여문 나무 열매다."); getch();
	PrintDescription("몬스터가 열매를 먹는다."); getch();

	//HP가 오버힐 되지 않게
	if (monster->Get_MaxHP() < monster->Get_NowHP() + RecoveryHP)
		monster->Set_NowHP(monster->Get_MaxHP());
	else
		monster->Set_NowHP(monster->Get_NowHP() + RecoveryHP);

	BLOOD
		PrintDescription(monster->Get_Name() + "이/가 HP" + to_string(RecoveryHP) + " 회복!");
	ORIGINAL
	getch();

	return WINCHECK_NOTHING;
}



//몬스터북에 있는 정보로 몬스터 판별
void Battle::BattleMonsterInfo(Player* player, MONSTER enumMonster, SITUATION situatioin, Character monster)
{
	int y = GAP_2;
	MonsterBook* monsterBook = player->GetMonsterBook();

	monsterBook->RecodeMonsterBook(situatioin, enumMonster); //상황에 맞게 몬스터 SaveMonsterBook.txt 의 bool을 1로 전환 
	//monsterBook->ReadMonsterBook(); //bSituation[][]에 bool값 받아온다.
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
{ //TODO::오류 손보기
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

	//약점 부위 세팅
	m_CriticalBodyParts[CRITICALBODYPARTS - 2] = sEntityBody[entityType][HIGHTEST_PERCENTAGE - 1]; 
	m_CriticalBodyParts[CRITICALBODYPARTS - 1] = sEntityBody[entityType][LOW_PERCENTAGE - 1];
}

bool Battle::WeaponProbability(int rate)
{ //ex)확률 rate가 20일 경우 rand() % 100가 0~19일시에 true를 리턴
	if (rand() % 100 < rate)
		return true;
	return false;
}