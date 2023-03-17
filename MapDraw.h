#pragma once
#include "framework.h"
#include "BitMapManager.h"
#include <list>

enum SPEED
{
	SPEED_BACK = 50,
};

enum IMG_XYWH
{
	//儡叼
	IMG_GRASS_X = 0,
	IMG_GRASS_Y = (int)(MAIN_H * 0.27f),
	IMG_GRASS_W = MAIN_W + MAIN_X,
	IMG_GRASS_H = MAIN_H - (int)(IMG_GRASS_Y * 2.3f),

	//包吝(7) 
	IMG_SPECTATOR_W = 65,
	IMG_SPECTATOR_H = 64,
	IMG_SPECTATOR_Y = IMG_GRASS_Y - IMG_SPECTATOR_H,

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
	float m_BacIMG_X;
	std::list<IMG> mBackIMG_List;
public:
	MapDraw();
	~MapDraw();

	void DrawGrass(HDC hdc);
	void UpdateSpectator(float deltaTime);
	void DrawSpectator(HDC hdc);
	void DrawRing(HDC hdc);
	void DrawPot(HDC hdc);
	void DrawGoal(HDC hdc);
};

