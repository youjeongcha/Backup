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

//-----엔진에서 전반적으로 사용될 메크로 함수 및 인터페이스 정의----- 
//FPS 및 Window 크기를 지정해 둔다


#ifndef ENGINE_MECRO_H
#define ENGINE_MECRO_H

#ifndef DEL
#define DEL(a) if(a) {	delete a; a = nullptr; } //delete 매크로 함수
#endif // !DEL

#ifndef REL_DEL
#define REL_DEL(a) if(a) { a->Release(); delete a; a = nullptr; } //Release() 함수 호출 후 delete
#endif // !REL_DEL

//typedef std::function<void()> EventListener; 

namespace ENGINE
{
	enum //무명(no name) enum, 게임 엔진에 사용되는 여러 기본 데이터 서렁 값
	{
		ClientSize_Width = 400,
		//ClientSize_Height = 600,
		ClientSize_Height = 140,
		//Client_Per_X = 50,
		Client_Per_X = 50,
		Client_Per_Y = 50, /*0 ~ 100%*/
		FPS = 120/*초당 프레임*/
	};

	__interface Scene
	{//공용 순수 가상함수 (일반적으로 추상 클래스가 상속을 받아서 사용한다. 기본 클래스에서 상속 받을 수 없다.)
		//생성자, 소멸자, 멤버 변수, 정적(static) 함수 포함 불가
		void Initialize();
		void Release();
		void Update(CONST float& deltaTime);
		void Draw();
	};
}

#endif // !ENGINE_MECRO_H