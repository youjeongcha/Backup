#pragma once
#include "EngineMecro.h"
#ifndef SINGLETON_H
#define SINGLETON_H

//Template Singleton
//�Ŵ��� Ŭ�������� ���� �̱��� Ŭ���� ����

template<typename T>
class Singleton
{
private:
	static T* instance;

protected:
	Singleton() {}

public:
	static T* GetInstance()
	{
		if (nullptr == instance)
			instance = new T;
		return instance;
	}

	static void Destroy() { DEL(instance); }
};

template<typename T>T* Singleton<T>::instance = nullptr;
#endif //!SiNGLETON_H