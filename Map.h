#pragma once
#include"Mecro.h"
#include"MapDraw.h"
#include"CharDraw.h"

class Map
{
private:
	Position m_position;
	Size m_mapSize;
	CharDraw charDraw;
public:
	void MapDraw();
	void CharDraw();
	Map();
	~Map();
};

