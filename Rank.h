#pragma once
#include "MapDraw.h"
#include "Player.h"
#include <algorithm>

enum MAXRANK
{
	MAXRANK = 10,
};


struct Ranking
{
	std::string name;
	int score;
	int level;
};

class Rank
{
private:
	std::vector<Ranking> rankingList;
public:
	Rank();
	~Rank();
	//void RankPrint();
	void LoadRanking();
	void SaveSortRanking(int stageLevel, std::string playerName, int playerScore);

	std::vector<Ranking> Get_RankingList() { return rankingList; }
};
