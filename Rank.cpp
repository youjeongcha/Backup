#include "Rank.h"

Rank::Rank()
{
	LoadRanking();
}

Rank::~Rank()
{
	rankingList.clear();
}

//필요한 인자만 interface로 전달
//void Rank::RankPrint()
//{
//	int playerRank_Y = INPUTBOX_HEIGHT + 5;
//
//	system("cls");
//	SKY_BLUE
//	MapDraw::BoxDraw(MAPSIZE_SART_X, MAPSIZE_SART_Y - 2, MAPSIZE_END_X, MAPSIZE_END_Y);
//	MapDraw::BoxDraw(INPUTBOX_START_X, MAPSIZE_SART_Y + 1, INPUTBOX_WIDTH, INPUTBOX_HEIGHT); //word 입력 박스
//	MapDraw::DrawMidText("Ranking", MAPSIZE_END_X, INPUTBOX_HEIGHT);
//	MapDraw::DrawMidText("=================================================================================================================================================== ", MAPSIZE_END_X, INPUTBOX_HEIGHT + 3);
//	MapDraw::DrawMidText("Name                    Score                    Stage", MAPSIZE_END_X, playerRank_Y++);
//
//
//	for (int i = 0; i < rankingList.size(); i++)
//	{
//		if (i == MAXRANK) //최대 10명 출력
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

	//랭킹 가져오기
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

//전역으로 두고 쓰기. sort가 어느 함수인지는 알아도 어디의(ex.GameManager class) sort인지 찾을 수 없어서 설정해주는 것보다 전역.
bool sortting(Ranking ranking_High, Ranking ranking_Low)
{//첫번째로 들어온게 더 크다는걸 전제로하고. 맞는지 true false 체크
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
	
	//이번 저장 데이터 저장
	ranking.name = playerName;
	ranking.score = playerScore;
	ranking.level = stageLevel - 1; //게임 돌리는 Stage 함수에서 stagelevel++로 사용해서 -1이 필요하다.
	rankingList.push_back(ranking);

	//랭킹 정렬 
	sort(rankingList.begin(), rankingList.end(), sortting); // 추가로 함수 넣어주면 원하는 정렬 기준으로 정렬 가능 //시작부터 끝까지 주소를 정렬

	//algorithm 헤더 파일의 둘 중에서 최솟값을 리턴해주는 매크로 함수
	max_count = min(rankingList.size(), 10);

	//랭킹 저장;
	save.open("SaveRanking.txt");
	if (save.is_open())
	{
		for (int i = 0; i < max_count; i++)
		{
			//if (i == MAXRANK) //10명 까지만 저장
			//	break;

			save << rankingList[i].name << " ";
			save << rankingList[i].score << " ";
			save << rankingList[i].level;

			//load에서 while(!load.eof)하면 endl으로 마지막 줄 정보가 없어서. 중복 출력
			if (i != max_count - 1) //0~8까지만 endl 출력. 9는 출력X
				save << std::endl;
		}
		save.close();
	}
}