#pragma once
#include "EngineMecro.h"
#ifndef ENGINE_MAIN_H
#define ENGINE_MAIN_H

/* ::Engine의 메인::
  기본적인 설정을 하여 Window를 만들고 게임 루프를 작동한다.
  디폴트 생성자를 사용하지 않기 위해 private에 선언*/


namespace ENGINE
{
	class WinApiEngine
	{
	private:
		bool isInit;
		//32비트(4바이트) 크기의 부호 !있!는 정수형 변수 선언
		INT32 x, y; //int32_t num3 = 2147483647; 
		//32비트(4바이트) 크기의 부호 !없!는 정수형 변수 선언
		UINT32 width, height; //uint32_t num7 = 4294967295;
		std::wstring title;

		//디폴트 생성자를 사용하지 않기 위해 private에 선언
		WinApiEngine();
	public:
		WinApiEngine(HINSTANCE hInstance, std::wstring title, INT32 per_x, INT32 per_y, UINT width, UINT height);
		~WinApiEngine();

		int Run();
		void Release();
	};
}


#endif // !ENGINE_MAIN_H