#pragma once
#include "Goblin.h"
#include "Oak.h"
#include "Werewolves.h"

class MonsterManager //상속할 필요가 없다. monster 관리하는 함수가 character가 아님
{
private:
	//TODO::다회차에 이전 몬스터가 여전히 존재하길 바란다면 파일 입출력 처리 필요
	// ★ 이거 vector로 바꾸기를 추천. 삭제할때도 iter 돌리고 찾을 때도 iter 돌리는 것이 낭비
	//수가 적을 경우 list로 하나하나 받는 것도 괜찮지만. 어디서 문제 생겨서 같은 몬스터가 무한히 받아질 수 있기 때문에, 최대 몬스터 수 걸어두고 넘으면 list에 있는 몬스터들만 나오게 구성하는 것이 더 나음.
	list<Character*> monsterList; //몬스터 살아있으면 monsterList에 들어있다. 
	vector<Character*> monsterInfoList; //몬스터의 정보를 저장 "SaveMonster.txt" 파일에서 받아온.
	//동적할당을 하는 이유 : 함수포인터 bind를 사용해서 timer에서 조정을 하는데 데이터가 날아가버리므로 동적할당 이용 필수
public:
	MonsterManager();
	~MonsterManager();

	//몬스터 조우 함수 - 새로운 몬스터인지 이전에 만났던 몬스터인지해서. list(vector)까지 관리
	void MonsterCreate(MONSTER monster);
	//void MonsterStatusSetting(Character* tmpMonster);
	void ReadMonsterStatus(); //"SaveMonster.txt" 원본 몬스터 스테이터스 가져오기
	// ★ 함수 삭제.은닉화 실패. Character에서 처리
	//생성된 몬스터 삭제 (몬스터 객체를 새로 만들고 텍스트의 값을 넣어주는 식이라 리스트 초기화 안하면 같은 스텟 몬스터 x2)
	void CreateMonsterReset();

	//생성 몬스터 저장 리셋
	void ResetSaveMonstersTxt();
	void SaveMonsters();
	void LoadMonsters(); // ★ 원본 몬스터 list 정보, 생성된 몬스터(살아있는) 불러오기 처리하는 함수


	// ★ list 전부 말고 필요한 해당 몬스터만 리턴 받아갈 수 있도록 함수 변경
	list<Character*>* Get_MonsterList() { return &monsterList; } //몬스터 스테이터스 Player에게 전달.
	vector<Character*> Get_MonsterInfoList() { return monsterInfoList; } //bool값 따라 몬스터 정보 출력용.
};