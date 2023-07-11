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
	TIMEZONE_NIGHT, //��
	TIMEZONE_DAYTIME, //��
};

inline std::string GetNameOfEntity(int value)
{
	switch (value)
	{
	case FSMENTITY_WINDOW:
		return "â��";
	case FSMENTITY_DOOR:
		return "��";
	case FSMENTITY_FLOWERPOT:
		return "ȭ��";
	case FSMENTITY_NPC:
		return "NPC";
	default:
		return "Unknown!";
	}
}


class Ngiht : public State
{
private:
	//int m_Sec; //�� ���� �ð� üũ�� clock���� �ϰ� �ְ� ���� �Լ��� �� �� �������� sec�� ���� �־ ���� �߻�(�������� ��� �ٶ�)
	//int m_OldClock;

	Ngiht() {}
	//�Ʒ� �� �ڵ�� �̱��濡�� ���Ǹ� �ȵǴ� �ڵ��̱� ������ private���� ���Ƶ� ��(����. ���� �ʿ�X)
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
	//int m_Sec; //�� ���� �ð� üũ�� clock���� �ϰ� �ְ� ���� �Լ��� �� �� �������� sec�� ���� �־ ���� �߻�(�������� ��� �ٶ�)
	//int m_OldClock;

	Daytime() {}
	//�Ʒ� �� �ڵ�� �̱��濡�� ���Ǹ� �ȵǴ� �ڵ��̱� ������ private���� ���Ƶ� ��(����. ���� �ʿ�X)
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
	static int m_nNextVaildID; //�ش� �Լ��� ID ���ڸ� �����ؾ����ٵ�. ������ Object�� ���� ����� ���� �ʴ°� ����. �׸��� NPC�� ��� ó���� ��� ����.

public:
	FSM();
	~FSM();

	int Get_NextVaildID() { return m_nNextVaildID++; } //���±�� ����Ǵ� ��ƼƼ ����� ���� �� �����ϱ�
};

