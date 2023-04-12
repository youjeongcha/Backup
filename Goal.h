#pragma once
#include "Object.h"



class Goal : public Object
{
private:
	bool m_EndPositionCheck; //골대가 제 위치에 도달한 상태인지 확인
	bool m_ActiveCheck; //화면상에서 작동 가능 여부 확인 위해

	//Rect 세팅
	virtual void SetRect() override; //변동성 있는 left와 right만 지속적으로 Set해주기 위해
public:
	Goal();
	~Goal();

	//초기 세팅 Goal에서는 인자를 사용하지 않는다.
	virtual void InitialSet(int _X, int _Y) override;
	virtual void Draw(HDC hdc) override;
	virtual void Update(float deltaTime, float total_MoveDistance, float _Prev_MoveDistance) override;

	
	//Goal이 그려짐+이동+충돌체크가 가능한 상태
	void Set_ActiveCheck(bool _ActiveCheck) { m_ActiveCheck = _ActiveCheck; }
	bool Get_ActiveCheck() { return m_ActiveCheck; }

	void Set_EndPositionCheck(bool _EndPositionCheck) { m_EndPositionCheck = _EndPositionCheck; }
	bool Get_EndPositionCheck() { return m_EndPositionCheck; }
};