#pragma once
#include"Mecro.h"
#include"MapDraw.h"


enum DIRECTION
{
	DIRECTION_LEFT = 'a',
	DIRECTION_RIGHT = 'd',
	DIRECTION_UP = 'w',
	DIRECTION_DOWN = 's'
};


class Character
{
private:
	string m_strShape;
	Position m_position;
	Rectingle m_mapSize;
public:
	void SetPosition(Position _position,Size _mapSize);
	void Draw();
	void Move();
	Character();
	~Character();
};

