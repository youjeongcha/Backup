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
	//txt���� �޾ƿ� word��
	std::vector<std::string> wordList;
	//ȭ�鿡 ��µǾ� �������� word��
	std::vector<Word> generatedWordList;
	//vector<Word*> generatedItemWordList;
public:
	WordManager();
	~WordManager();

	//ȭ�鿡 ��µ� �ܾ� ����
	void CreateWord(bool hideWordCheck);
	//bool�� Y�� ��� �ܾ� ����� ���� Ȯ�ο� //��ǥ �̵�
	//bool DropWord(int playerLife, bool hideWordCheck);


	bool DropWord(int playerLife); //�� X���� ������ ����. ��Ī ���� DropWord��
	//ȭ�� ��� Drop + ������ �ܾ� ����
	void DropWordPrint(bool hideWordCheck); //�� �̰� Drop�� �ƴϴ�. PrintWord�� ����


	//bool ������ �����ͼ� GameManager���� ������ �÷� �ش�.
	ITEM TypingCheck(std::string* inputWord);
	//void DeleteWord();
	//wordList�� generatedWordList �ʱ�ȭ
	void RestList();
	//������ �۵�(�Ϲ� �ܾ�� �ȿ��� �ɷ�����.) + �ܾ� ����
	//�ð� �����ϴ� ������ �۵� ���� �ð� �����α� ���� ITEM����
	void ItemOperate(ITEM usedItem, int& createSpeed, int& dropSpeed, int& usedItem_OldClock);

	//SaveWord.txt ���Ͽ��� �ܾ� �ҷ�����
	void LoadWordList();
};

