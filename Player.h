#pragma once
#include"Mecro.h"
#include"DrawManager.h"
#include"Stone.h"
#include<vector>

#define BLACKTEAMICON "○"
#define WHITETEAMICON "●"
#define MAX_UNDO_COUNT 5


enum class PLAYERTYPE
{
	WHITE,
	BLACK,
	END
};

class GameManager;
class Player
{
private:
	vector<Stone> m_vecStoneList; //플레이어가 돌 하나하나를 List에 들고 있다.
	Stone m_undoStone; //무르기 표시가 undoStone
	string m_strShape;
	Stone m_Cursor; //현재 움직이는 돌
	int m_iUndoCount;
	PLAYERTYPE m_ePlayerType;
	GameManager* m_pGameManager;
public:
	inline int GetUndoCount() { return m_iUndoCount; }
	inline int GetStoneCount() { return m_vecStoneList.size(); }
	void Init(int _iWidth, int _iHeight, PLAYERTYPE _ePlayerType,GameManager* _pGameManager);
	KEY Input(Player* _enemyPlayer,int _iTurn,GAMETYPE _eGameType); //enum으로로 형 가능
	bool CheckStoneList(Stone stone, bool _bDrawStatus = false);
	void UndoSet();
	bool WinCheck(GAMETYPE _eGameType,Player* _enemyPlayer, int MaxStoneSize);
	bool FiveInARowCheck();
	bool OthelloLineCheck(Player* _enemyPlayer, int _addX, int _addY);
	bool StoneCheck(Stone _stone, bool _bDrawStatus = false);
	bool StoneCheck(int _ix,int _iy);
	void DeleteStoneList(vector<Stone> _stoneList);
	void AppendStoneList(vector<Stone> _stoneList);
	vector<Stone> StoneLineCheck(Stone _cursor, int _addX, int _addY);
};

