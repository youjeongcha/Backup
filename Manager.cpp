 #include "Manager.h"

Manager::Manager() { }

void Manager::Menu()
{
	while (true)
	{
		system("cls");

		switch (MenuDraw())
		{
		case 1:
			system("cls");
			GameStart();
			break;
		case 2:
			return;
		}
	}
}

int Manager::MenuDraw()
{
	int Menu_Y = 9;
	int select;

	ObstacleBorder();

	DrawMidText("S n a k e  G a m e", WIDTH, Menu_Y);
	DrawMidText("1.Game Start", WIDTH, Menu_Y += 3);
	DrawMidText("2.Exit", WIDTH, Menu_Y += 3);
	DrawMidText("Select : ", WIDTH, Menu_Y += 3);
	cin >> select;

	return select;
}



void Manager::GameStart()
{
	int foodClock, moveClock;
	int score = 0;
	int SnakeSpeed = SNAKE_SPEED_DEFAULT;

	foodClock = clock();
	moveClock = clock();

	ObstacleBorder();
	RandomCreate(Obstacle); //장애물::일회성
	Snake::SnakeCreate(BlockCheck::Snake_Head); //뱀 머리 생성

	PrintScore(score);
	
	while (true)
	{
		if ((foodList.size() < MAXFOOD) && (clock() - foodClock >= FOODCLCOK))
		{
			RandomCreate(Food); //먹이::횟수한정 10개 최대. 미만일 시에 1.5초에 하나씩 생성
			foodClock = clock();
		}

		//뱀 이동 입력값
		Snake::SnakeInput();

		//뱀 이동 시간
		if (clock() - moveClock >= SnakeSpeed) 
		{
			//뱀 이동 전에 장애물 체크
			if ((SnakeInteraction(SREACHLIST::OBSTACLELIST) || (SnakeInteraction(SREACHLIST::SNAKELIST))))
			{//clock 안에 안 넣으면 장애물 앞에 도착하자마자 GameOver 떠버린다.
				GameOver(score);
				Snake::InputReset();
				return;
			}

			Snake::SnakeMove();
			moveClock = clock();
		}

		//뱀 이동 다음에 체크
		if (SnakeInteraction(SREACHLIST::FOODLIST))
		{
			score++;
			PrintScore(score);
			Snake::SnakeCreate(BlockCheck::Snake_Body);
			SnakeSpeed -= SNAKE_FASTER;
		}
	}
}

void Manager::PrintScore(int score)
{
	DrawMidText("score : ", WIDTH, 31);
	cout << score;
}

void Manager::GameOver(int score)
{
	DrawMidText("G a m e  O v e r", WIDTH, 9);
	DrawMidText("score : ", WIDTH, 15);
	cout << score;
	DrawMidText("Press Key", WIDTH, 21);

	//list들 초기화
	obstacleList.clear();
	foodList.clear();
	Snake::snakeList.clear();

	getch(); //키 입력 받을 때까지 대기.
}


bool Manager::SnakeInteraction(SREACHLIST enList)
{//뱀 이동하기 전에 길 확인 하는 코드 //뱀 머리랑 먹이 좌표 겹치면 > 리스트 지움
	list<Block>* blockList; //포인터
	XY snakeHead = Snake::snakeList.begin()->GetXY();

	switch (enList)
	{
	case FOODLIST:
		blockList = &foodList; //현재 위치 체크 > snakeHead 좌표 그대로
		break;
	case OBSTACLELIST:
		blockList = &obstacleList;
		snakeHead.x += Snake::m_InputXY.x * 2; //미리 체크
		snakeHead.y += Snake::m_InputXY.y;
		break;
	case SNAKELIST:
		blockList = &Snake::snakeList;
		snakeHead.x += Snake::m_InputXY.x * 2; //미리 체크
		snakeHead.y += Snake::m_InputXY.y;
		break;
	default:
		break;
	}

	for (list<Block>::iterator iter = blockList->begin(); iter != blockList->end(); iter++)
	{
		if ((enList == SNAKELIST) && (Snake::snakeList.size() == 1)) //뱀 머리 == 뱀 리스트 처음 > GameOver가 된다.
			return false;
		if ((snakeHead.x == iter->GetXY().x) && (snakeHead.y == iter->GetXY().y)) 
		{
			if (enList == FOODLIST)
				blockList->erase(iter);
			return true;
		}
	}
	return false;
}


void Manager::RandomCreate(BlockCheck checkBlock)
{//장애물::일회성 //먹이::횟수한정
	int x, y, rCount = 0;
	Block block; //코드 밑에서 NewBlock 생성하고 있음 //그래도 질문
	string drawBlock;


	srand(time(NULL)); //srand시드값 들고온다


	switch (checkBlock)
	{
	case Obstacle:
		rCount = MAXOBSTACLE;
		break;
	case Food:
		rCount = ONEFOOD;
		break;
	default:
		return; //break으로 해두면 무조건 아래과정을 돌아버리는데, 장애물이나 음식이 아니면 아래 과정을 할 필요가X
	}

	drawBlock = Block::CheckBlock(checkBlock);

	for (int count = 0; count < rCount; count++)
	{
		block = block.NewBlock();
		block.SetXY(PATERN_RANDOM, 0, 0);

		//switch
		if (checkBlock == Obstacle)
		{ //장애물:: 한 줄에 1~7개 생성 랜덤. 한 번에 1개씩 생성
			if (RepetitionCheck(block, Snake::snakeList))
				count--;

			obstacleList.push_back(block);
			block.DrawBlock(drawBlock);
		}
		else if (checkBlock == Food)
		{ //먹이:: 함수 한 번에 1개씩 생성
			if (RepetitionCheck(block, obstacleList) || RepetitionCheck(block, Snake::snakeList) || RepetitionCheck(block, foodList))
				count--;
			else
			{
				foodList.push_back(block);
				block.DrawBlock(drawBlock);
			}
		}

	}
}

bool Manager::RepetitionCheck(Block block, list<Block> List) //인자	받으면서 메모리 복사가 일어나고 있다. > 상수,레퍼런스 나 포인터로 변경
{//XY 받아쓰는 구조 OR block에서 PostionCompare()로 이거 처리하는 함수 만드는 것이 더 좋음
	/*for (const Block& block : List) //범위기반 for문 : 0부터 끝까지 다 돌아간다. //const상수화 &레퍼런스 => 복사 일어나지 x 
	{
	}*/
	for (list<Block>::iterator iter = List.begin(); iter != List.end(); iter++)
	{
		if ((block.GetXY().x == iter->GetXY().x) && (block.GetXY().y == iter->GetXY().y)) 
			return true;
	}
	return false;
}

void Manager::ObstacleBorder()
{
	for (int y = 0; y < HEIGHT; y++)
	{
		for (int x = 0; x < WIDTH; x++)
		{
			if ((y == 0) || (y == HEIGHT - 1) || (x == 0) || (x == WIDTH - 1))
			{//가로 양 끝줄 //세로 양 끝줄
				Block block = block.NewBlock();
				block.SetXY(PATERN_APPOINT, x * 2, y);
				block.DrawBlock(Block::CheckBlock(BlockCheck::Obstacle));//인자 값에 따라 리턴 블럭 달라짐
				obstacleList.push_back(block);
			}
		}
		cout << "\n";
	}
}


Manager::~Manager() { }