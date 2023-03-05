#include "Player.h"
#include"GameManager.h"


void Player::Init(int _iWidth, int _iHeight, PLAYERTYPE _ePlayerType,GameManager* _pGameManager)
{//내 코드의 setting과 유사
	m_ePlayerType = _ePlayerType; //흰돌 검은돌 확인
	switch (m_ePlayerType)
	{
	case PLAYERTYPE::WHITE:
		m_strShape = WHITETEAMICON; //string 받는다. define이용 "○"
		break;
	case PLAYERTYPE::BLACK:
	default:
		m_strShape = BLACKTEAMICON;
		break;
	}
	m_Cursor.SetPosition(_iWidth / 2, _iHeight / 2, m_strShape); //m_Cursor은 Stone의 객체
	m_iUndoCount = MAX_UNDO_COUNT;
	m_vecStoneList.clear();
	m_pGameManager = _pGameManager;
	m_undoStone.Disable(m_pGameManager->GetWidth(), m_pGameManager->GetHeight()); //어디서 언제 왜 쓰는 건지
}

KEY Player::Input(Player* _enemyPlayer, int _iTurn, GAMETYPE _eGameType)
{//enum으로로 형 가능
	while (true)
	{
		m_undoStone.DrawUndoStone(); //무르기 돌 표시
		m_Cursor.DrawStone(); //둬야 할 돌 표시
		char ch = getch();
		if(CheckStoneList(m_Cursor,true) == false && _enemyPlayer->CheckStoneList(m_Cursor,true) == false)
			m_Cursor.EraseStone(m_pGameManager->GetWidth(),m_pGameManager->GetHeight());
			//돌 있던 부분만 지우기. 
		//CheckStoneList 둔 돌의 위치인지 체크하고 아니면 그린다.
		//_enemyPlayer->CheckStoneList 상대편이 둔 돌인지 체크, 아니면 그린다.
		switch ((KEY)ch)
		{
		case KEY::LEFT:
			if (m_Cursor.GetX() > 0)//판 안에서 움직이도록
				m_Cursor.SetLeft();
			break;
		case KEY::RIGHT:
			if (m_Cursor.GetX() < m_pGameManager->GetWidth() - 1)//한계는 맵 크기에 맞게
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
			return KEY::ESC; //ESC를 판단하는 걸 따로 안 만들고 enum이용
		case KEY::DROP://enter
			if (m_undoStone.Compare(m_Cursor) == false && CheckStoneList(m_Cursor) == false && _enemyPlayer->CheckStoneList(m_Cursor) == false)
				//m_undoStone 무르기 표시 체크. 무르기 할 돌이라 false로 둘 수 없어야 한다.
				//CheckStoneList 이미 놓아져 있는 돌들의 리스트
			{ 
				m_undoStone.Disable(m_pGameManager->GetWidth(), m_pGameManager->GetHeight(),true);
				m_Cursor.DrawStone();
				m_vecStoneList.push_back(m_Cursor); //vector에 넣는다.
				if (WinCheck(_eGameType,_enemyPlayer, m_pGameManager->GetWidth()*m_pGameManager->GetHeight()))//맨 뒤가 maxStoneSize 바둑판에 총 둘 수 있는 바둑돌의 갯수
					//바둑판을 다 채웠을 경우
					return KEY::WIN; //바둑판의 바둑을 많이 가진 플레이어 판단은 GameManager에서 input을 받아서
				else
					return KEY::DROP;
			}
			break;
		case KEY::UNDO://무르기
			if (_eGameType == GAMETYPE::FIVE_IN_A_ROW && m_iUndoCount > 0 && _iTurn > 1) //바둑일 경우에만 작동하도록 //무르기 횟수와 턴 1턴이상 고려
			{
				m_iUndoCount--;
				m_undoStone.Disable(m_pGameManager->GetWidth(), m_pGameManager->GetHeight(),true); //무리기 표시
				return KEY::UNDO;//표시는 input 리턴 받은 GameManager에서
			}
			break;
		default:
			break;
		}
	}
}

bool Player::CheckStoneList(Stone _stone, bool _bDrawStatus)
{//List를 확인하고 List에 존재하지 않으면 돌을 그린다. //그리다와 두다 다름. 구분 필요.
	if (_bDrawStatus && m_undoStone.Compare(_stone)) //무르기 돌인지 확인
	{
		m_undoStone.DrawUndoStone(); //무르기 표시 그린다.
		return true;
	}
	return StoneCheck(_stone, _bDrawStatus); //둘 수 있으면 돌 그림. _bDrawStatus이 false면 안 그림
}

void Player::UndoSet()
{
	if (m_vecStoneList.size() > 0)
	{
		m_undoStone = m_vecStoneList.back();
		m_vecStoneList.pop_back();
	}
}


bool Player::WinCheck(GAMETYPE _eGameType, Player* _enemyPlayer,int MaxStoneSize)
{//MaxStoneSize  바둑판에 총 둘 수 있는 바둑돌의 갯수
	switch (_eGameType)
	{
	case GAMETYPE::FIVE_IN_A_ROW:
		return FiveInARowCheck();
	case GAMETYPE::OTHELLO:
		OthelloLineCheck(_enemyPlayer,-1,0);
		OthelloLineCheck(_enemyPlayer,1,0);
		OthelloLineCheck(_enemyPlayer,0,-1);
		OthelloLineCheck(_enemyPlayer,0,1);
		OthelloLineCheck(_enemyPlayer,-1,-1);
		OthelloLineCheck(_enemyPlayer,1,1);
		OthelloLineCheck(_enemyPlayer,-1,1);
		OthelloLineCheck(_enemyPlayer,1,-1);
		if (m_vecStoneList.size() + _enemyPlayer->m_vecStoneList.size() == MaxStoneSize)
			return true;
		else
			return false;
	}
}
bool Player::FiveInARowCheck()
{
	if (StoneLineCheck(m_Cursor,-1, 0).size() + StoneLineCheck(m_Cursor, 1, 0).size() == 4) //바로 위 아래 돌 합계내도록
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
{//vector에 넣어서 라인 관리
	vector<Stone> vecStoneList;
	int iWidth = m_pGameManager->GetWidth(); //m_pGameManager은 cpp에 h 받아서 //get이용 방법 이렇게
	int iHeight = m_pGameManager->GetHeight();
	int iCount = 0;
	for (int x = _cursor.GetX() + _addX, y = _cursor.GetY() + _addY; //둔 돌 기준에서 체크할 방향의 돌이. 첫번째로 체크 되는 돌
		(x >= 0 && x < iWidth) && (y >= 0 && y < iHeight); //판 안에 범위 체크
		x += _addX, y += _addY)
	{//범위 맞는지 걸러내기
		if (StoneCheck(x, y) == false)
			break;
		else
			vecStoneList.push_back(Stone(x, y));
	}
	return vecStoneList;
}

bool Player::StoneCheck(Stone _stone, bool _bDrawStatus)
{//둘 수 있으면 돌 그림. _bDrawStatus이 false면 안 그림
	//foreach 문법 List 처음부터 끝까지 돈다. 하지만 내용 수정 불가능. 확인용
	for (Stone st : m_vecStoneList)
	{
		if (st.Compare(_stone))
		{//판단과 일치하는 돌
			if (_bDrawStatus) //돌 
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

bool Player::OthelloLineCheck(Player* _enemyPlayer, int _addX, int _addY)
{//vector에 넣어서 라인 관리
	vector<Stone> vecStoneList;
	vecStoneList = _enemyPlayer->StoneLineCheck(m_Cursor, _addX, _addY);
	if (vecStoneList.size() != 0 && StoneCheck(vecStoneList.back().GetX() + _addX, vecStoneList.back().GetY() + _addY))
		//비교나  true false 판별 없는 거 같은데?
	{
		_enemyPlayer->DeleteStoneList(vecStoneList);//적 돌 먹는 것 //이걸 위해 주소값 받아온단
		AppendStoneList(vecStoneList); ////돌 흰검 정하고 그리고, vector에 넣기
	}
	return true;
}

void Player::DeleteStoneList(vector<Stone> _stoneList)
{
	for (Stone st : _stoneList)
	{
		for (auto iter = m_vecStoneList.begin(); iter != m_vecStoneList.end(); iter++)
		{
			if (iter->Compare(st) == true)
			{//foreach이용한 st로 
				m_vecStoneList.erase(iter);
				break;
			}
		}
	}
}
void Player::AppendStoneList(vector<Stone> _stoneList)
{//돌 흰검 정하고 그리고, vector에 넣기
	for (Stone st : _stoneList)
	{
		st.SetShape(m_strShape);
		st.DrawStone();
		m_vecStoneList.push_back(st);
	}
}