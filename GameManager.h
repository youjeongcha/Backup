#pragma once
#include"Mecro.h"
#include"DrawManager.h"
#include"Player.h"


enum class OPTIONMENU
{
	MAPSIZE = 1,
	CURSOR,
	STONE,
	UNDO,
	RETURN
};

enum class LOBBYMENU
{
	START = 1,
	OPTION,
	EXIT
};


class GameManager
{
private:
	int m_iTurn;
	int m_iWidth;
	int m_iHeight;
	Player m_Players[(int)PLAYERTYPE::END];
	GAMETYPE m_eGameType;
public:
	void BoardSizeSet();
	void CurPlayerInfoDraw();
	void InputInfoDraw();
	void LobbyDraw();
	void GameMain();
	void Play();
	inline int GetWidth() { return m_iWidth; }
	inline int GetHeight() { return m_iHeight; }
	GameManager();
	~GameManager();
};

