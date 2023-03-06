#ifndef _STATE_H_
#define _STATE_H_

struct Telegram;

template<typename T>
class State
{
public:
	virtual ~State(){}

	// 상태에 진입할 때 이것이 실행된다.
	virtual void Enter(T*) = 0;

	// 갱신 단계에서 mnier의 갱신 함수가 호출된다.
	virtual void Execute(T*) = 0;

	// 상태 퇴장 시에 실행된다.
	virtual void Exit(T*, bool) = 0;

	// 에이전트가 메시지 발송기로부터 
	// 메시지를 접수하면 이 부분이 실행된다.
	virtual bool OnMessage(T*, const Telegram&) = 0;
};

#endif