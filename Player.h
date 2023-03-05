#pragma once
#include "Mecro.h"

//#define MAXLIFE 10 //�÷��̾� �ִ� ���
//define�� �ٸ� ������ ��������� MAXLIFE �������� �ƴ϶� 10���� ���� ��� ����

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
	//��� ����
	void DecreasePlayerLife();

	int Get_PlayerLife() const { return mLife; };
	int Get_PlayerScore() const { return mScore; };
	std::string Get_PlayerName() const { return mName; };

	void Set_PlayerName(std::string _Nmae) { mName = _Nmae; };
	void Set_PlayerScore(int _Score) { mScore = _Score; };
	void Set_PlayerLife(int _Life) { mLife = _Life; };
};

