#pragma once
#include "Player.h"
#include "EntityBody.h"
#include "WeaponShop.h" //WeaponCritical �Լ��� �̿�
#include "MapDraw.h"
#include "Character.h"
#include "MonsterManager.h"
#include "Interface.h"

#define CRITICALBODYPARTS 2

enum WINCHECK
{
	WINCHECK_NOTHING,

	WINCHECK_PLAYER_WIN,
	WINCHECK_PLAYER_LOSE,
	WINCHECK_PLAYER_RUNAWAY,	
	
	WINCHECK_MONSTER_WIN,
	WINCHECK_MONSTER_LOSE,
	WINCHECK_MONSTER_RUNAWAY,
};
enum BATTLEOPTIONS
{
	BATTLEOPTIONS_START,
	BATTLEOPTIONS_ATTACK,
	BATTLEOPTIONS_ACTION,
	BATTLEOPTIONS_BAG,
	BATTLEOPTIONS_ESCAPE,
	BATTLEOPTIONS_END,
};

//struct WhoWin
//{
//	string name;
//	WINCHECK winCheck;
//};

class Battle
{
private:
	EntityBody entityBody; //������ ������ ������ Ÿ��
	string m_AttackSelect[FOUR]; //������ ������ ���Ϳ��� ���� ������ ����
	//������ ������ ������(�׸��� �÷��̾�) ũ��Ƽ�� ���� 2 ����
	//���� ������ �ε��� 0,1�� ũ��Ƽ�� ������ ����
	//0�� ���� ���� ��� ũ��Ƽ��, 1�� ���� ��� ũ��Ƽ��
	string m_CriticalBodyParts[CRITICALBODYPARTS]; 

public:
	Battle();
	~Battle();

	Character* MeetMonster(Player* player, MonsterManager* monsterManager); //meet�� battle�̶� �и� ���� : ���Ͱ� �÷��̾� �������� ��Ȳ �߻�
	MONSTER RandomMonsterEnum();

	WINCHECK BattleTurn(Character* monster, Player* player, MonsterManager* monsterManager);
	WINCHECK PlayerTurn(Player* player, ENTITYTYPE entityType, Character* monster, vector<Character*> monsterInfoList);
	int SelectAction(); //����, �ൿ, ����, ���� ����
	WINCHECK PlayerAttack(Player* player, ENTITYTYPE entityType, Character* monster);
	WINCHECK MonsterTurn(Player* player, ENTITYTYPE entityType, Character* monster);
	WINCHECK MonsterAttack(Player* player, ENTITYTYPE entityType, Character* monster);
	WINCHECK MonsterHeal(ENTITYTYPE entityType, Character* monster);

	void BattleMonsterInfo(Player* player, MONSTER enumMonster, SITUATION situatioin, Character monster); //���ͺϿ� �ִ� ������ ���� �Ǻ�

	void PrintDescription(string _string); //���Ͱ� ���ϰ� �ִ�. ������ �� �� ��. �����̼�
	void RandomBodyPartsSetting(ENTITYTYPE entityType); //���� ������ ��������. �迭�� type�� enum (Character.h�� ��ġ)���� ����
	bool WeaponProbability(int rate); //ex)Ȯ�� rate�� 20�� ��� rand() % 100�� 0~19�Ͻÿ� true�� ����
};