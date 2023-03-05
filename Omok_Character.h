#pragma once
#include"Mecro.h"
#include<stack>
//Player

#define OMOK_WINJUGE 9 //��


class Map;
	//�ֹ� ��Ŭ��� �Ŀ� private�� Map m_map; �ϸ� ���������� ������ �����.
	//�����Ϸ��� ��� ���� �� �����ϴ�. v���
	//Ŭ������ �ִ°� ǥ�ø� �ϰ�
	//Character.cpp�� Map.h ��Ŭ���
	//���� ��Ŭ��� �ϴ°� .cpp�� �̴ϱ⶧���� ����

class Omok_Character
{
private:
	Position m_position;
	Rectingle m_mapSize;
	string m_strCharacter;
	//Mecro mecro;
	string m_player;
	bool bMoveStatus;
	bool bESC;
	int m_backCount;
	int m_turn;
	stack <Position> m_backXY;
	bool bBackCheck;

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
	inline void SetCharater(string _strCharacter, string _player)
	{
		m_strCharacter = _strCharacter;
		m_player = _player;
		m_backCount = 5;
	}
	inline bool GetEsc()
	{//Esc Ȯ��
		return bESC;
	}
	inline void SetESC(bool _bESC)
	{//2ȸ�� �� - �ʱ�ȭ �ʿ�
		bESC = _bESC;
	}
	inline void GetBackTurn(int _m_turn)
	{//1�ϱ����� ������ �����ϰ� ����
		m_turn = _m_turn;
	}
	inline bool GetBack()
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
	void BackMapDraw(Position* m_temp);
	string MapDraw(int m_x, int m_y);
	string MapDrawPart(int m_x, string part1, string part2, string part3);
	void ShowInfo();
	void Move();
	bool WinCheck(Position m_CheckCount, int m_X1, int m_Y1, int m_X2, int m_Y2);
	int WinCheck(Position m_CheckCount, int m_count, int checkX, int checkY);
	void Turn();
	Omok_Character();
	~Omok_Character();
};

