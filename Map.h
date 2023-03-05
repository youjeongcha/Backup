#pragma once
#include"Mecro.h"
#include"MapDraw.h"
class Map
{
private:
	Position m_position;
	Size m_mapSize;
public:
	void MapDraw();
	Map();
	~Map();
};

