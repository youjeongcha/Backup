#pragma once
#include "BitMapManager.h"
#include <list>

enum SPEED
{
	//SPEED_BACK = 80,
	SPEED_BACK = 140,
};

enum MAP_IMG_XYWH
{
	//儡叼
	IMG_GRASS_X = 0,
	IMG_GRASS_Y = (int)(MAIN_H / 2.6), //(int)(MAIN_H / 2.9f),
	IMG_GRASS_W = MAIN_W + MAIN_X,
	IMG_GRASS_H = (int)(MAIN_H / 2.2f),

	//包吝(7) 
	IMG_SPECTATOR_W = 65,
	//IMG_SPECTATOR_H = 64,
	//IMG_SPECTATOR_Y = IMG_GRASS_Y - IMG_SPECTATOR_H,

	//内尝府
	IMG_ELEPHANT_W = 66,
	IMG_ELEPHANT_H = 67,
	IMG_ELEPHANT_Y = IMG_GRASS_Y - IMG_ELEPHANT_H,
};


enum IMG_BACK
{
	//包吝(7)-内尝府(1)-包吝(7)-内尝府(1)
	IMG_BACK_COUNT = 16,

	//包吝(7)
	//IMG_SPECTATOR_COUNT = 15,

	//内尝府(1)
	IMG_ELEPHANT_FIRST = 7,
	IMG_ELEPHANT_SECOND = 15,
};

class MapDraw
{
private:
	float m_BackIMG_X;
	std::list<IMG> m_BackIMG_List; 

	//硅版
	void DrawGrass(HDC hdc);	//钱
	void DrawBack(HDC hdc);		//包吝+内尝府
public:
	MapDraw();
	~MapDraw();

	void DrawMap(HDC hdc);
	void UpdateBack(float deltaTime, float thisTurn_MoveDistance);

};

