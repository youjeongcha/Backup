#include "Map.h"



Map::Map()
{
	cout << "�� X �Է� :";
	cin >> m_position.m_ix;
	cout << "�� y �Է� :";
	cin >> m_position.m_iy;
	cout << "�� ���� ���� �Է� :";
	cin >> m_mapSize.m_iWidth;
	cout << "�� ���� ���� �Է� :";
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
