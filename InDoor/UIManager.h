#pragma once
// UIManager.h
#include "Singleton.h"
#include "UIButton.h" //#include "UIImage.h"
#include "UILabel.h" //#include "UIPanel.h"

//해당 씬에서 사용할 UI를 가지고, 사용되는 모든 UI를 갱신 및 그리기를 처리하여 준다.

#ifndef UI_MANAGER_H
#define UI_MANAGER_H

namespace ENGINE
{
	class UIManager : public Singleton<UIManager>
	{
	private:
		std::map<std::string, UIPanel*> map_UI;
		std::vector<UIPanel*> child_UI;
		UIManager() {}
	public:
		~UIManager();
		VOID Initialize();
		VOID Clear();
		VOID Update();
		VOID Draw();

		//플레이어와 겹치는 가로축 object의 index를 선택하도록
		

		template<typename T> T* AddUI(std::string name, UIPanel* parent = nullptr);
		UIPanel* GetUI(std::string name);
		BOOL Remove(std::string name);
		friend Singleton;

	}; // class UIManager


	template<typename T>

	inline T* UIManager::AddUI(std::string name, UIPanel* parent)
	{
		if (name.empty()) 
			return nullptr; // 빈 문자열을 이름으로 지정할 수 없게 한다.

		auto iter = map_UI.find(name); // 이미 같은 이름의 UI가 있을 경우 추가 실패.

		if (map_UI.end() != iter) 
			return nullptr; // 이미 있는 UI의 타입이 다를 수 있기에 null을 반환.

		T* ui = new T;
		if (parent) parent->AddChildUI(ui);
		map_UI.insert(std::make_pair(name, ui));

		return ui;
	}

#define UIMgr UIManager::GetInstance()
}
#endif // !UI_MANAGER_H
