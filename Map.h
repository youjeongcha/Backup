#pragma once
#include"Omok_Character.h"
#include"Othello_Character.h"
//GameManager

enum Game
{
	OMOK,
	OTHELLO 
};


class Map
{
private:
	Position m_position;
	Size m_mapSize;
	Omok_Character m_Omok_BlackCharater;
	Omok_Character m_Omok_WhiteCharater;
	Othello_Character m_Othello_BlackCharater;
	Othello_Character m_Othello_WhiteCharater;
	//Mecro mecro;
	int m_turn;
public:
	static string mapLog[MAPMAX][MAPMAX];
	//static���� ���� //string mapLog�� �ΰ��� ���� ������ �Ǵ� �� > ������ �ȵȴ�.
	//string�� �ʱ�ȭ ���ص� �ڵ����� ��
	void Setting();
	void BoxDraw(int Start_x, int Start_y, int Width, int Height);
	void BoxSetting(int Start_x, int Start_y, int Width, int Height);
	////
	void Menu();
	////
	void Omok_Play();
	bool Omok_PlayerTurn(Omok_Character* m_NowTurn_Charater, Omok_Character* m_NextTurn_Charater);
	void Omok_ShowInfo();
	//
	void Othello_Play();
	bool Othello_PlayerTurn(Othello_Character* m_NowTurn_Charater, Othello_Character* m_NextTurn_Charater);
	void Othello_ShowInfo();
	Map();
	~Map();
};

