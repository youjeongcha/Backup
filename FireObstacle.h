#pragma once
#include "Object.h"

class FireObstacle : public Object
{
private:
public:
	virtual void Draw(HDC hdc) override;
	virtual void Update(float thisTurn_MoveDistance, float _Prev_MoveDistance) override;
	virtual bool ColliderCheck() override;
};