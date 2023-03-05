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
	RandomCreate(Obstacle); //��ֹ�::��ȸ��
	Snake::SnakeCreate(BlockCheck::Snake_Head); //�� �Ӹ� ����

	PrintScore(score);
	
	while (true)
	{
		if ((foodList.size() < MAXFOOD) && (clock() - foodClock >= FOODCLCOK))
		{
			RandomCreate(Food); //����::Ƚ������ 10�� �ִ�. �̸��� �ÿ� 1.5�ʿ� �ϳ��� ����
			foodClock = clock();
		}

		//�� �̵� �Է°�
		Snake::SnakeInput();

		//�� �̵� �ð�
		if (clock() - moveClock >= SnakeSpeed) 
		{
			//�� �̵� ���� ��ֹ� üũ
			if ((SnakeInteraction(SREACHLIST::OBSTACLELIST) || (SnakeInteraction(SREACHLIST::SNAKELIST))))
			{//clock �ȿ� �� ������ ��ֹ� �տ� �������ڸ��� GameOver ��������.
				GameOver(score);
				Snake::InputReset();
				return;
			}

			Snake::SnakeMove();
			moveClock = clock();
		}

		//�� �̵� ������ üũ
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

	//list�� �ʱ�ȭ
	obstacleList.clear();
	foodList.clear();
	Snake::snakeList.clear();

	getch(); //Ű �Է� ���� ������ ���.
}


bool Manager::SnakeInteraction(SREACHLIST enList)
{//�� �̵��ϱ� ���� �� Ȯ�� �ϴ� �ڵ� //�� �Ӹ��� ���� ��ǥ ��ġ�� > ����Ʈ ����
	list<Block>* blockList; //������
	XY snakeHead = Snake::snakeList.begin()->GetXY();

	switch (enList)
	{
	case FOODLIST:
		blockList = &foodList; //���� ��ġ üũ > snakeHead ��ǥ �״��
		break;
	case OBSTACLELIST:
		blockList = &obstacleList;
		snakeHead.x += Snake::m_InputXY.x * 2; //�̸� üũ
		snakeHead.y += Snake::m_InputXY.y;
		break;
	case SNAKELIST:
		blockList = &Snake::snakeList;
		snakeHead.x += Snake::m_InputXY.x * 2; //�̸� üũ
		snakeHead.y += Snake::m_InputXY.y;
		break;
	default:
		break;
	}

	for (list<Block>::iterator iter = blockList->begin(); iter != blockList->end(); iter++)
	{
		if ((enList == SNAKELIST) && (Snake::snakeList.size() == 1)) //�� �Ӹ� == �� ����Ʈ ó�� > GameOver�� �ȴ�.
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
{//��ֹ�::��ȸ�� //����::Ƚ������
	int x, y, rCount = 0;
	Block block; //�ڵ� �ؿ��� NewBlock �����ϰ� ���� //�׷��� ����
	string drawBlock;


	srand(time(NULL)); //srand�õ尪 ���´�


	switch (checkBlock)
	{
	case Obstacle:
		rCount = MAXOBSTACLE;
		break;
	case Food:
		rCount = ONEFOOD;
		break;
	default:
		return; //break���� �صθ� ������ �Ʒ������� ���ƹ����µ�, ��ֹ��̳� ������ �ƴϸ� �Ʒ� ������ �� �ʿ䰡X
	}

	drawBlock = Block::CheckBlock(checkBlock);

	for (int count = 0; count < rCount; count++)
	{
		block = block.NewBlock();
		block.SetXY(PATERN_RANDOM, 0, 0);

		//switch
		if (checkBlock == Obstacle)
		{ //��ֹ�:: �� �ٿ� 1~7�� ���� ����. �� ���� 1���� ����
			if (RepetitionCheck(block, Snake::snakeList))
				count--;

			obstacleList.push_back(block);
			block.DrawBlock(drawBlock);
		}
		else if (checkBlock == Food)
		{ //����:: �Լ� �� ���� 1���� ����
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

bool Manager::RepetitionCheck(Block block, list<Block> List) //����	�����鼭 �޸� ���簡 �Ͼ�� �ִ�. > ���,���۷��� �� �����ͷ� ����
{//XY �޾ƾ��� ���� OR block���� PostionCompare()�� �̰� ó���ϴ� �Լ� ����� ���� �� ����
	/*for (const Block& block : List) //������� for�� : 0���� ������ �� ���ư���. //const���ȭ &���۷��� => ���� �Ͼ�� x 
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
			{//���� �� ���� //���� �� ����
				Block block = block.NewBlock();
				block.SetXY(PATERN_APPOINT, x * 2, y);
				block.DrawBlock(Block::CheckBlock(BlockCheck::Obstacle));//���� ���� ���� ���� �� �޶���
				obstacleList.push_back(block);
			}
		}
		cout << "\n";
	}
}


Manager::~Manager() { }