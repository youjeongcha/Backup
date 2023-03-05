#include "Player.h"
#include"GameManager.h"


void Player::Init(int _iWidth, int _iHeight, PLAYERTYPE _ePlayerType,GameManager* _pGameManager, GAMETYPE _eGameType)
{
	m_ePlayerType = _ePlayerType;
	switch (m_ePlayerType)
	{
	case PLAYERTYPE::WHITE:
		m_strShape = WHITETEAMICON;
		break;
	case PLAYERTYPE::BLACK:
	default:
		m_strShape = BLACKTEAMICON;
		break;
	}
	m_Cursor.SetPosition(_iWidth / 2, _iHeight / 2, m_strShape);
	m_iUndoCount = MAX_UNDO_COUNT;
	m_vecStoneList.clear();
	m_pGameManager = _pGameManager;
	m_undoStone.Disable(m_pGameManager->GetWidth(), m_pGameManager->GetHeight());
	if (_eGameType == GAMETYPE::OTHELLO)
	{
		switch (m_ePlayerType)
		{
		case PLAYERTYPE::WHITE:
			m_vecStoneList.push_back(Stone(_iWidth / 2 - 1, _iHeight / 2 - 1, m_strShape));
			m_vecStoneList.back().DrawStone();
			m_vecStoneList.push_back(Stone(_iWidth / 2, _iHeight / 2, m_strShape));
			m_vecStoneList.back().DrawStone();
			break;
		case PLAYERTYPE::BLACK:
			m_vecStoneList.push_back(Stone(_iWidth / 2 - 1, _iHeight / 2, m_strShape));
			m_vecStoneList.back().DrawStone();
			m_vecStoneList.push_back(Stone(_iWidth / 2, _iHeight / 2 - 1, m_strShape));
			m_vecStoneList.back().DrawStone();
			break;
		default:
			break;
		}
	}
}

void Player::DropStone()
{
	m_undoStone.Disable(m_pGameManager->GetWidth(), m_pGameManager->GetHeight(), true);
	m_Cursor.DrawStone();
	m_vecStoneList.push_back(m_Cursor);
}

KEY Player::Input(Player* _enemyPlayer, int _iTurn, GAMETYPE _eGameType)
{
	if (_eGameType == GAMETYPE::OTHELLO && DropCheck(_enemyPlayer) == false)
		return KEY::PASS;
	while (true)
	{
		m_undoStone.DrawUndoStone();
		m_Cursor.DrawStone();
		char ch = getch();
		if(CheckStoneList(m_Cursor,true) == false && _enemyPlayer->CheckStoneList(m_Cursor,true) == false)
			m_Cursor.EraseStone(m_pGameManager->GetWidth(),m_pGameManager->GetHeight());
		switch ((KEY)ch)
		{
		case KEY::LEFT:
			if (m_Cursor.GetX() > 0)
				m_Cursor.SetLeft();
			break;
		case KEY::RIGHT:
			if (m_Cursor.GetX() < m_pGameManager->GetWidth() - 1)
				m_Cursor.SetRight();
			break;
		case KEY::UP:
			if (m_Cursor.GetY() > 0)
				m_Cursor.SetUp();
			break;
		case KEY::DOWN:
			if (m_Cursor.GetY() < m_pGameManager->GetHeight() - 1)
				m_Cursor.SetDown();
			break;
		case KEY::ESC:
			return KEY::ESC;
		case KEY::DROP:
			if (m_undoStone.Compare(m_Cursor) == false && CheckStoneList(m_Cursor) == false && _enemyPlayer->CheckStoneList(m_Cursor) == false)
			{
				switch (_eGameType)
				{
				case GAMETYPE::FIVE_IN_A_ROW:
					DropStone();
					if (FiveInARowCheck())
						return KEY::WIN;
					else
						return KEY::DROP;
					break;
				case GAMETYPE::OTHELLO:
					if (OthelloCheck(m_Cursor,_enemyPlayer))
					{
						DropStone();
						return KEY::DROP;
					}
					break;
				}
			}
			break;
		case KEY::UNDO:
			if (_eGameType == GAMETYPE::FIVE_IN_A_ROW && m_iUndoCount > 0 && _iTurn > 1)
			{
				m_iUndoCount--;
				m_undoStone.Disable(m_pGameManager->GetWidth(), m_pGameManager->GetHeight(),true);
				return KEY::UNDO;
			}
			break;
		default:
			break;
		}
	}
}

bool Player::CheckStoneList(Stone _stone, bool _bDrawStatus)
{
	if (_bDrawStatus && m_undoStone.Compare(_stone))
	{
		m_undoStone.DrawUndoStone();
		return true;
	}
	return StoneCheck(_stone, _bDrawStatus);
}

void Player::UndoSet()
{
	if (m_vecStoneList.size() > 0)
	{
		m_undoStone = m_vecStoneList.back();
		m_vecStoneList.pop_back();
	}
}

bool Player::OthelloCheck(Stone _cursor,Player* _enemyPlayer, bool Check)
{
	int count = 0;
	count += OthelloLineCheck(_cursor,_enemyPlayer, -1, 0, Check);
	count += OthelloLineCheck(_cursor, _enemyPlayer, 1, 0, Check);
	count += OthelloLineCheck(_cursor, _enemyPlayer, 0, -1, Check);
	count += OthelloLineCheck(_cursor, _enemyPlayer, 0, 1, Check);
	count += OthelloLineCheck(_cursor, _enemyPlayer, -1, -1, Check);
	count += OthelloLineCheck(_cursor, _enemyPlayer, 1, 1, Check);
	count += OthelloLineCheck(_cursor, _enemyPlayer, -1, 1, Check);
	count += OthelloLineCheck(_cursor, _enemyPlayer, 1, -1, Check);
	if (count == 0)
		return false;
	else
		return true;
}

bool Player::FiveInARowCheck()
{
	if (StoneLineCheck(m_Cursor,-1, 0).size() + StoneLineCheck(m_Cursor, 1, 0).size() == 4)
		return true;
	else if (StoneLineCheck(m_Cursor, 0, -1).size() + StoneLineCheck(m_Cursor, 0, 1).size() == 4)
		return true;
	else if (StoneLineCheck(m_Cursor, -1, -1).size() + StoneLineCheck(m_Cursor, 1, 1).size() == 4)
		return true;
	else if (StoneLineCheck(m_Cursor, 1, -1).size() + StoneLineCheck(m_Cursor, -1, 1).size() == 4)
		return true;
	else return false;
}


vector<Stone> Player::StoneLineCheck(Stone _cursor,int _addX, int _addY)
{
	vector<Stone> vecStoneList;
	int iWidth = m_pGameManager->GetWidth();
	int iHeight = m_pGameManager->GetHeight();
	int iCount = 0;
	for (int x = _cursor.GetX() + _addX, y = _cursor.GetY() + _addY;
		(x >= 0 && x < iWidth) && (y >= 0 && y < iHeight);
		x += _addX, y += _addY)
	{
		if (StoneCheck(x, y) == false)
			break;
		else
			vecStoneList.push_back(Stone(x, y));
	}
	return vecStoneList;
}

bool Player::StoneCheck(Stone _stone, bool _bDrawStatus)
{

	for (Stone st : m_vecStoneList)
	{
		if (st.Compare(_stone))
		{
			if (_bDrawStatus)
				st.DrawStone();
			return true;
		}
	}
	return false;
}
bool Player::StoneCheck(int _ix, int _iy)
{
	for (Stone st : m_vecStoneList)
	{
		if (st.Compare(_ix, _iy))
		{
			return true;
		}
	}
	return false;
}


bool Player::DropOthelloCheck(Stone stone, Player* _enemyPlayer)
{
	Stone tmp;
	for (int y = -1; y <= 1; y++)
	{
		for (int x = -1; x <= 1; x++)
		{
			if (x == 0 && y == 0)
				continue;
			tmp.SetPosition(stone.GetX() + x, stone.GetY() + y);
			if (tmp.GetX() <= -1 || tmp.GetX() >= m_pGameManager->GetWidth())
				continue;
			if (tmp.GetY() <= -1 || tmp.GetY() >= m_pGameManager->GetHeight())
				continue;
			if (CheckStoneList(tmp) == true || _enemyPlayer->CheckStoneList(tmp) == true)
				continue;
			if (OthelloCheck(tmp, _enemyPlayer,true) == true)
				return true;
		}
	}
	return false;
}

bool Player::DropCheck(Player* _enemyPlayer)
{
	vector<Stone> _EnemyStoneList = _enemyPlayer->getStoneList();
	for (Stone stone: _EnemyStoneList)
	{
		if (DropOthelloCheck(stone, _enemyPlayer) == true)
			return true;
	}
	return false;
}

bool Player::OthelloLineCheck(Stone _cursor,Player* _enemyPlayer, int _addX, int _addY,bool Check)
{
	vector<Stone> vecStoneList;
	vecStoneList = _enemyPlayer->StoneLineCheck(_cursor, _addX, _addY);
	if (vecStoneList.size() != 0 && StoneCheck(vecStoneList.back().GetX() + _addX, vecStoneList.back().GetY() + _addY))
	{
		if (Check == false)
		{
			_enemyPlayer->DeleteStoneList(vecStoneList);
			AppendStoneList(vecStoneList);
		}
		return true;
	}
	else
		return false;
}

void Player::DeleteStoneList(vector<Stone> _stoneList)
{
	for (Stone st : _stoneList)
	{
		for (auto iter = m_vecStoneList.begin(); iter != m_vecStoneList.end(); iter++)
		{
			if (iter->Compare(st) == true)
			{
				m_vecStoneList.erase(iter);
				break;
			}
		}
	}
}
void Player::AppendStoneList(vector<Stone> _stoneList)
{
	for (Stone st : _stoneList)
	{
		st.SetShape(m_strShape);
		st.DrawStone();
		m_vecStoneList.push_back(st);
	}
}