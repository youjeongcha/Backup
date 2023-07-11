#pragma once
#include "Window.h"

enum FSMENTITY
{
	FSMENTITY_WINDOW,
	FSMENTITY_DOOR,
	FSMENTITY_FLOWERPOT,


	FSMENTITY_NPC,
	FSMENTITY_COUNT,
};

enum class TIMEZONE
{
	TIMEZONE_NIGHT, //밤
	TIMEZONE_DAYTIME, //낮
};

inline std::string GetNameOfEntity(int value)
{
	switch (value)
	{
	case FSMENTITY_WINDOW:
		return "창문";
	case FSMENTITY_DOOR:
		return "문";
	case FSMENTITY_FLOWERPOT:
		return "화분";
	case FSMENTITY_NPC:
		return "NPC";
	default:
		return "Unknown!";
	}
}


class Ngiht : public State
{
private:
	//int m_Sec; //★ 실제 시간 체크는 clock으로 하고 있고 내부 함수로 한 턴 돌때마다 sec를 세고 있어서 괴리 발생(다음에는 고려 바람)
	//int m_OldClock;

	Ngiht() {}
	//아래 두 코드는 싱글톤에서 사용되면 안되는 코드이기 때문에 private으로 막아둔 것(보험. 굳이 필요X)
	Ngiht(const Ngiht&);
	Ngiht& operator=(const Ngiht&);
public:
	static Ngiht* Instance();

	virtual void Enter(Object*);
	virtual void Excute(Object*);
	virtual void Exit(Object*);
};

class Daytime : public State
{
private:
	//int m_Sec; //★ 실제 시간 체크는 clock으로 하고 있고 내부 함수로 한 턴 돌때마다 sec를 세고 있어서 괴리 발생(다음에는 고려 바람)
	//int m_OldClock;

	Daytime() {}
	//아래 두 코드는 싱글톤에서 사용되면 안되는 코드이기 때문에 private으로 막아둔 것(보험. 굳이 필요X)
	Daytime(const Daytime&);
	Daytime& operator=(const Daytime&);
public:
	static Daytime* Instance();

	virtual void Enter(Object*);
	virtual void Excute(Object*);
	virtual void Exit(Object*);
};

class FSM
{
private:
	static int m_nNextVaildID; //해당 함수로 ID 숫자를 관리해야할텐데. 문제는 Object에 이중 상속을 쓰지 않는게 좋다. 그리고 NPC의 경우 처리를 어떻게 하지.

public:
	FSM();
	~FSM();

	int Get_NextVaildID() { return m_nNextVaildID++; } //상태기계 적용되는 엔티티 만들고 나면 수 증가하기
};

