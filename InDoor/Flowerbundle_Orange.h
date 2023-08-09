#pragma once
#include "Object.h"

class Flowerbundle_Orange : public Object
{
private:
	FRUITS_GROWTH growthRate;
	bool seedPlanting, watering; //�̹� ������ ����, �̹� ���� �� Ȯ��
	float m_elapsedHour, m_elapsedSec, m_elapsedMin; // �Ĺ� ���� - ��� �ð� (��, �� ����)

public:
	Flowerbundle_Orange();
	Flowerbundle_Orange(const ObjectData& dataSet, int index);
	~Flowerbundle_Orange();
	VOID Initialize() override;
	VOID Move(const FLOAT& deltaTime) override;
	void PassOfthe_TimeChangeBitmap() override;
	void Update(const FLOAT& deltaTime) override;
	//---������ ����----
	void DetailSelect(int selectNum) override;
};