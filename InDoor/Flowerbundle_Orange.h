#pragma once
#include "Object.h"

class Flowerbundle_Orange : public Object
{
private:
	FRUITS_GROWTH growthRate;
	bool seedPlanting, watering; //이미 씨앗을 심음, 이미 물을 줌 확인
	float m_elapsedHour, m_elapsedSec, m_elapsedMin; // 식물 성장 - 경과 시간 (초, 분 단위)

public:
	Flowerbundle_Orange();
	Flowerbundle_Orange(const ObjectData& dataSet, int index);
	~Flowerbundle_Orange();
	VOID Initialize() override;
	VOID Move(const FLOAT& deltaTime) override;
	void PassOfthe_TimeChangeBitmap() override;
	void Update(const FLOAT& deltaTime) override;
	//---선택지 관련----
	void DetailSelect(int selectNum) override;
};