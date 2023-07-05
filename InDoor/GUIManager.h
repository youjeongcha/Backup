#pragma once
#include "Singleton.h"
#include "Object.h"

enum UI_SELECT
{
	UI_SELECT_X = ENGINE::ClientSize_Width - 10,
	UI_SELECT_Y = ENGINE::ClientSize_Height - 40,
};

namespace ENGINE
{
	class GUIManager : public Singleton<GUIManager>
	{
	private:
		BOOL isPause;
		UIImage* select_UI;


		GUIManager();
	public:
		~GUIManager();
		void Initialize();
		void Clear();
		void Update();
		void Draw();


		//TODO::추가 진행중인 코드
		//플레이어와 겹치는 object 선택
		void SelectOptional(std::vector<Object>& interObject);
		//플레이어와 겹치는 가로축 object의 index를 선택하는 양식
		void OptionalForm(std::vector<Object>& interObject);

		void SelectBtnClickHandler(Object* objectIndexs, int select);
		void CancelBtnClickHandler();

		bool Get_IsPause() { return isPause; }
		friend Singleton;

	#define GUIMgr GUIManager::GetInstance()
	};
}