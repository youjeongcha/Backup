#pragma once
#include"Mecro.h"
#include"MapDraw.h"
#include"Character.h"
class Map
{
private:
	Position m_position;
	Size m_mapSize;
	Character m_character;
public:
	void MapDraw();
	Map();
	~Map();
};

