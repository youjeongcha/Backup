#pragma once
#include"Player.h"
#include<fstream>

#define OMOK_WINJUGE 9
#define MAXSTONE 400 //���� �� ä�����ٰ� �Ǵ��� �� ����
#define OTHELLO_WINJUGE 10 //��

#define BACKCOUNT 5

enum DIRECTION_CHECK
{
	C_UP,
	C_DOWN,
	C_LEFT,
	C_RIGHT,
	C_CROSS1,
	C_CROSS2,
	C_CROSS3,
	C_CROSS4
};

class GameManager
{
private:
	Position m_position;
	Size m_mapSize;
	Player m_BlackPlayer;
	Player m_WhitePlayer;
	int m_iGame;
	int CharaterTurn;
	int m_ContinueCheck;
public:
	static string mapLog[MAPMAX][MAPMAX];
	static int turn;
	//static���� ���� //string mapLog�� �ΰ��� ���� ������ �Ǵ� �� > ������ �ȵȴ�.
	//string�� �ʱ�ȭ ���ص� �ڵ����� ��
	void Setting()
	{
		m_position.m_ix = 0;
		m_position.m_iy = 0;
		m_mapSize.m_iWidth = MAPMAX;
		m_mapSize.m_iHeight = MAPMAX;
		m_BlackPlayer.SetPosition(m_position, m_mapSize);
		m_WhitePlayer.SetPosition(m_position, m_mapSize);
		BoxSetting(mapLog, m_position.m_ix, m_position.m_iy, m_mapSize.m_iWidth, m_mapSize.m_iHeight);
	}
	void Reset_stoneLog()
	{//���� �ʱ�ȭ
		while (!Player::stoneLog.empty())
		{
			Player::stoneLog.pop();
			if (Player::stoneLog.empty())
				return;
		}
	}

	///
	void Menu();
	//stack <Position> ContinueLoad(ifstream loadOption, int iTmp, stack <Position> _Temp);
	//
	void Play(int ContinueCheck);
	bool PlayerTurn(Player* m_NowTurn_Player, Player* m_NextTurn_Player, CHARATER player, int ContinueCheck);
	void ShowInfo();
	//
	void BoxSetting(string mapLog[][MAPMAX], int Start_x, int Start_y, int Width, int Height);
	GameManager();
	~GameManager();
};