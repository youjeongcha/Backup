#pragma once
#include"Player.h"

#define OMOK_WINJUGE 9
#define MAXSTONE 400 //���� �� ä�����ٰ� �Ǵ��� �� ����
#define OTHELLO_WINJUGE 10 //��

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
	int m_turn;
	int m_iGame;
public:
	static string mapLog[MAPMAX][MAPMAX];
	//static���� ���� //string mapLog�� �ΰ��� ���� ������ �Ǵ� �� > ������ �ȵȴ�.
	//string�� �ʱ�ȭ ���ص� �ڵ����� ��
	inline void Setting()
	{
		m_position.m_ix = 0;
		m_position.m_iy = 0;
		m_mapSize.m_iWidth = MAPMAX;
		m_mapSize.m_iHeight = MAPMAX;
		m_BlackPlayer.SetPosition(m_position, m_mapSize);
		m_WhitePlayer.SetPosition(m_position, m_mapSize);
		BoxSetting(mapLog, m_position.m_ix, m_position.m_iy, m_mapSize.m_iWidth, m_mapSize.m_iHeight);
	}

	///
	void Menu();
	//
	void Play();
	bool PlayerTurn(Player* m_NowTurn_Player, Player* m_NextTurn_Player, CHARATER player);
	void ShowInfo();
	//
	void BoxSetting(string mapLog[][MAPMAX], int Start_x, int Start_y, int Width, int Height);
	GameManager();
	~GameManager();
};

