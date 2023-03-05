#pragma once
#include"Mecro.h"
#include<stack>
//Player

#define MAXSTONE 400 //판이 다 채워졌다고 판단할 돌 수량
#define OTHELLO_WINJUGE 10 //턴

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
//쌍방 인클루드 후에 private에 Map m_map; 하면 구조적으로 문제가 생긴다.
//참조하려고 들고 오는 건 가능하다. v방법
//클래스가 있는걸 표시만 하고
//Character.cpp에 Map.h 인클루드


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
	//inline은 무조건 헤더 파일에서만 선언
	//세팅 - 확인
	inline void SetPosition(Position _position, Size _mapSize)
	{//맵 안에 속하는 좌표 지정해두고 시작
		m_mapSize.m_iLeft = _position.m_ix;
		m_mapSize.m_iUp = _position.m_iy;
		m_mapSize.m_iRight = _position.m_ix + _mapSize.m_iWidth * 2;
		m_mapSize.m_iDown = _position.m_iy + _mapSize.m_iHeight;
		m_position.m_ix = _position.m_ix + _mapSize.m_iWidth;// +1; //말그대로 x축 크기
		m_position.m_iy = _position.m_iy + _mapSize.m_iHeight / 2; //y축
	}
	inline void SetCharater(string _strCharacter, string _m_Compare_strCharacter, string _player)
	{
		m_strCharacter = _strCharacter;
		m_Compare_strCharacter = _m_Compare_strCharacter;
		m_player = _player;
	}
	inline bool GetEsc()
	{//Esc 확인
		return bESC;
	}
	inline void SetESC(bool _bESC)
	{//2회차 시 - 초기화 필요
		bESC = _bESC;
	}
	inline void GetTurn(int _m_turn)
	{//승패 조건. 판 다채움 - 40되면, 바둑돌 한 색 - 10턴 이상
		m_turn = _m_turn;
	}

	//기능
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
