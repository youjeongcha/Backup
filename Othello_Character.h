#pragma once
#include"Mecro.h"
#include<stack>
//Player

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

class Map;
//�ֹ� ��Ŭ��� �Ŀ� private�� Map m_map; �ϸ� ���������� ������ �����.
//�����Ϸ��� ��� ���� �� �����ϴ�. v���
//Ŭ������ �ִ°� ǥ�ø� �ϰ�
//Character.cpp�� Map.h ��Ŭ���


class Othello_Character
{
private:
	Position m_position;
	Rectingle m_mapSize;
	string m_strCharacter;
	string m_Compare_strCharacter;
	Mecro mecro;
	string m_player;
	bool bMoveStatus;
	bool bESC;
	int m_turn;

public:
	//inline�� ������ ��� ���Ͽ����� ����
	//���� - Ȯ��
	inline void SetPosition(Position _position, Size _mapSize)
	{//�� �ȿ� ���ϴ� ��ǥ �����صΰ� ����
		m_mapSize.m_iLeft = _position.m_ix;
		m_mapSize.m_iUp = _position.m_iy;
		m_mapSize.m_iRight = _position.m_ix + _mapSize.m_iWidth * 2;
		m_mapSize.m_iDown = _position.m_iy + _mapSize.m_iHeight;
		m_position.m_ix = _position.m_ix + _mapSize.m_iWidth;// +1; //���״�� x�� ũ��
		m_position.m_iy = _position.m_iy + _mapSize.m_iHeight / 2; //y��
	}
	inline void SetCharater(string _strCharacter, string _m_Compare_strCharacter, string _player)
	{
		m_strCharacter = _strCharacter;
		m_Compare_strCharacter = _m_Compare_strCharacter;
		m_player = _player;
	}
	inline bool GetEsc()
	{//Esc Ȯ��
		return bESC;
	}
	inline void SetESC(bool _bESC)
	{//2ȸ�� �� - �ʱ�ȭ �ʿ�
		bESC = _bESC;
	}
	inline void GetTurn(int _m_turn)
	{//���� ����. �� ��ä�� - 40�Ǹ�, �ٵϵ� �� �� - 10�� �̻�
		m_turn = _m_turn;
	}

	//���
	void Draw();
	void ShowInfo();
	void Move();
	void StoneChange(Position m_CheckCount, int m_X1, int m_Y1, int m_X2, int m_Y2, int m_direction1, int m_direction2);
	void StoneChange(Position m_CheckCount, int checkX, int checkY, int m_direction);
	void Turn();
	void WinCheck_StoneCount(int winType);
	Othello_Character();
	~Othello_Character();
};
