#pragma once
#include "Object.h"

class FireObstacle : public Object
{
private:
public:
	virtual void Draw(HDC hdc) override;
	virtual void Update(float deltaTime, float thisTurn_MoveDistance) override;
	//virtual bool BumpCheck() override;
};