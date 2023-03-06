#ifndef _STATE_H_
#define _STATE_H_

struct Telegram;

template<typename T>
class State
{
public:
	virtual ~State(){}

	// ���¿� ������ �� �̰��� ����ȴ�.
	virtual void Enter(T*) = 0;

	// ���� �ܰ迡�� mnier�� ���� �Լ��� ȣ��ȴ�.
	virtual void Execute(T*) = 0;

	// ���� ���� �ÿ� ����ȴ�.
	virtual void Exit(T*, bool) = 0;

	// ������Ʈ�� �޽��� �߼۱�κ��� 
	// �޽����� �����ϸ� �� �κ��� ����ȴ�.
	virtual bool OnMessage(T*, const Telegram&) = 0;
};

#endif