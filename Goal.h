#pragma once
#include "Object.h"

enum GOAL_IMG
{
	GOAL_IMG_W = 60,
	GOAL_IMG_H = 50,

	GOAL_IMG_ARRIVE_X = MAIN_W - 150,
};

class Goal : public Object
{
private:
	bool m_EndCheck;
public:
	Goal();
	~Goal();
	virtual void Draw(HDC hdc) override;
	virtual void Update(float deltaTime, float thisTurn_MoveDistance) override;

	bool Get_EndCheck() { return m_EndCheck; }
	//virtual bool BumpCheck() override;
};