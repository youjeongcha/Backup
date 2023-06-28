#pragma once
// UIManager.h
#include "Singleton.h"
#include "UIButton.h" //#include "UIImage.h"
#include "UILabel.h" //#include "UIPanel.h"

//�ش� ������ ����� UI�� ������, ���Ǵ� ��� UI�� ���� �� �׸��⸦ ó���Ͽ� �ش�.

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

		//�÷��̾�� ��ġ�� ������ object�� index�� �����ϵ���
		

		template<typename T> T* AddUI(std::string name, UIPanel* parent = nullptr);
		UIPanel* GetUI(std::string name);
		BOOL Remove(std::string name);
		friend Singleton;

	}; // class UIManager


	template<typename T>

	inline T* UIManager::AddUI(std::string name, UIPanel* parent)
	{
		if (name.empty()) 
			return nullptr; // �� ���ڿ��� �̸����� ������ �� ���� �Ѵ�.

		auto iter = map_UI.find(name); // �̹� ���� �̸��� UI�� ���� ��� �߰� ����.

		if (map_UI.end() != iter) 
			return nullptr; // �̹� �ִ� UI�� Ÿ���� �ٸ� �� �ֱ⿡ null�� ��ȯ.

		T* ui = new T;
		if (parent) parent->AddChildUI(ui);
		map_UI.insert(std::make_pair(name, ui));

		return ui;
	}

#define UIMgr UIManager::GetInstance()
}
#endif // !UI_MANAGER_H
