#pragma once
#include"Mecro.h"
#include"DrawManager.h"
#include"Stone.h"
#include<vector>

#define BLACKTEAMICON "¡Û"
#define WHITETEAMICON "¡Ü"
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
	vector<Stone> m_vecStoneList;
	Stone m_undoStone;
	string m_strShape;
	Stone m_Cursor;
	int m_iUndoCount;
	PLAYERTYPE m_ePlayerType;
	GameManager* m_pGameManager;
public:
	inline int GetUndoCount() { return m_iUndoCount; }
	inline int GetStoneCount() { return m_vecStoneList.size(); }
	inline vector<Stone> getStoneList() { return m_vecStoneList; }
	void Init(int _iWidth, int _iHeight, PLAYERTYPE _ePlayerType,GameManager* _pGameManager, GAMETYPE _eGameType);
	KEY Input(Player* _enemyPlayer,int _iTurn,GAMETYPE _eGameType);
	bool CheckStoneList(Stone stone, bool _bDrawStatus = false);
	void UndoSet();
	bool FiveInARowCheck();
	bool OthelloLineCheck(Stone _cursor,Player* _enemyPlayer, int _addX, int _addY, bool Check);
	bool StoneCheck(Stone _stone, bool _bDrawStatus = false);
	bool StoneCheck(int _ix,int _iy);
	void DeleteStoneList(vector<Stone> _stoneList);
	void AppendStoneList(vector<Stone> _stoneList);
	vector<Stone> StoneLineCheck(Stone _cursor, int _addX, int _addY);
	bool OthelloCheck(Stone _cursor,Player* _enemyPlayer, bool Check = false);
	void DropStone();
	bool DropCheck(Player* _enemyPlayer);
	bool DropOthelloCheck(Stone stone, Player* _enemyPlayer);
};

