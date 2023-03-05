#pragma once
#include "Mecro.h"

//#define MAXLIFE 10 //플레이어 최대 목숨
//define은 다른 곳에서 디버깅히면 MAXLIFE 변수명이 아니라 10으로 떠서 사용 지양

enum MAXLIFE
{
	MAXLIFE = 10,
};

class Player
{
private:
	int mLife;
	int mScore;
	std::string mName;
public:
	Player();
	~Player();

	void InitalSetting();
	//목숨 감소
	void DecreasePlayerLife();

	int Get_PlayerLife() const { return mLife; };
	int Get_PlayerScore() const { return mScore; };
	std::string Get_PlayerName() const { return mName; };

	void Set_PlayerName(std::string _Nmae) { mName = _Nmae; };
	void Set_PlayerScore(int _Score) { mScore = _Score; };
	void Set_PlayerLife(int _Life) { mLife = _Life; };
};

