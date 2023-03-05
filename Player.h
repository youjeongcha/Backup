#pragma once
#include"DrawManager.h"
#include<stack>


//쌍방 인클루드 후에 private에 Map m_map; 하면 구조적으로 문제가 생긴다.
//참조하려고 들고 오는 건 가능하다. v방법
//클래스가 있는걸 표시만 하고
//Character.cpp에 Map.h 인클루드
//맵이 인클루드 하는건 .cpp가 이니기때문에 가능
class GameManager;


class Player
{
private:
	Position m_position;
	Rectingle m_mapSize;
	string m_strCharacter;
	string m_Compare_player_stone;
	string m_player_stone;
	bool bMoveStatus; //없애기★
	bool bESC; //없애기★
	int m_backCount;
	int m_turn; //없애기★ GamenManager에서 함수로 get해서 return받아오기
	stack <Position> m_backXY;
	bool bBackCheck; //없애기★

public:
	//세팅
	inline void SetPosition(Position _position, Size _mapSize)
	{//맵 안에 속하는 좌표 지정해두고 시작
		m_mapSize.m_iLeft = _position.m_ix;
		m_mapSize.m_iUp = _position.m_iy;
		m_mapSize.m_iRight = _position.m_ix + _mapSize.m_iWidth * 2;
		m_mapSize.m_iDown = _position.m_iy + _mapSize.m_iHeight;
		m_position.m_ix = _position.m_ix + _mapSize.m_iWidth;// +1; //말그대로 x축 크기
		m_position.m_iy = _position.m_iy + _mapSize.m_iHeight / 2; //y축
	}
	inline void SetCharater(string _strCharacter, string _m_Compare_player_stone, string _player_stone)
	{
		m_strCharacter = _strCharacter;
		m_Compare_player_stone = _m_Compare_player_stone;
		m_player_stone = _player_stone;
		m_backCount = 5;
	}
	inline bool GetEsc()//★ enum return 이용
	{//Esc 확인
		return bESC;
	}
	inline void SetESC(bool _bESC)//★ enum return 이용
	{//2회차 시 - 초기화 필요
		bESC = _bESC;
	}
	inline void GetTurn(int _m_turn)
	{//1턴까지만 무르기 가능하게 제한
		m_turn = _m_turn;
	}
	inline bool GetBack()//★enum return 이용
	{//무르기 신청 확인
		return bBackCheck;
	}
	inline void SetBack(bool _bBackCheck)
	{
		bBackCheck = _bBackCheck;
	}
	inline void Reset_m_backXY()
	{//스택 초기화
		while (!m_backXY.empty())
		{
			m_backXY.pop();
			if (m_backXY.empty())
				return;
		}
	}

	//기능
	void Draw();
	void ShowPlayerInfo(int _iGame);
	int Move(int _iGame);
	int Turn(int _iGame);
	//오목
	void BackMapDraw(Position* m_temp);
	bool WinCheck(Position m_CheckCount, int m_X1, int m_Y1, int m_X2, int m_Y2);
	int WinCheck(Position m_CheckCount, int m_count, int checkX, int checkY);
	//오델로
	void StoneChange(Position m_CheckCount, int m_X1, int m_Y1, int m_X2, int m_Y2, int m_direction1, int m_direction2);
	void StoneChange(Position m_CheckCount, int checkX, int checkY, int m_direction);
	void WinCheck_StoneCount(int winType);
	Player();
	~Player();
};

