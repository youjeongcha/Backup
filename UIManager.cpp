#include "UIManager.h" 

namespace ENGINE
{
	UIManager::~UIManager()
	{
		Clear();
	}

	VOID UIManager::Initialize()
	{
		Clear();
	}

	VOID UIManager::Clear()
	{
		for (std::pair<std::string, UIPanel*> pair : map_UI)
			DEL(pair.second);

		map_UI.clear();
	}

	VOID UIManager::Update()
	{
		//�θ� ���� ��� �θ� �ʿ��� Update() �Լ��� ȣ�� �ϰ� �ִ�.
		for (std::pair<std::string, UIPanel*> pair : map_UI)
			if (!pair.second->GetParent())
				pair.second->Update();
	}

	VOID UIManager::Draw()
	{
		//�θ� ���� ��� �θ� �ʿ��� Draw() �Լ��� ȣ�� �ϰ� �ִ�.
		for (std::pair<std::string, UIPanel*> pair : map_UI)
			if (!pair.second->GetParent())
				pair.second->Draw();
	}

	UIPanel* UIManager::GetUI(std::string name)
	{
		auto iter = map_UI.find(name);

		if (map_UI.end() != iter)
			return iter->second;

		return nullptr;
	}

	BOOL UIManager::Remove(std::string name)
	{
		auto ui = GetUI(name);
		
		if (nullptr != ui)
		{
			map_UI.erase(name);
			DEL(ui);

			return true;
		}
		return false;
	}
} //namespace ENGINE