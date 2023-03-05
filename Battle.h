#pragma once
#include "Player.h"
#include "EntityBody.h"
#include "WeaponShop.h" //WeaponCritical 함수를 이용
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
	EntityBody entityBody; //전투시 마주한 몬스터의 타입
	string m_AttackSelect[FOUR]; //전투시 마주한 몬스터에게 공격 가능한 부위
	//전투시 마주한 몬스터의(그리고 플레이어) 크리티컬 부위 2 종류
	//몬스터 부위의 인덱스 0,1이 크리티컬 부위로 설정
	//0이 가장 높은 계수 크리티컬, 1이 낮은 계수 크리티컬
	string m_CriticalBodyParts[CRITICALBODYPARTS]; 

public:
	Battle();
	~Battle();

	Character* MeetMonster(Player* player, MonsterManager* monsterManager); //meet랑 battle이랑 분리 이유 : 몬스터가 플레이어 지나가는 상황 발생
	MONSTER RandomMonsterEnum();

	WINCHECK BattleTurn(Character* monster, Player* player, MonsterManager* monsterManager);
	WINCHECK PlayerTurn(Player* player, ENTITYTYPE entityType, Character* monster, vector<Character*> monsterInfoList);
	int SelectAction(); //공격, 행동, 가방, 도망 선택
	WINCHECK PlayerAttack(Player* player, ENTITYTYPE entityType, Character* monster);
	WINCHECK MonsterTurn(Player* player, ENTITYTYPE entityType, Character* monster);
	WINCHECK MonsterAttack(Player* player, ENTITYTYPE entityType, Character* monster);
	WINCHECK MonsterHeal(ENTITYTYPE entityType, Character* monster);

	void BattleMonsterInfo(Player* player, MONSTER enumMonster, SITUATION situatioin, Character monster); //몬스터북에 있는 정보로 몬스터 판별

	void PrintDescription(string _string); //몬스터가 뭐하고 있다. 데미지 얼마 들어감 등. 나레이션
	void RandomBodyPartsSetting(ENTITYTYPE entityType); //공격 가능한 부위들을. 배열과 type의 enum (Character.h에 위치)으로 관리
	bool WeaponProbability(int rate); //ex)확률 rate가 20일 경우 rand() % 100가 0~19일시에 true를 리턴
};