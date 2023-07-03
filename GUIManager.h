#pragma once
#include "Singleton.h"
#include "UIManager.h"

namespace ENGINE
{
	class GUIManager : public Singleton<GUIManager>
	{
	private:
		GUIManager();
	public:
		~GUIManager();
		//TODO::추가 진행중인 코드
		//플레이어와 겹치는 가로축 object의 index를 선택하도록
		void OptionalForm();
		friend Singleton;

	#define GUIMgr GUIManager::GetInstance()
	};
}