#include "Player.h"
#include"GameManager.h"


void Player::Init(int _iWidth, int _iHeight, PLAYERTYPE _ePlayerType,GameManager* _pGameManager)
{//�� �ڵ��� setting�� ����
	m_ePlayerType = _ePlayerType; //�� ������ Ȯ��
	switch (m_ePlayerType)
	{
	case PLAYERTYPE::WHITE:
		m_strShape = WHITETEAMICON; //string �޴´�. define�̿� "��"
		break;
	case PLAYERTYPE::BLACK:
	default:
		m_strShape = BLACKTEAMICON;
		break;
	}
	m_Cursor.SetPosition(_iWidth / 2, _iHeight / 2, m_strShape); //m_Cursor�� Stone�� ��ü
	m_iUndoCount = MAX_UNDO_COUNT;
	m_vecStoneList.clear();
	m_pGameManager = _pGameManager;
	m_undoStone.Disable(m_pGameManager->GetWidth(), m_pGameManager->GetHeight()); //��� ���� �� ���� ����
}

KEY Player::Input(Player* _enemyPlayer, int _iTurn, GAMETYPE _eGameType)
{//enum���η� �� ����
	while (true)
	{
		m_undoStone.DrawUndoStone(); //������ �� ǥ��
		m_Cursor.DrawStone(); //�־� �� �� ǥ��
		char ch = getch();
		if(CheckStoneList(m_Cursor,true) == false && _enemyPlayer->CheckStoneList(m_Cursor,true) == false)
			m_Cursor.EraseStone(m_pGameManager->GetWidth(),m_pGameManager->GetHeight());
			//�� �ִ� �κи� �����. 
		//CheckStoneList �� ���� ��ġ���� üũ�ϰ� �ƴϸ� �׸���.
		//_enemyPlayer->CheckStoneList ������� �� ������ üũ, �ƴϸ� �׸���.
		switch ((KEY)ch)
		{
		case KEY::LEFT:
			if (m_Cursor.GetX() > 0)//�� �ȿ��� �����̵���
				m_Cursor.SetLeft();
			break;
		case KEY::RIGHT:
			if (m_Cursor.GetX() < m_pGameManager->GetWidth() - 1)//�Ѱ�� �� ũ�⿡ �°�
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
			return KEY::ESC; //ESC�� �Ǵ��ϴ� �� ���� �� ����� enum�̿�
		case KEY::DROP://enter
			if (m_undoStone.Compare(m_Cursor) == false && CheckStoneList(m_Cursor) == false && _enemyPlayer->CheckStoneList(m_Cursor) == false)
				//m_undoStone ������ ǥ�� üũ. ������ �� ���̶� false�� �� �� ����� �Ѵ�.
				//CheckStoneList �̹� ������ �ִ� ������ ����Ʈ
			{ 
				m_undoStone.Disable(m_pGameManager->GetWidth(), m_pGameManager->GetHeight(),true);
				m_Cursor.DrawStone();
				m_vecStoneList.push_back(m_Cursor); //vector�� �ִ´�.
				if (WinCheck(_eGameType,_enemyPlayer, m_pGameManager->GetWidth()*m_pGameManager->GetHeight()))//�� �ڰ� maxStoneSize �ٵ��ǿ� �� �� �� �ִ� �ٵϵ��� ����
					//�ٵ����� �� ä���� ���
					return KEY::WIN; //�ٵ����� �ٵ��� ���� ���� �÷��̾� �Ǵ��� GameManager���� input�� �޾Ƽ�
				else
					return KEY::DROP;
			}
			break;
		case KEY::UNDO://������
			if (_eGameType == GAMETYPE::FIVE_IN_A_ROW && m_iUndoCount > 0 && _iTurn > 1) //�ٵ��� ��쿡�� �۵��ϵ��� //������ Ƚ���� �� 1���̻� ���
			{
				m_iUndoCount--;
				m_undoStone.Disable(m_pGameManager->GetWidth(), m_pGameManager->GetHeight(),true); //������ ǥ��
				return KEY::UNDO;//ǥ�ô� input ���� ���� GameManager����
			}
			break;
		default:
			break;
		}
	}
}

bool Player::CheckStoneList(Stone _stone, bool _bDrawStatus)
{//List�� Ȯ���ϰ� List�� �������� ������ ���� �׸���. //�׸��ٿ� �δ� �ٸ�. ���� �ʿ�.
	if (_bDrawStatus && m_undoStone.Compare(_stone)) //������ ������ Ȯ��
	{
		m_undoStone.DrawUndoStone(); //������ ǥ�� �׸���.
		return true;
	}
	return StoneCheck(_stone, _bDrawStatus); //�� �� ������ �� �׸�. _bDrawStatus�� false�� �� �׸�
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
{//MaxStoneSize  �ٵ��ǿ� �� �� �� �ִ� �ٵϵ��� ����
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
	if (StoneLineCheck(m_Cursor,-1, 0).size() + StoneLineCheck(m_Cursor, 1, 0).size() == 4) //�ٷ� �� �Ʒ� �� �հ賻����
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
{//vector�� �־ ���� ����
	vector<Stone> vecStoneList;
	int iWidth = m_pGameManager->GetWidth(); //m_pGameManager�� cpp�� h �޾Ƽ� //get�̿� ��� �̷���
	int iHeight = m_pGameManager->GetHeight();
	int iCount = 0;
	for (int x = _cursor.GetX() + _addX, y = _cursor.GetY() + _addY; //�� �� ���ؿ��� üũ�� ������ ����. ù��°�� üũ �Ǵ� ��
		(x >= 0 && x < iWidth) && (y >= 0 && y < iHeight); //�� �ȿ� ���� üũ
		x += _addX, y += _addY)
	{//���� �´��� �ɷ�����
		if (StoneCheck(x, y) == false)
			break;
		else
			vecStoneList.push_back(Stone(x, y));
	}
	return vecStoneList;
}

bool Player::StoneCheck(Stone _stone, bool _bDrawStatus)
{//�� �� ������ �� �׸�. _bDrawStatus�� false�� �� �׸�
	//foreach ���� List ó������ ������ ����. ������ ���� ���� �Ұ���. Ȯ�ο�
	for (Stone st : m_vecStoneList)
	{
		if (st.Compare(_stone))
		{//�Ǵܰ� ��ġ�ϴ� ��
			if (_bDrawStatus) //�� 
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
{//vector�� �־ ���� ����
	vector<Stone> vecStoneList;
	vecStoneList = _enemyPlayer->StoneLineCheck(m_Cursor, _addX, _addY);
	if (vecStoneList.size() != 0 && StoneCheck(vecStoneList.back().GetX() + _addX, vecStoneList.back().GetY() + _addY))
		//�񱳳�  true false �Ǻ� ���� �� ������?
	{
		_enemyPlayer->DeleteStoneList(vecStoneList);//�� �� �Դ� �� //�̰� ���� �ּҰ� �޾ƿ´�
		AppendStoneList(vecStoneList); ////�� ��� ���ϰ� �׸���, vector�� �ֱ�
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
			{//foreach�̿��� st�� 
				m_vecStoneList.erase(iter);
				break;
			}
		}
	}
}
void Player::AppendStoneList(vector<Stone> _stoneList)
{//�� ��� ���ϰ� �׸���, vector�� �ֱ�
	for (Stone st : _stoneList)
	{
		st.SetShape(m_strShape);
		st.DrawStone();
		m_vecStoneList.push_back(st);
	}
}