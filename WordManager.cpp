#include "WordManager.h"
#include "Interface.h"

WordManager::WordManager()
{
	LoadWordList();
}
WordManager::~WordManager()
{
}

void WordManager::RestList()
{
	for (std::vector<Word>::iterator iter = generatedWordList.begin(); iter != generatedWordList.end();)
		iter = generatedWordList.erase(iter); //list���� ����. iter�� ���� �ּ� �޾���� ������ �� ���.
}

void WordManager::CreateWord(bool hideWordCheck)
{
	int iRandWord = rand() % wordList.size(); //���� �ܾ�(string) ���ϱ�
	int iRand_Nomal_Or_Item = rand() % 100; //�Ϲ� �ܾ� vs ������ �ܾ� ���ϱ�
	int iRandItemType = 0; //0�� Normal ������ �ƴ� �ܾ� enum

	// �̷������� �ڵ� ����ȭ �����ϴ�.if�� �ѹ��� ���Ƶ� �ǰ�. + word �̴ϼȶ��������� item ���� ���ִ� �ͱ���
	if (iRand_Nomal_Or_Item >= 80)
		iRandItemType = rand() % 5 + 1; //������ �ܾ� ���� ���ϱ�
	generatedWordList.push_back(Word(wordList[iRandWord], (ITEM)iRandItemType));

	//��������� ��� //hide ������ ����ÿ� �ܾ� �����Ǹ� ������ ���� �� ���·� ��� ����.
	generatedWordList.back().PrintWord(hideWordCheck);

	/*
	80% Ȯ���� �Ϲ� �ܾ� ����
	if (iRand_Nomal_Or_Item < 80)
		tmpWord.Set_Word(wordList[iRandWord], ITEM_NOMAL);
	else //20% Ȯ���� ������ �ܾ� ����
	{
		int iRandItemType = rand() % 5 + 1; //������ �ܾ� ���� ���ϱ�
		tmpWord.Set_Word(wordList[iRandWord], (ITEM)iRandItemType);
	}
	generatedWordList.push_back(tmpWord);
	//generatedWordList.push_back(new Word); //�̷� ������ �ϴ� ��쿡 ���� �����ڰ� �ʿ�.
	//+���� ����� �Ҷ� ���� ������ ���� ������ ��
	//�����Ҵ��ؼ� ��ü�� ���� �ʿ䰡 ���� ��쿡�� new�� ���. new�� ����ϸ� *�����ͷ� �޾ƾ� �Ѵ�.

	//��������� ��� //hide ������ ����ÿ� �ܾ� �����Ǹ� ������ ���� �� ���·� ��� ����.
	tmpWord.PrintWord(hideWordCheck);
	*/
}

bool WordManager::DropWord(int playerLife)
{//�� Drop���� �ٲٰ�
	//Word deleteWord;// = NULL; //����
	XY endCheck_Y;
	bool endWordCheck = false;

	for (std::vector<Word>::iterator iter = generatedWordList.begin(); iter != generatedWordList.end();)
	{
		iter->EraseWord(); //�ܾ� ȭ�鿡�� �����
		iter->Drop(); //�ܾ� Y ��ǥ ����߸���

		endCheck_Y = iter->Get_XY();


		//Y ��ǥ �Ѱ� �Ѿ�� list���� ���� ����
		if (endCheck_Y.m_Y > DROP_END_Y)
		{//�ڿ����� ����� �κС�
			iter = generatedWordList.erase(iter); //list���� ����. iter�� ���� �ּ� �޾���� ������ �� ���.

			endWordCheck = true; //���� �ܾ�. �ٴڱ��� ������ �ܾ�.
		}
		else
			iter++;
	}

	return endWordCheck;
}

void WordManager::DropWordPrint(bool hideWordCheck)
{//�� ��Ī ����. ���� ������ ��ģ�ٸ� Print�� �ص� �ɰ�.
	//��°� ������ �� ������ ����. ����Ʈ�Ǵ� ������ ���ƾ� �Ѵ�.
	for (std::vector<Word>::iterator iter = generatedWordList.begin(); iter != generatedWordList.end(); iter++)
	{
		//iter->EraseWord();//���� �ǰ����� iter�� �ȿ��� �ڱ� word size�˰� �����ϱ�. get�ؿ� �ʿ䰡 �ϵ� ����.
		iter->PrintWord(hideWordCheck);
	}
}

ITEM WordManager::TypingCheck(std::string* inputWord)
{
	ITEM deleteWordItem;

	for (std::vector<Word>::iterator iter = generatedWordList.begin(); iter != generatedWordList.end(); iter++)
	{
		if (iter->Get_Word() == *inputWord)
		{//�ܾ ������ �ÿ�
			//������ �ܾ� �����ؼ� �޾ư���
			//deleteWord = &(*iter);
			//*deleteWord = *iter; //iter�� �ּ��� �� ���ڸ� ����� �Ұ���. �ּҸ� �����Ϸ��� ������ erase�Ǹ� �����Ⱚ�� �Ǿ���ȴ�.
			deleteWordItem = iter->Get_ItemType();	
			//�Է���. �������� ���� �����
			iter->EraseWord();//�ڱⰡ word size�� ������ �ִ¾ص�. get�� �ʿ�X

			SKY_BLUE
			MapDraw::BoxDraw(INPUTBOX_START_X, INPUTBOX_START_Y, INPUTBOX_WIDTH, INPUTBOX_HEIGHT); //�Է¹ڽ� �� �ܾ� ���� �� ����� ���� ����
			ORIGINAL

			//�������� ���� List���� ����
			generatedWordList.erase(iter);
			//iter = generatedWordList.erase(iter); //return �����ϱ� ���� ���ʿ�X

			//�Է�â�� �ִ� ���� ȭ�鿡���� �����. inputWord ����� �ۿ���
			MapDraw::DrawMidText("                      ", MAPSIZE_END_X, INPUTBOX_PRINT); 
			return deleteWordItem;
		}
	}
	return ITEM_NONE;
}

//void WordManager::DeleteWord()
//{
//}

//�� ���۷����� �޾ƿͼ� �ٲٱ�. �����ͷ� ��� �ٲ� �ʿ䵵. �ּ� �ٲ� �ʿ䵵 ����.
void WordManager::ItemOperate(ITEM usedItem, int& createSpeed, int& dropSpeed, int& usedItem_UsingTime)
{
	switch (usedItem)
	{
	case ITEM_NOMAL: //������ �ƴ�
		break;
	case ITEM_SPEED_UP: //����ӵ� ����(3��)
		usedItem_UsingTime = 3000;
		createSpeed -= 400;
		dropSpeed -= 150;
		break;
	case ITEM_SPEED_DOWN: //����ӵ� ����(3��)
		usedItem_UsingTime = 3000;
		createSpeed += 1000;
		dropSpeed += 800;
		break;
	case ITEM_STOP: //�����Ͻ�����(1.5��)
		usedItem_UsingTime = 1500;
		createSpeed = 10000000000;
		dropSpeed = 10000000000;
		break;
	case ITEM_SCREEN_CLEAR: //ȭ�� Ŭ����
	{
		for (std::vector<Word>::iterator iter = generatedWordList.begin(); iter != generatedWordList.end();)
		{
			iter->EraseWord(); //ȭ�鿡�� �����
			iter = generatedWordList.erase(iter); //list���� ����. iter�� ���� �ּ� �޾���� ������ �� ���.
		}
		break;
	}
	case ITEM_HIDE: //���尡����(1.5��)
		usedItem_UsingTime = 1500;
		break;
	default:
		break;
	}
}


void WordManager::LoadWordList()
{
	std::string stringTmp;
	int totalWordsCount;
	std::fstream load;
	load.open("Word.txt");

	if (load.is_open())
	{
		load >> totalWordsCount;

		for (int i = 0; i < totalWordsCount; i++)
		{
			load >> stringTmp;
			wordList.push_back(stringTmp);
		}
		load.close();
	}
}