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
		//TODO::�߰� �������� �ڵ�
		//�÷��̾�� ��ġ�� ������ object�� index�� �����ϵ���
		void OptionalForm();
		friend Singleton;

	#define GUIMgr GUIManager::GetInstance()
	};
}