#ifndef _BASE_GAME_ENTITY_H_
#define _BASE_GAME_ENTITY_H_

#include <string>

#include "Telegram.h"

class BaseGameEntity
{
private:
	// 모든 엔티티들은 고유한 식별번호를 갖는다.
	int m_ID;

	// 이것은 유효한 다음 식별번호이다.
	// BaseGameEntity가 매번 초기화될 때 이 값도 갱신된다.
	static int m_iNextValidID;

	// 이것은 ID가 정확하게 설정되도록 생성자 내부에서 호출된다.
	// 이것은 ID를 설정하고 우효한 다음 ID를 증가시키키 전에,
	// 메소드에 전달된 값이 유효한 다음 ID보다 더 큰지 아니면 같은지를 확인한다.
	void SetID(int id);

public:
	BaseGameEntity(int id)
	{
		SetID(id);
	}

	virtual ~BaseGameEntity(){}

	// 모든 엔티티들은 갱신 함수를 설치하고 있어야만 한다.
	virtual void Update() = 0;

	int ID()const
	{
		return m_ID;
	}

	virtual bool HandleMessage(const Telegram& msg) = 0;
};

#endif