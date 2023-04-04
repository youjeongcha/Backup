#pragma once
#include "Object.h"

enum GOAL_IMG
{
	GOAL_IMG_W = 60,
	GOAL_IMG_H = 50,

	//GOAL_IMG_ARRIVE_X = MAIN_W - 150,
};

class Goal : public Object
{
private:
	bool m_EndPositionCheck; //골대가 제 위치에 도달한 상태인지 확인
	bool m_ActiveCheck; //화면상에서 작동 가능 여부 확인 위해
public:
	Goal();
	~Goal();
	virtual void Draw(HDC hdc) override;
	virtual void Update(float total_MoveDistance, float _Prev_MoveDistance) override;


	//void Set_Goal_X(float _X) { m_Rect[RECTTYPE_BITMAP].left = _X; } //M가 0이 출력될 차례가 오면 goal의 x 좌표 세팅
	
	//Goal이 그려짐+이동+충돌체크가 가능한 상태
	void Set_ActiveCheck(bool _ActiveCheck) { m_ActiveCheck = _ActiveCheck; }
	bool Get_ActiveCheck() { return m_ActiveCheck; }

	void Set_EndPositionCheck(bool _EndPositionCheck) { m_EndPositionCheck = _EndPositionCheck; }
	bool Get_EndPositionCheck() { return m_EndPositionCheck; }
	virtual bool ColliderCheck() override;
};