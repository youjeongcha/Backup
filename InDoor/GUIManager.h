#pragma once
#include "Singleton.h"
#include "UIManager.h"
#include "Object.h"

namespace ENGINE
{
	class GUIManager : public Singleton<GUIManager>
	{
	private:
		UIImage* select_UI;


		GUIManager();
	public:
		~GUIManager();
		//TODO::추가 진행중인 코드
		//플레이어와 겹치는 object 선택
		int SelectOptional(Object** objectIndexs, int inter_Count);
		//플레이어와 겹치는 가로축 object의 index를 선택하는 양식
		void OptionalForm(Object** objectIndexs, int inter_Count);

		void SelectBtnClickHandler(Object** objectIndexs, int select);
		void CancelBtnClickHandler();


		friend Singleton;

	#define GUIMgr GUIManager::GetInstance()
	};
}