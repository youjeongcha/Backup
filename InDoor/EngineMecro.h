#pragma comment(lib, "msimg32.lib")
#pragma once
#include<crtdbg.h>
#include<Windows.h>
#include<time.h>
//#include<string>
//#include<vector>
//#include<map>
//#include<functional>
#include<algorithm>
//#include "Math.h"
#include"Component.h"

//-----�������� ���������� ���� ��ũ�� �Լ� �� �������̽� ����----- 
//FPS �� Window ũ�⸦ ������ �д�


#ifndef ENGINE_MECRO_H
#define ENGINE_MECRO_H

#ifndef DEL
#define DEL(a) if(a) {	delete a; a = nullptr; } //delete ��ũ�� �Լ�
#endif // !DEL

#ifndef REL_DEL
#define REL_DEL(a) if(a) { a->Release(); delete a; a = nullptr; } //Release() �Լ� ȣ�� �� delete
#endif // !REL_DEL

//typedef std::function<void()> EventListener; 

namespace ENGINE
{
	enum //����(no name) enum, ���� ������ ���Ǵ� ���� �⺻ ������ ���� ��
	{
		ClientSize_Width = 400,
		//ClientSize_Height = 600,
		ClientSize_Height = 140,
		//Client_Per_X = 50,
		Client_Per_X = 50,
		Client_Per_Y = 50, /*0 ~ 100%*/
		FPS = 120/*�ʴ� ������*/
	};

	__interface Scene
	{//���� ���� �����Լ� (�Ϲ������� �߻� Ŭ������ ����� �޾Ƽ� ����Ѵ�. �⺻ Ŭ�������� ��� ���� �� ����.)
		//������, �Ҹ���, ��� ����, ����(static) �Լ� ���� �Ұ�
		void Initialize();
		void Release();
		void Update(CONST float& deltaTime);
		void Draw();
	};
}

#endif // !ENGINE_MECRO_H