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
		iter = generatedWordList.erase(iter); //list에서 삭제. iter로 다음 주소 받아줘야 오류가 안 뜬다.
}

void WordManager::CreateWord(bool hideWordCheck)
{
	int iRandWord = rand() % wordList.size(); //생성 단어(string) 정하기
	int iRand_Nomal_Or_Item = rand() % 100; //일반 단어 vs 아이템 단어 정하기
	int iRandItemType = 0; //0이 Normal 아이템 아닌 단어 enum

	// 이런식으로 코드 간소화 가능하다.if문 한번만 돌아도 되고. + word 이니셜라이저에서 item 설정 해주는 것까지
	if (iRand_Nomal_Or_Item >= 80)
		iRandItemType = rand() % 5 + 1; //아이템 단어 종류 정하기
	generatedWordList.push_back(Word(wordList[iRandWord], (ITEM)iRandItemType));

	//만들어지면 출력 //hide 아이템 적용시에 단어 생성되면 아이템 적용 된 상태로 출력 위해.
	generatedWordList.back().PrintWord(hideWordCheck);

	/*
	80% 확률로 일반 단어 생성
	if (iRand_Nomal_Or_Item < 80)
		tmpWord.Set_Word(wordList[iRandWord], ITEM_NOMAL);
	else //20% 확률로 아이템 단어 생성
	{
		int iRandItemType = rand() % 5 + 1; //아이템 단어 종류 정하기
		tmpWord.Set_Word(wordList[iRandWord], (ITEM)iRandItemType);
	}
	generatedWordList.push_back(tmpWord);
	//generatedWordList.push_back(new Word); //이런 식으로 하는 경우에 복사 생성자가 필요.
	//+깊은 복사로 할때 복사 생성자 따로 만들어야 함
	//동적할당해서 객체를 받을 필요가 있을 경우에만 new를 사용. new를 사용하면 *포인터로 받아야 한다.

	//만들어지면 출력 //hide 아이템 적용시에 단어 생성되면 아이템 적용 된 상태로 출력 위해.
	tmpWord.PrintWord(hideWordCheck);
	*/
}

bool WordManager::DropWord(int playerLife)
{//★ Drop으로 바꾸고
	//Word deleteWord;// = NULL; //질문
	XY endCheck_Y;
	bool endWordCheck = false;

	for (std::vector<Word>::iterator iter = generatedWordList.begin(); iter != generatedWordList.end();)
	{
		iter->EraseWord(); //단어 화면에서 지우기
		iter->Drop(); //단어 Y 좌표 떨어뜨리기

		endCheck_Y = iter->Get_XY();


		//Y 좌표 한계 넘어가면 list에서 문자 빼기
		if (endCheck_Y.m_Y > DROP_END_Y)
		{//★여전히 어려운 부분★
			iter = generatedWordList.erase(iter); //list에서 삭제. iter로 다음 주소 받아줘야 오류가 안 뜬다.

			endWordCheck = true; //죽은 단어. 바닥까지 떨어진 단어.
		}
		else
			iter++;
	}

	return endWordCheck;
}

void WordManager::DropWordPrint(bool hideWordCheck)
{//★ 명칭 변경. 위에 과정을 거친다면 Print만 해도 될것.
	//출력과 삭제는 이 곳에서 관리. 프린트되는 순간이 같아야 한다.
	for (std::vector<Word>::iterator iter = generatedWordList.begin(); iter != generatedWordList.end(); iter++)
	{
		//iter->EraseWord();//삭제 되겠지만 iter는 안에서 자기 word size알고 있으니까. get해올 필요가 하등 없다.
		iter->PrintWord(hideWordCheck);
	}
}

ITEM WordManager::TypingCheck(std::string* inputWord)
{
	ITEM deleteWordItem;

	for (std::vector<Word>::iterator iter = generatedWordList.begin(); iter != generatedWordList.end(); iter++)
	{
		if (iter->Get_Word() == *inputWord)
		{//단어를 맞췄을 시에
			//삭제될 단어 저장해서 받아가기
			//deleteWord = &(*iter);
			//*deleteWord = *iter; //iter는 주소일 뿐 인자를 복사는 불가능. 주소를 복사하려고 했지만 erase되면 쓰레기값이 되어버렸다.
			deleteWordItem = iter->Get_ItemType();	
			//입력한. 떨어지는 문자 지우기
			iter->EraseWord();//자기가 word size를 가지고 있는앤데. get할 필요X

			SKY_BLUE
			MapDraw::BoxDraw(INPUTBOX_START_X, INPUTBOX_START_Y, INPUTBOX_WIDTH, INPUTBOX_HEIGHT); //입력박스 위 단어 맞출 시 생기는 공백 막기
			ORIGINAL

			//떨어지는 문자 List에서 비우기
			generatedWordList.erase(iter);
			//iter = generatedWordList.erase(iter); //return 받으니까 굳이 할필요X

			//입력창에 있던 문자 화면에서만 지우기. inputWord 비우기는 밖에서
			MapDraw::DrawMidText("                      ", MAPSIZE_END_X, INPUTBOX_PRINT); 
			return deleteWordItem;
		}
	}
	return ITEM_NONE;
}

//void WordManager::DeleteWord()
//{
//}

//★ 레퍼런스로 받아와서 바꾸기. 포인터로 대상 바꿀 필요도. 주소 바꿀 필요도 없다.
void WordManager::ItemOperate(ITEM usedItem, int& createSpeed, int& dropSpeed, int& usedItem_UsingTime)
{
	switch (usedItem)
	{
	case ITEM_NOMAL: //아이템 아님
		break;
	case ITEM_SPEED_UP: //워드속도 증가(3초)
		usedItem_UsingTime = 3000;
		createSpeed -= 400;
		dropSpeed -= 150;
		break;
	case ITEM_SPEED_DOWN: //워드속도 감소(3초)
		usedItem_UsingTime = 3000;
		createSpeed += 1000;
		dropSpeed += 800;
		break;
	case ITEM_STOP: //워드일시정지(1.5초)
		usedItem_UsingTime = 1500;
		createSpeed = 10000000000;
		dropSpeed = 10000000000;
		break;
	case ITEM_SCREEN_CLEAR: //화면 클리어
	{
		for (std::vector<Word>::iterator iter = generatedWordList.begin(); iter != generatedWordList.end();)
		{
			iter->EraseWord(); //화면에서 지우기
			iter = generatedWordList.erase(iter); //list에서 삭제. iter로 다음 주소 받아줘야 오류가 안 뜬다.
		}
		break;
	}
	case ITEM_HIDE: //워드가리기(1.5초)
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