#pragma once
#include "Object.h"


class Furniture : public Object
{
protected:


public:
	Furniture();
	~Furniture();

	VOID Initialize() override;
	VOID Update(const FLOAT& deltaTime);
	//VOID Move(const FLOAT& deltaTime);

	virtual VOID SetScale(CONST Vector2& scale) override;
};