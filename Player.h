#pragma once
#include"DrawManager.h"
#include<stack>


//�ֹ� ��Ŭ��� �Ŀ� private�� Map m_map; �ϸ� ���������� ������ �����.
//�����Ϸ��� ��� ���� �� �����ϴ�. v���
//Ŭ������ �ִ°� ǥ�ø� �ϰ�
//Character.cpp�� Map.h ��Ŭ���
//���� ��Ŭ��� �ϴ°� .cpp�� �̴ϱ⶧���� ����
class GameManager;


class Player
{
private:
	Position m_position;
	Rectingle m_mapSize;
	string m_strCharacter;
	string m_Compare_player_stone;
	string m_player_stone;
	bool bMoveStatus; //���ֱ��
	bool bESC; //���ֱ��
	int m_backCount;
	int m_turn; //���ֱ�� GamenManager���� �Լ��� get�ؼ� return�޾ƿ���
	stack <Position> m_backXY;
	bool bBackCheck; //���ֱ��

public:
	//����
	inline void SetPosition(Position _position, Size _mapSize)
	{//�� �ȿ� ���ϴ� ��ǥ �����صΰ� ����
		m_mapSize.m_iLeft = _position.m_ix;
		m_mapSize.m_iUp = _position.m_iy;
		m_mapSize.m_iRight = _position.m_ix + _mapSize.m_iWidth * 2;
		m_mapSize.m_iDown = _position.m_iy + _mapSize.m_iHeight;
		m_position.m_ix = _position.m_ix + _mapSize.m_iWidth;// +1; //���״�� x�� ũ��
		m_position.m_iy = _position.m_iy + _mapSize.m_iHeight / 2; //y��
	}
	inline void SetCharater(string _strCharacter, string _m_Compare_player_stone, string _player_stone)
	{
		m_strCharacter = _strCharacter;
		m_Compare_player_stone = _m_Compare_player_stone;
		m_player_stone = _player_stone;
		m_backCount = 5;
	}
	inline bool GetEsc()//�� enum return �̿�
	{//Esc Ȯ��
		return bESC;
	}
	inline void SetESC(bool _bESC)//�� enum return �̿�
	{//2ȸ�� �� - �ʱ�ȭ �ʿ�
		bESC = _bESC;
	}
	inline void GetTurn(int _m_turn)
	{//1�ϱ����� ������ �����ϰ� ����
		m_turn = _m_turn;
	}
	inline bool GetBack()//��enum return �̿�
	{//������ ��û Ȯ��
		return bBackCheck;
	}
	inline void SetBack(bool _bBackCheck)
	{
		bBackCheck = _bBackCheck;
	}
	inline void Reset_m_backXY()
	{//���� �ʱ�ȭ
		while (!m_backXY.empty())
		{
			m_backXY.pop();
			if (m_backXY.empty())
				return;
		}
	}

	//���
	void Draw();
	void ShowPlayerInfo(int _iGame);
	int Move(int _iGame);
	int Turn(int _iGame);
	//����
	void BackMapDraw(Position* m_temp);
	bool WinCheck(Position m_CheckCount, int m_X1, int m_Y1, int m_X2, int m_Y2);
	int WinCheck(Position m_CheckCount, int m_count, int checkX, int checkY);
	//������
	void StoneChange(Position m_CheckCount, int m_X1, int m_Y1, int m_X2, int m_Y2, int m_direction1, int m_direction2);
	void StoneChange(Position m_CheckCount, int checkX, int checkY, int m_direction);
	void WinCheck_StoneCount(int winType);
	Player();
	~Player();
};

