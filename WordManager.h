#pragma once
#include "Word.h"
#include "Player.h"

enum CREATEWORD
{
	CREATEWORD_SPEED_STAGE1 = 2400,
	CREATEWORD_SPEED_STAGE2 = 2200,
	CREATEWORD_SPEED_STAGE3 = 2000,
	CREATEWORD_SPEED_STAGE4 = 1800,
	CREATEWORD_SPEED_STAGE5 = 1600,
	CREATEWORD_SPEED_STAGE6 = 1400,

	CREATEWORD_RANGE = 500,
};

class WordManager
{
private:
	//txt에서 받아온 word들
	std::vector<std::string> wordList;
	//화면에 출력되어 떨어지는 word들
	std::vector<Word> generatedWordList;
	//vector<Word*> generatedItemWordList;
public:
	WordManager();
	~WordManager();

	//화면에 출력될 단어 생성
	void CreateWord(bool hideWordCheck);
	//bool값 Y축 벗어난 단어 지우기 위해 확인용 //좌표 이동
	//bool DropWord(int playerLife, bool hideWordCheck);


	bool DropWord(int playerLife); //★ X축은 변경이 없다. 명칭 변경 DropWord로
	//화면 출력 Drop + 떨어진 단어 삭제
	void DropWordPrint(bool hideWordCheck); //★ 이건 Drop이 아니다. PrintWord로 변경


	//bool 값으로 가져와서 GameManager에서 점수를 올려 준다.
	ITEM TypingCheck(std::string* inputWord);
	//void DeleteWord();
	//wordList와 generatedWordList 초기화
	void RestList();
	//아이템 작동(일반 단어는 안에서 걸러진다.) + 단어 삭제
	//시간 변경하는 아이템 작동 이후 시간 돌려두기 위해 ITEM으로
	void ItemOperate(ITEM usedItem, int& createSpeed, int& dropSpeed, int& usedItem_OldClock);

	//SaveWord.txt 파일에서 단어 불러오기
	void LoadWordList();
};

