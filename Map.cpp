#include "Map.h"



Map::Map()
{
	cout << "¸Ê X ÀÔ·Â :";
	cin >> m_position.m_ix;
	cout << "¸Ê y ÀÔ·Â :";
	cin >> m_position.m_iy;
	cout << "¸Ê °¡·Î ±æÀÌ ÀÔ·Â :";
	cin >> m_mapSize.m_iWidth;
	cout << "¸Ê ¼¼·Î ±æÀÌ ÀÔ·Â :";
	cin >> m_mapSize.m_iHeight;
	m_character.SetPosition(m_position, m_mapSize);
}


void Map::MapDraw()
{
	MapDraw::BoxDraw(m_position.m_ix, m_position.m_iy, m_mapSize.m_iWidth, m_mapSize.m_iHeight);
	m_character.Draw();
	m_character.Move();
}

Map::~Map()
{
}
