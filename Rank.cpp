#include "Rank.h"

Rank::Rank()
{
	LoadRanking();
}

Rank::~Rank()
{
	rankingList.clear();
}

//�ʿ��� ���ڸ� interface�� ����
//void Rank::RankPrint()
//{
//	int playerRank_Y = INPUTBOX_HEIGHT + 5;
//
//	system("cls");
//	SKY_BLUE
//	MapDraw::BoxDraw(MAPSIZE_SART_X, MAPSIZE_SART_Y - 2, MAPSIZE_END_X, MAPSIZE_END_Y);
//	MapDraw::BoxDraw(INPUTBOX_START_X, MAPSIZE_SART_Y + 1, INPUTBOX_WIDTH, INPUTBOX_HEIGHT); //word �Է� �ڽ�
//	MapDraw::DrawMidText("Ranking", MAPSIZE_END_X, INPUTBOX_HEIGHT);
//	MapDraw::DrawMidText("=================================================================================================================================================== ", MAPSIZE_END_X, INPUTBOX_HEIGHT + 3);
//	MapDraw::DrawMidText("Name                    Score                    Stage", MAPSIZE_END_X, playerRank_Y++);
//
//
//	for (int i = 0; i < rankingList.size(); i++)
//	{
//		if (i == MAXRANK) //�ִ� 10�� ���
//			break;
//
//		MapDraw::DrawPoint(rankingList[i].name, RANKINGPRINT_X_NAME, playerRank_Y);
//		MapDraw::DrawPoint(std::to_string(rankingList[i].score), RANKINGPRINT_X_SCORE, playerRank_Y);
//		MapDraw::DrawPoint(std::to_string(rankingList[i].level), RANKINGPRINT_X_LEVEL, playerRank_Y++);
//	}
//
//	ORIGINAL
//}

void Rank::LoadRanking()
{
	std::ifstream load;
	Ranking ranking;

	//��ŷ ��������
	load.open("SaveRanking.txt");
	if (load.is_open())
	{
		while (!load.eof())
		{
			load >> ranking.name;
			load >> ranking.score;
			load >> ranking.level;

			rankingList.push_back(ranking);
		}
		load.close();
	}
}

//�������� �ΰ� ����. sort�� ��� �Լ������� �˾Ƶ� �����(ex.GameManager class) sort���� ã�� �� ��� �������ִ� �ͺ��� ����.
bool sortting(Ranking ranking_High, Ranking ranking_Low)
{//ù��°�� ���°� �� ũ�ٴ°� �������ϰ�. �´��� true false üũ
	if (ranking_High.level < ranking_Low.level)
		return false;
	else
	{
		if (ranking_High.level == ranking_Low.level)
		{
			if (ranking_High.score > ranking_Low.score)
				return true;
			else
				return false;
		}
		return true;
	}
}

void Rank::SaveSortRanking(int stageLevel, std::string playerName, int playerScore)
{
	std::ifstream load;
	std::ofstream save;
	Ranking ranking;
	int max_count;
	
	//�̹� ���� ������ ����
	ranking.name = playerName;
	ranking.score = playerScore;
	ranking.level = stageLevel - 1; //���� ������ Stage �Լ����� stagelevel++�� ����ؼ� -1�� �ʿ��ϴ�.
	rankingList.push_back(ranking);

	//��ŷ ���� 
	sort(rankingList.begin(), rankingList.end(), sortting); // �߰��� �Լ� �־��ָ� ���ϴ� ���� �������� ���� ���� //���ۺ��� ������ �ּҸ� ����

	//algorithm ��� ������ �� �߿��� �ּڰ��� �������ִ� ��ũ�� �Լ�
	max_count = min(rankingList.size(), 10);

	//��ŷ ����;
	save.open("SaveRanking.txt");
	if (save.is_open())
	{
		for (int i = 0; i < max_count; i++)
		{
			//if (i == MAXRANK) //10�� ������ ����
			//	break;

			save << rankingList[i].name << " ";
			save << rankingList[i].score << " ";
			save << rankingList[i].level;

			//load���� while(!load.eof)�ϸ� endl���� ������ �� ������ ���. �ߺ� ���
			if (i != max_count - 1) //0~8������ endl ���. 9�� ���X
				save << std::endl;
		}
		save.close();
	}
}