#pragma once
#include "EngineMecro.h"
#ifndef ENGINE_MAIN_H
#define ENGINE_MAIN_H

/* ::Engine�� ����::
  �⺻���� ������ �Ͽ� Window�� ����� ���� ������ �۵��Ѵ�.
  ����Ʈ �����ڸ� ������� �ʱ� ���� private�� ����*/


namespace ENGINE
{
	class WinApiEngine
	{
	private:
		bool isInit;
		//32��Ʈ(4����Ʈ) ũ���� ��ȣ !��!�� ������ ���� ����
		INT32 x, y; //int32_t num3 = 2147483647; 
		//32��Ʈ(4����Ʈ) ũ���� ��ȣ !��!�� ������ ���� ����
		UINT32 width, height; //uint32_t num7 = 4294967295;
		std::wstring title;

		//����Ʈ �����ڸ� ������� �ʱ� ���� private�� ����
		WinApiEngine();
	public:
		WinApiEngine(HINSTANCE hInstance, std::wstring title, INT32 per_x, INT32 per_y, UINT width, UINT height);
		~WinApiEngine();

		int Run();
		void Release();
	};
}


#endif // !ENGINE_MAIN_H